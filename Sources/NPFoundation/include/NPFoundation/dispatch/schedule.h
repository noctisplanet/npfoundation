//
//  schedule.h
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

#ifndef NP_DISPATCH_SCHEDULE_H
#define NP_DISPATCH_SCHEDULE_H
#ifdef __BLOCKS__

#include <NPFoundation/Definitions.h>
#include <dispatch/dispatch.h>

NP_CEXTERN_BEGIN

struct NPScheduleWork {
    dispatch_block_t resume;
    dispatch_block_t cancel;
};
typedef struct NPScheduleWork NPScheduleWork;

/// Schedules a throttled execution of a callback function on a specified dispatch queue.
///
/// Throttling ensures the callback is executed at most once within the specified delay period,
/// regardless of how many times the returned NPScheduleWork function is called.
///
/// Calling cancel is ineffective in NPDispatchScheduleThrottle because it executes immediately (from a timeline perspective)
///
/// - Parameters:
///   - delayInSeconds: The minimum delay (in seconds) between allowed callback executions.
///                     Subsequent calls to the returned NPScheduleWork within this delay window will be ignored.
///   - on: The dispatch queue on which to execute the callback function.
///   - callback: The function to execute when the throttling condition is met.
NP_EXTERN NPScheduleWork NPDispatchScheduleThrottle(double delayInSeconds, dispatch_queue_t on, dispatch_block_t callback);

/// Schedules a debounced execution of a callback function on a specified dispatch queue.
///
/// Debouncing delays the callback execution until after the specified delay has elapsed
/// without receiving new calls to the returned NPScheduleWork function.
///
/// Calling cancel is effective in NPDispatchScheduleDebounce because its tasks are always delayed.
///
/// - Parameters:
///   - delayInSeconds: The debounce delay (in seconds) that must pass without new calls
///                     to the returned NPScheduleWork before the callback is executed.
///   - leewayInSeconds: The allowed leeway (in seconds) for timer execution to optimize
///                     power consumption and performance. A positive value indicates
///                     the system may delay timer firing within this tolerance.
///   - on: The dispatch queue on which to execute the callback function.
///   - callback: The function to execute when the debounce condition is met.
NP_EXTERN NPScheduleWork NPDispatchScheduleDeboundce(double delayInSeconds, double leewayInSeconds, dispatch_queue_t on, dispatch_block_t callback);

NP_CEXTERN_END

#endif /* __BLOCKS__ */
#endif /* NP_DISPATCH_SCHEDULE_H */
