//
//  NSObjCRuntime.h
//  knfoundation
//
//  Created by Jonathan Lee on 5/6/25.
//
//  MIT License
//
//  Copyright (c) 2025 Jonathan Lee
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

#ifndef KN_OBJC_NSOBJCRUNTIME_H
#define KN_OBJC_NSOBJCRUNTIME_H

#include <objc/message.h>
#include <objc/runtime.h>
#include <KNFoundation/Definitions.h>

KN_CEXTERN_BEGIN

struct _kn_objc_super2 {
    id _Nonnull receiver;
    Class _Nonnull current_class;
};

KN_EXTERN Method _Nullable KNClassGetOwnMethod(Class _Nullable cls, SEL _Nonnull name);

KN_EXTERN Method _Nullable KNClassGetSuperMethod(Class _Nullable cls, SEL _Nonnull name);

KN_CEXTERN_END

// A >> A
#define _KN_GUARD_(A) A

// (id self, SEL name, ) >> (id self, )
#define _KN_BLOCK_ARGS_(A1,A2,ARGS...) A1, ##ARGS
// (id self, SEL name, ) >> (id self, SEL name, )
#define _KN_FUNCTION_ARGS_(A1,A2,ARGS...) A1, A2, ##ARGS
// (id self, SEL name, ) >> (struct objc_super *super, SEL name, )
#define _KN_OBJCSUPER_ARGS_(A1,A2,ARGS...) _KN_GUARD_(struct _kn_objc_super2 *super), A2, ##ARGS

// A >> A
#define KN_RETURN(TYPE) TYPE

// A1,A2, >> A1,A2
#define KN_ARGS(ARGS...) ARGS

/// class_addMethod
///
#define KN_CLASS_ADDMETHOD_BEGIN(CLASS,SELECTOR,TYPES,RETURN,ARGS)                                                          \
    do {                                                                                                                    \
        Class        _kn_cls     = (CLASS);                                                                                 \
        SEL          _kn_sel     = (SELECTOR);                                                                              \
        const char * _kn_types   = NULL;                                                                                    \
        __block IMP  _kn_imp     = NULL;                                                                                    \
        __block bool _kn_success = false;                                                                                   \
        if (_kn_cls && _kn_sel) {                                                                                           \
            _kn_types            = (TYPES);                                                                                 \
            _kn_imp              = imp_implementationWithBlock(^__typeof(RETURN)(_KN_BLOCK_ARGS_(ARGS))
        
#define KN_CLASS_ADDMETHOD_PROCESS                                                                                          \
                );                                                                                                          \
            _kn_success          = class_addMethod(_kn_cls, _kn_sel, _kn_imp, _kn_types);                                   \
        }

#define KN_CLASS_ADDMETHOD_END                                                                                              \
    } while(false);

/// class_replaceMethod
///
#define KN_CLASS_REPLACEMETHOD_BEGIN(CLASS,SELECTOR,TYPES,RETURN,ARGS)                                                      \
    do {                                                                                                                    \
        typedef __typeof(RETURN)(*_KN_NEXT_IMP)(_KN_FUNCTION_ARGS_(ARGS));                                                  \
        Class                _kn_cls      = (CLASS);                                                                        \
        SEL                  _kn_sel      = (SELECTOR);                                                                     \
        const char *         _kn_types    = NULL;                                                                           \
        Method               _kn_method   = NULL;                                                                           \
        __block IMP          _kn_imp      = NULL;                                                                           \
        __block _KN_NEXT_IMP _kn_next_imp = NULL;                                                                           \
        if (_kn_cls && _kn_sel) {                                                                                           \
            _kn_method                    = KNClassGetOwnMethod(_kn_cls, _kn_sel);                                          \
            if (_kn_method) {                                                                                               \
                _kn_types                 = (TYPES);                                                                        \
                if (!_kn_types) {                                                                                           \
                    _kn_types             = method_getTypeEncoding(_kn_method);                                             \
                }                                                                                                           \
                _kn_imp                   = imp_implementationWithBlock(^__typeof(RETURN)(_KN_BLOCK_ARGS_(ARGS))
    
#define KN_CLASS_REPLACEMETHOD_PROCESS                                                                                      \
                    );                                                                                                      \
                _kn_next_imp              = (_KN_NEXT_IMP)class_replaceMethod(_kn_cls, _kn_sel, _kn_imp, _kn_types);        \
            }                                                                                                               \
        }

#define KN_CLASS_REPLACEMETHOD_END                                                                                          \
    } while(false);

#define KN_METHOD_OVERLOAD(ARGS...)                                                                                         \
    _kn_next_imp(ARGS)

/// class_addMethod(override)
///
#define KN_CLASS_OVERRIDEMETHOD_BEGIN(CLASS,SELECTOR,TYPES,RETURN,ARGS)                                                     \
    do {                                                                                                                    \
        OBJC_EXPORT void objc_msgSendSuper2(struct _kn_objc_super2 * super, SEL op, ...);                                   \
        typedef __typeof(RETURN)(*_KN_OBJC_MSGSENDSUPER)(_KN_OBJCSUPER_ARGS_(ARGS));                                        \
        Class                 _kn_cls               = (CLASS);                                                              \
        SEL                   _kn_sel               = (SELECTOR);                                                           \
        const char *          _kn_types             = NULL;                                                                 \
        Method                _kn_super_method      = NULL;                                                                 \
        __block IMP           _kn_imp               = NULL;                                                                 \
        __block bool          _kn_success           = false;                                                                \
        _KN_OBJC_MSGSENDSUPER _kn_objc_msgsendsuper = (_KN_OBJC_MSGSENDSUPER)objc_msgSendSuper2;                            \
        if (_kn_cls && _kn_sel) {                                                                                           \
            _kn_super_method                        = KNClassGetSuperMethod(_kn_cls, _kn_sel);                              \
            if (_kn_super_method) {                                                                                         \
                _kn_types                           = (TYPES);                                                              \
                if (!_kn_types) {                                                                                           \
                    _kn_types                       = method_getTypeEncoding(_kn_super_method);                             \
                }                                                                                                           \
                _kn_imp                             = imp_implementationWithBlock(^__typeof(RETURN)(_KN_BLOCK_ARGS_(ARGS))
    
#define KN_CLASS_OVERRIDEMETHOD_PROCESS                                                                                     \
                    );                                                                                                      \
                _kn_success                         = class_addMethod(_kn_cls, _kn_sel, _kn_imp, _kn_types);                \
            }                                                                                                               \
        }

#define KN_CLASS_OVERRIDEMETHOD_END                                                                                         \
    } while(false);

#define KN_MAKE_OBJC_SUPER(ID)                                                                                              \
    struct _kn_objc_super2 _kn_objc_super           = { (ID), _kn_cls };                                                    \

#define KN_METHOD_OVERRIDE(ARGS...)                                                                                         \
    _kn_objc_msgsendsuper(&_kn_objc_super, ARGS)

#endif /* KN_OBJC_NSOBJCRUNTIME_H */
