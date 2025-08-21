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

#include <CoreFoundation/CoreFoundation.h>
#include <NPFoundation/Definitions.h>
#include <dispatch/dispatch.h>

NP_CEXTERN_BEGIN

typedef dispatch_source_t NPTimer;

#ifdef __OBJC__

#import <Foundation/Foundation.h>

/// Creates a new timer to monitor low-level system events with automatic lifecycle management.
///
/// The timer is automatically activated and its lifecycle is bound to the observable object.
/// When the observable object is deallocated, the timer will be automatically cancelled.
///
/// - Parameters:
///   - observable: The object to which the timer's lifecycle will be bound.
///   - dispatchQueue: The dispatch queue to which the event handler block is submitted.
///   - intervalInSeconds: The seconds interval for the timer.
///   - leewayInSeconds: The amount of time, in nanoseconds, that the system can defer the timer.
///   - block: The event handler block to submit to the source’s target queue.
///            This function performs a Block_copy on behalf of the caller,
///            and Block_release on the previous handler (if any).
///            This parameter cannot be NULL.
NP_EXTERN NPTimer NPDispatchTimerObservable(id observable, dispatch_queue_t dispatchQueue, double intervalInSeconds, double leewayInSeconds, dispatch_block_t block);

#endif /* __OBJC__ */

/// Creates a new timer to monitor low-level system events.
///
/// The timer is automatically activated.
///
/// - Parameters:
///   - dispatchQueue: The dispatch queue to which the event handler block is submitted.
///   - intervalInSeconds: The seconds interval for the timer.
///   - leewayInSeconds: The amount of time, in nanoseconds, that the system can defer the timer.
///   - block: The event handler block to submit to the source’s target queue.
///            This function performs a Block_copy on behalf of the caller,
///            and Block_release on the previous handler (if any).
///            This parameter cannot be NULL.
NP_EXTERN NPTimer NPDispatchTimer(dispatch_queue_t dispatchQueue, double intervalInSeconds, double leewayInSeconds, dispatch_block_t block);

/// Asynchronously resume the NPTimer
/// - Parameter timer: The timer to resume
NP_EXTERN void NPDispatchTimerResume(NPTimer timer);

/// Asynchronously suspend the NPTimer
/// - Parameter timer: The timer to suspend
NP_EXTERN void NPDispatchTimerSuspend(NPTimer timer);

/// Asynchronously cancel the NPTimer
/// - Parameter timer: The timer to cancel
NP_EXTERN void NPDispatchTimerCancel(NPTimer timer);

NP_CEXTERN_END

#endif /* __BLOCKS__ */
#endif /* NP_DISPATCH_TIMER_H */
