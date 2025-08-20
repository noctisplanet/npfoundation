//
//  schedule.m
//  npfoundation
//
//  Created by Jonathan Lee on 8/14/25.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#include <NPFoundation/dispatch.h>
#include <Foundation/Foundation.h>

void NPDispatchScheduleThrottle(double delayInSeconds, dispatch_queue_t on, dispatch_block_t callback) {
    static dispatch_queue_t queue = NULL;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        dispatch_queue_attr_t attribute = dispatch_queue_attr_make_with_qos_class(DISPATCH_QUEUE_SERIAL, QOS_CLASS_USER_INITIATED, 0);
        queue = dispatch_queue_create("com.dispatch.throttle-queue", attribute);
    });
    
    __block double previous = 0;
    dispatch_block_t block = ^{
        double timestamp = CFAbsoluteTimeGetCurrent();
        if (timestamp - previous >= delayInSeconds) {
            previous = timestamp;
            dispatch_async(on, callback);
        }
    };
    return ^{
        dispatch_async(queue, block);
    };
}

void NPDispatchScheduleDeboundce(double delayInSeconds, double leewayInSeconds, dispatch_queue_t on, dispatch_block_t callback) {
    static dispatch_queue_t queue = NULL;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        dispatch_queue_attr_t attribute = dispatch_queue_attr_make_with_qos_class(DISPATCH_QUEUE_SERIAL, QOS_CLASS_USER_INITIATED, 0);
        queue = dispatch_queue_create("com.dispatch.deboundce-queue", attribute);
    });
    
    __block uint64_t previous = 0;
    dispatch_block_t block = ^{
        uint64_t seq = ++previous;
        double started = CFAbsoluteTimeGetCurrent();
        dispatch_after(dispatch_walltime(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC)), queue, ^{
            if (seq == previous) {
                dispatch_async(on, callback);
            } else if (previous - seq == 1) {
                double ended = CFAbsoluteTimeGetCurrent();
                double timeout = ended - started - delayInSeconds;
                if (timeout < leewayInSeconds) {
                    dispatch_async(on, callback);
                }
            }
        });
    };
    return ^{
        dispatch_async(queue, block);
    };
}
