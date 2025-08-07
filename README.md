KNFoundation
===

# Installation
## Installation with Swift Package Manager
```Swift
dependencies: [
    .package(url: "https://github.com/kainian/knfoundation.git", branch: "main")
]
```

# Usage

## objc
### NSObjCRuntime
Add new methods to NSObject and its subclasses: place method implementations  
after BEGIN, then read method addition success status after PROCESS.
```Objective-C
#import <KNFoundation/KNFoundation.h>

KN_CLASS_ADDMETHOD_BEGIN([Object class], @selector(name), NULL, 
        KN_RETURN(NSString *), KN_ARGS(id self, SEL name)) {
    return @"ObjectName";
}
KN_CLASS_ADDMETHOD_PROCESS {
    NSLog(@"  class: %@", _kn_cls);
    NSLog(@"    sel: %s", sel_getName(_kn_sel));
    NSLog(@"  types: %s", _kn_types);
    NSLog(@"success: %d", _kn_success);
}
KN_CLASS_ADDMETHOD_END

```
Replace the original method of NSObject and its subclasses, where  
the original method can be called via `_kn_next_imp`.
```Objective-C
KN_CLASS_REPLACEMETHOD_BEGIN([Object class], @selector(name), NULL, 
        KN_RETURN(NSString *), KN_ARGS(id self, SEL name)) {
    NSString *name = KN_METHOD_OVERLOAD(self, _kn_sel);
    return name;
}
KN_CLASS_REPLACEMETHOD_PROCESS {
    NSLog(@"   class: %@", _kn_cls);
    NSLog(@"     sel: %s", sel_getName(_kn_sel));
    NSLog(@"   types: %s", _kn_types);
    NSLog(@"NEXT_IMP: %p", _kn_next_imp);
}
KN_CLASS_REPLACEMETHOD_END
```

Rewrite the method of the superclass, simulating the call to [super method] 
using `KN_MAKE_OBJC_SUPER` & `KN_METHOD_OVERRIDE`.
```Objective-C
KN_CLASS_OVERRIDEMETHOD_BEGIN([Subobject class], @selector(name), NULL, 
        KN_RETURN(NSString *), KN_ARGS(id self, SEL name)) {
    KN_MAKE_OBJC_SUPER(self);
    NSString *name = KN_METHOD_OVERRIDE(_kn_sel);
    return name;
}
KN_CLASS_OVERRIDEMETHOD_PROCESS {
    NSLog(@"   class: %@", _kn_cls);
    NSLog(@"     sel: %s", sel_getName(_kn_sel));
    NSLog(@"   types: %s", _kn_types);
    NSLog(@"  method: %p", _kn_super_method);
}
KN_CLASS_OVERRIDEMETHOD_END
```
