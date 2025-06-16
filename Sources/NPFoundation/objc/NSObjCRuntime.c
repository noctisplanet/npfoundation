//
//  NSObjCRuntime.h
//  npfoundation
//
//  Created by Jonathan Lee on 5/6/25.
//

#include <NPFoundation/objc/NSObjCRuntime.h>

Method _Nullable NPClassGetOwnMethod(Class _Nullable cls, SEL _Nonnull name) {
    unsigned int outCount = 0;
    Method *methods = class_copyMethodList(cls, &outCount);
    if (methods) {
        for (int idx = 0; idx < outCount; idx ++) {
            Method method = methods[idx];
            SEL sel = method_getName(method);
            if (sel_isEqual(sel, name)) {
                free(methods);
                return method;
            }
        }
        free(methods);
    }
    return NULL;
}

Method _Nullable NPClassGetSuperMethod(Class _Nullable cls, SEL _Nonnull name) {
    Class super = class_getSuperclass(cls);
    if (!super)
        return NULL;
    if (super == cls)
        return NULL;
    return class_getInstanceMethod(super, name);
}
