//
//  NSObjCRuntime.h
//  npfoundation
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

#ifndef NP_OBJC_NSOBJCRUNTIME_H
#define NP_OBJC_NSOBJCRUNTIME_H

#include <objc/message.h>
#include <objc/runtime.h>
#include <NPFoundation/Definitions.h>

NP_CEXTERN_BEGIN

struct _np_objc_super2 {
    id _Nonnull receiver;
    Class _Nonnull current_class;
};

NP_EXTERN Method _Nullable KNClassGetOwnMethod(Class _Nullable cls, SEL _Nonnull name);

NP_EXTERN Method _Nullable KNClassGetSuperMethod(Class _Nullable cls, SEL _Nonnull name);

NP_CEXTERN_END

// A >> A
#define _NP_GUARD_(A) A

// (id self, SEL name, ) >> (id self, )
#define _NP_BLOCK_ARGS_(A1,A2,ARGS...) A1, ##ARGS
// (id self, SEL name, ) >> (id self, SEL name, )
#define _NP_FUNCTION_ARGS_(A1,A2,ARGS...) A1, A2, ##ARGS
// (id self, SEL name, ) >> (struct objc_super *super, SEL name, )
#define _NP_OBJCSUPER_ARGS_(A1,A2,ARGS...) _NP_GUARD_(struct _np_objc_super2 *super), A2, ##ARGS

// A >> A
#define NP_RETURN(TYPE) TYPE

// A1,A2, >> A1,A2
#define NP_ARGS(ARGS...) ARGS

/// class_addMethod
///
#define NP_CLASS_ADDMETHOD_BEGIN(CLASS,SELECTOR,TYPES,RETURN,ARGS)                                                          \
    do {                                                                                                                    \
        Class        _np_cls     = (CLASS);                                                                                 \
        SEL          _np_sel     = (SELECTOR);                                                                              \
        const char * _np_types   = NULL;                                                                                    \
        __block IMP  _np_imp     = NULL;                                                                                    \
        __block bool _np_success = false;                                                                                   \
        if (_np_cls && _np_sel) {                                                                                           \
            _np_types            = (TYPES);                                                                                 \
            _np_imp              = imp_implementationWithBlock(^__typeof(RETURN)(_NP_BLOCK_ARGS_(ARGS))
        
#define NP_CLASS_ADDMETHOD_PROCESS                                                                                          \
                );                                                                                                          \
            _np_success          = class_addMethod(_np_cls, _np_sel, _np_imp, _np_types);                                   \
        }

#define NP_CLASS_ADDMETHOD_END                                                                                              \
    } while(false);

/// class_replaceMethod
///
#define NP_CLASS_REPLACEMETHOD_BEGIN(CLASS,SELECTOR,TYPES,RETURN,ARGS)                                                      \
    do {                                                                                                                    \
        typedef __typeof(RETURN)(*_NP_NEXT_IMP)(_NP_FUNCTION_ARGS_(ARGS));                                                  \
        Class                _np_cls      = (CLASS);                                                                        \
        SEL                  _np_sel      = (SELECTOR);                                                                     \
        const char *         _np_types    = NULL;                                                                           \
        Method               _np_method   = NULL;                                                                           \
        __block IMP          _np_imp      = NULL;                                                                           \
        __block _NP_NEXT_IMP _np_next_imp = NULL;                                                                           \
        if (_np_cls && _np_sel) {                                                                                           \
            _np_method                    = KNClassGetOwnMethod(_np_cls, _np_sel);                                          \
            if (_np_method) {                                                                                               \
                _np_types                 = (TYPES);                                                                        \
                if (!_np_types) {                                                                                           \
                    _np_types             = method_getTypeEncoding(_np_method);                                             \
                }                                                                                                           \
                _np_imp                   = imp_implementationWithBlock(^__typeof(RETURN)(_NP_BLOCK_ARGS_(ARGS))
    
#define NP_CLASS_REPLACEMETHOD_PROCESS                                                                                      \
                    );                                                                                                      \
                _np_next_imp              = (_NP_NEXT_IMP)class_replaceMethod(_np_cls, _np_sel, _np_imp, _np_types);        \
            }                                                                                                               \
        }

#define NP_CLASS_REPLACEMETHOD_END                                                                                          \
    } while(false);

#define NP_METHOD_OVERLOAD(ARGS...)                                                                                         \
    _np_next_imp(ARGS)

/// class_addMethod(override)
///
#define NP_CLASS_OVERRIDEMETHOD_BEGIN(CLASS,SELECTOR,TYPES,RETURN,ARGS)                                                     \
    do {                                                                                                                    \
        OBJC_EXPORT void objc_msgSendSuper2(struct _np_objc_super2 * super, SEL op, ...);                                   \
        typedef __typeof(RETURN)(*_NP_OBJC_MSGSENDSUPER)(_NP_OBJCSUPER_ARGS_(ARGS));                                        \
        Class                 _np_cls               = (CLASS);                                                              \
        SEL                   _np_sel               = (SELECTOR);                                                           \
        const char *          _np_types             = NULL;                                                                 \
        Method                _np_super_method      = NULL;                                                                 \
        __block IMP           _np_imp               = NULL;                                                                 \
        __block bool          _np_success           = false;                                                                \
        _NP_OBJC_MSGSENDSUPER _np_objc_msgsendsuper = (_NP_OBJC_MSGSENDSUPER)objc_msgSendSuper2;                            \
        if (_np_cls && _np_sel) {                                                                                           \
            _np_super_method                        = KNClassGetSuperMethod(_np_cls, _np_sel);                              \
            if (_np_super_method) {                                                                                         \
                _np_types                           = (TYPES);                                                              \
                if (!_np_types) {                                                                                           \
                    _np_types                       = method_getTypeEncoding(_np_super_method);                             \
                }                                                                                                           \
                _np_imp                             = imp_implementationWithBlock(^__typeof(RETURN)(_NP_BLOCK_ARGS_(ARGS))
    
#define NP_CLASS_OVERRIDEMETHOD_PROCESS                                                                                     \
                    );                                                                                                      \
                _np_success                         = class_addMethod(_np_cls, _np_sel, _np_imp, _np_types);                \
            }                                                                                                               \
        }

#define NP_CLASS_OVERRIDEMETHOD_END                                                                                         \
    } while(false);

#define NP_MAKE_OBJC_SUPER(ID)                                                                                              \
    struct _np_objc_super2 _np_objc_super           = { (ID), _np_cls };                                                    \

#define NP_METHOD_OVERRIDE(ARGS...)                                                                                         \
    _np_objc_msgsendsuper(&_np_objc_super, ARGS)

#endif /* NP_OBJC_NSOBJCRUNTIME_H */
