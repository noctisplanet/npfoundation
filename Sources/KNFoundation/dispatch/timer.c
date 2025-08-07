//
//  timer.h
//  knfoundation
//
//  Created by Jonathan Lee on 7/13/25.
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

#include <KNFoundation/dispatch.h>

dispatch_source_t KNDispatchTimerCreate(dispatch_queue_t queue, double interval, dispatch_block_t block) {
    if (queue == NULL) {
        queue = dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0);
    }
    dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
    dispatch_source_set_timer(timer, DISPATCH_TIME_NOW, interval * NSEC_PER_SEC, 0 * NSEC_PER_SEC);
    dispatch_source_set_event_handler(timer, block);
    return timer;
}

dispatch_source_t KNDispatchTimerFire(dispatch_queue_t queue, double interval, dispatch_block_t block) {
    dispatch_source_t timer = KNDispatchTimerCreate(queue, interval, block);
    dispatch_activate(timer);
    return timer;
}

void KNDispatchTimerResume(dispatch_source_t timer) {
    if (timer) {
        dispatch_resume(timer);
    }
}

void KNDispatchTimerSuspend(dispatch_source_t timer) {
    if (timer) {
        dispatch_suspend(timer);
    }
}

void KNDispatchTimerCancel(dispatch_source_t timer) {
    if (timer) {
        dispatch_source_cancel(timer);
    }
}
