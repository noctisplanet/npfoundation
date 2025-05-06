//
//  Definitions.h
//  npfoundation
//
//  Created by Jonathan Lee on 5/6/25.
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
