//
//  Definitions.h
//  knfoundation
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

#ifndef KN_DEFINITION_H
#define KN_DEFINITION_H

#ifdef __APPLE__
#include <Availability.h>
#include <TargetConditionals.h>
#define KN_PLATFORM_APPLE 1
#endif

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
#define KN_DESTINATION_XROS 1
#else
#define KN_DESTINATION_XROS 0
#endif

#define KN_DESTINATION_IOS     (KN_PLATFORM_APPLE && TARGET_OS_IOS  )
#define KN_DESTINATION_TVOS    (KN_PLATFORM_APPLE && TARGET_OS_TV   )
#define KN_DESTINATION_WATCHOS (KN_PLATFORM_APPLE && TARGET_OS_WATCH)
#define KN_DESTINATION_MACOS   (KN_PLATFORM_APPLE && TARGET_OS_MAC && !(TARGET_OS_IOS || TARGET_OS_TV || TARGET_OS_WATCH || KN_DESTINATION_XROS))

#if KN_DESTINATION_IOS || KN_DESTINATION_TVOS || KN_DESTINATION_WATCHOS || KN_DESTINATION_XROS
#define KN_HAS_UIKIT 1
#else
#define KN_HAS_UIKIT 0
#endif

#if defined(__cplusplus)
#define KN_EXTERN extern "C"
#else
#define KN_EXTERN extern
#endif

#define KN_EXPORT KN_EXTERN
#define KN_IMPORT KN_EXTERN

#define KN_STATIC_INLINE static __inline__
#define KN_EXTERN_INLINE extern __inline__

#if defined(__cplusplus)
#define KN_CEXTERN_BEGIN extern "C" {
#define KN_CEXTERN_END }
#else
#define KN_CEXTERN_BEGIN
#define KN_CEXTERN_END
#endif

#define KN_NAMESPACE_BEGIN(NAME) namespace NAME {
#define KN_NAMESPACE_END }

#ifdef __cplusplus

KN_NAMESPACE_BEGIN(KN)

// Mix-in for classes that must not be copied.
class nocopy {
  
private:
    
    nocopy(const nocopy&) = delete;
    const nocopy& operator=(const nocopy&) = delete;
    
protected:
    
    constexpr nocopy() = default;
    ~nocopy() = default;
};

KN_NAMESPACE_END

#endif /* __cplusplus */

#endif /* KN_DEFINITION_H */
