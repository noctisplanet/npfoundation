//
//  NSObjCRuntime.h
//  npfoundation
//
//  Created by Jonathan Lee on 5/6/25.
//

#ifndef NP_OBJC_NSOBJCRUNTIME_H
#define NP_OBJC_NSOBJCRUNTIME_H

#include <objc/message.h>
#include <objc/runtime.h>
#include <NPFoundation/Definitions.h>

// A >> A
#define _NP_GUARD_(A) A
// (id self, SEL name, ) >> (id self, )
#define _NP_BLOCK_ARGS_(A1,A2,ARGS...) A1, ##ARGS
// (id self, SEL name, ) >> (id self, SEL name, )
#define _NP_FUNCTION_ARGS_(A1,A2,ARGS...) A1, A2, ##ARGS
// (id self, SEL name, ) >> (struct objc_super *super, SEL name, )
#define _NP_OBJCSUPER_ARGS_(A1,A2,ARGS...) _NP_GUARD_(struct objc_super *super), A2, ##ARGS

// A >> A
#define NP_RETURN(TYPE) TYPE

// A1,A2, >> A1,A2
#define NP_ARGS(ARGS...) ARGS

/// class_addMethod
///
#define NP_CLASS_ADDMETHOD_BEGIN(CLASS,SELECTOR,TYPES,RETURN,ARGS)                                  \
    do {                                                                                            \
        Class          __cls = (CLASS);                                                             \
        SEL            __sel = (SELECTOR);                                                          \
        if (!__cls || !__sel) break;                                                                \
        const char * __types = (TYPES);                                                             \
        IMP            __imp = imp_implementationWithBlock(^__typeof(RETURN)(_NP_BLOCK_ARGS_(ARGS))
        
#define NP_CLASS_ADDMETHOD_PROCESS                                                                  \
        );                                                                                          \
        __attribute__((unused)) bool __success = class_addMethod(__cls, __sel, __imp, __types);     

#define NP_CLASS_ADDMETHOD_END                                                                      \
    } while(false);

/// class_replaceMethod
///


#endif /* NP_OBJC_NSOBJCRUNTIME_H */
