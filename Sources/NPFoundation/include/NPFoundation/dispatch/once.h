//
//  once.h
//  npfoundation
//
//  Created by Jonathan Lee on 6/14/25.
//

#ifndef NP_DISPATCH_ONCE_H
#define NP_DISPATCH_ONCE_H
#ifdef __BLOCKS__

#include <NPFoundation/Definitions.h>
#include <dispatch/dispatch.h>

NP_CEXTERN_BEGIN

NP_EXTERN void NPDispatchOnce(dispatch_once_t *predicate, void(*func)(void));

NP_CEXTERN_END

#endif /* __BLOCKS__ */
#endif /* NP_DISPATCH_ONCE_H */
