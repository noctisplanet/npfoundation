//
//  timer.h
//  npfoundation
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

#ifndef NP_DISPATCH_TIMER_H
#define NP_DISPATCH_TIMER_H
#ifdef __BLOCKS__

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif /* __OBJC__ */

#include <CoreFoundation/CoreFoundation.h>
#include <NPFoundation/Definitions.h>
#include <dispatch/dispatch.h>

NP_CEXTERN_BEGIN

struct np_timer_t {
    CFTypeRef ref;
};

typedef struct np_timer_t * np_timer;

NP_EXTERN dispatch_source_t KNDispatchTimerCreate(dispatch_queue_t queue, double interval, dispatch_block_t block);

NP_EXTERN dispatch_source_t KNDispatchTimerFire(dispatch_queue_t queue, double interval, dispatch_block_t block);

#ifdef __OBJC__
NP_EXTERN dispatch_source_t KNDispatchTimerFireWithObservable(id observable, dispatch_queue_t queue, double interval, dispatch_block_t block);
#endif /* __OBJC__ */

NP_EXTERN void KNDispatchTimerResume(dispatch_source_t timer);

NP_EXTERN void KNDispatchTimerSuspend(dispatch_source_t timer);

NP_EXTERN void KNDispatchTimerCancel(dispatch_source_t timer);

NP_CEXTERN_END

#endif /* __BLOCKS__ */
#endif /* NP_DISPATCH_TIMER_H */
