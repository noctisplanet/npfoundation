//
//  Definitions.h
//  npfoundation
//
//  Created by Jonathan Lee on 5/6/25.
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

#include <TargetConditionals.h>
#include <Availability.h>

#if defined(__cplusplus)
#define NP_EXTERN extern "C"
#else
#define NP_EXTERN extern
#endif

#define NP_EXPORT NP_EXTERN
#define NP_IMPORT NP_EXTERN

#define NP_STATIC_INLINE static __inline__
#define NP_EXTERN_INLINE extern __inline__

#if defined(__cplusplus)
#define NP_CEXTERN_BEGIN extern "C" {
#define NP_CEXTERN_END }
#else
#define NP_CEXTERN_BEGIN
#define NP_CEXTERN_END
#endif

#define NP_NAMESPACE_BEGIN(NAME) namespace NAME {
#define NP_NAMESPACE_END }
