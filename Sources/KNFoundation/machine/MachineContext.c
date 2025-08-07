//
//  MachineContext.c
//  knfoundation
//
//  Created by Jonathan Lee on 6/27/25.
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

#include <KNFoundation/machine.h>
#include <mach/mach_types.h>
#include <mach/mach_error.h>
#include <mach/thread_act.h>

#if KN_DESTINATION_IOS || KN_DESTINATION_TVOS || KN_DESTINATION_MACOS || KN_DESTINATION_XROS
static bool setState(const thread_t thread, const thread_state_t state, const thread_state_flavor_t flavor, const mach_msg_type_number_t number) {
    mach_msg_type_number_t cnt = number;
    kern_return_t kr = thread_get_state(thread, flavor, state, &cnt);
    if (kr == KERN_SUCCESS) {
        return true;
    } else {
        return false;
    }
}
#else
KN_STATIC_INLINE bool fillState(const thread_t thread, const thread_state_t state, const thread_state_flavor_t flavor, const mach_msg_type_number_t stateCount) {
    return false;
}
#endif

bool KNMachineContextGet(struct KNMachineContext *context, pthread_t thread) {
    if (!context) {
        return false;
    }
    const thread_t machThread = pthread_mach_thread_np(thread);
    if (machThread == MACH_PORT_NULL) {
        return false;
    }
#if defined(__arm__)
    return setState(machThread, (thread_state_t)&context->data.__ss, ARM_THREAD_STATE, ARM_THREAD_STATE_COUNT) &&
        setState(machThread, (thread_state_t)&context->data.__es, ARM_EXCEPTION_STATE, ARM_EXCEPTION_STATE_COUNT);
#elif defined(__arm64__)
    return setState(machThread, (thread_state_t)&context->data.__ss, ARM_THREAD_STATE64, ARM_THREAD_STATE64_COUNT) &&
        setState(machThread, (thread_state_t)&context->data.__es, ARM_EXCEPTION_STATE64, ARM_EXCEPTION_STATE64_COUNT);
#elif defined(__i386__)
    return setState(machThread, (thread_state_t)&context->data.__ss, x86_THREAD_STATE32, x86_THREAD_STATE32_COUNT) &&
        setState(machThread, (thread_state_t)&context->data.__es, x86_EXCEPTION_STATE32, x86_EXCEPTION_STATE32_COUNT);
#elif defined(__x86_64__)
    return setState(machThread, (thread_state_t)&context->data.__ss, x86_THREAD_STATE64, x86_THREAD_STATE64_COUNT) &&
        setState(machThread, (thread_state_t)&context->data.__es, x86_EXCEPTION_STATE64, x86_EXCEPTION_STATE64_COUNT);
#endif
}

uintptr_t KNMachineContextGetFramePointer(const struct KNMachineContext *const context) {
#if defined(__arm__)
    return context->data.__ss.__r[7];
#elif defined(__arm64__)
    return context->data.__ss.__fp;
#elif defined(__i386__)
    return context->data.__ss.__ebp;
#elif defined(__x86_64__)
    return context->data.__ss.__rbp;
#endif
}

uintptr_t KNMachineContextGetStackPointer(const struct KNMachineContext *const context) {
#if defined(__arm__)
    return context->data.__ss.__sp;
#elif defined(__arm64__)
    return context->data.__ss.__sp;
#elif defined(__i386__)
    return context->data.__ss.__esp;
#elif defined(__x86_64__)
    return context->data.__ss.__rsp;
#endif
}

uintptr_t KNMachineContextGetInstructionAddress(const struct KNMachineContext *const context) {
#if defined(__arm__)
    return context->data.__ss.__pc;
#elif defined(__arm64__)
    return context->data.__ss.__pc;
#elif defined(__i386__)
    return context->data.__ss.__eip;
#elif defined(__x86_64__)
    return context->data.__ss.__rip;
#endif
}

uintptr_t KNMachineContextGetLinkRegister(const struct KNMachineContext *const context) {
#if defined(__arm__)
    return context->data.__ss.__lr;
#elif defined(__arm64__)
    return context->data.__ss.__lr;
#elif defined(__i386__)
    return 0;
#elif defined(__x86_64__)
    return 0;
#endif
}
