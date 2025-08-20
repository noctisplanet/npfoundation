//
//  NSValueObserving.h
//  npfoundation
//
//  Created by Jonathan Lee on 8/19/25.
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

#ifndef NP_OBJC_NSVALUEOBSERVING_H
#define NP_OBJC_NSVALUEOBSERVING_H
#ifdef __OBJC__

#include <NPFoundation/Definitions.h>
#include <Foundation/Foundation.h>

NP_CEXTERN_BEGIN

NP_EXTERN void NPAttachDeallocationHandler(id<NSObject> observable, dispatch_block_t handler);

NP_CEXTERN_END

#endif /* __OBJC__ */
#endif /* NP_OBJC_NSVALUEOBSERVING_H */
