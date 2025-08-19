//
//  NSObjCRuntime.h
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

#include <KNFoundation/objc.h>
#include <objc/message.h>
#include <objc/runtime.h>

Method _Nullable KNClassGetOwnMethod(Class _Nullable cls, SEL _Nonnull name) {
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

Method _Nullable KNClassGetSuperMethod(Class _Nullable cls, SEL _Nonnull name) {
    Class super = class_getSuperclass(cls);
    if (!super)
        return NULL;
    if (super == cls)
        return NULL;
    return class_getInstanceMethod(super, name);
}
