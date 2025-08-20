//
//  MachineContext.h
//  npfoundation
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

#ifndef NP_MACHINE_CONTEXT_H
#define NP_MACHINE_CONTEXT_H

#include <NPFoundation/Definitions.h>
#include <sys/ucontext.h>
#include <stdbool.h>
#include <pthread.h>

NP_CEXTERN_BEGIN

struct KNMachineContext {
//#ifdef __arm64__
//    _STRUCT_MCONTEXT64 data;
//#else
    _STRUCT_MCONTEXT data;
//#endif
};

NP_EXTERN bool KNMachineContextGet(struct KNMachineContext *context, pthread_t thread);

NP_EXTERN uintptr_t KNMachineContextGetFramePointer(const struct KNMachineContext *const context);

NP_EXTERN uintptr_t KNMachineContextGetStackPointer(const struct KNMachineContext *const context);

NP_EXTERN uintptr_t KNMachineContextGetInstructionAddress(const struct KNMachineContext *const context);

NP_EXTERN uintptr_t KNMachineContextGetLinkRegister(const struct KNMachineContext *const context);

NP_CEXTERN_END

#endif /* NP_MACHINE_CONTEXT_H */
