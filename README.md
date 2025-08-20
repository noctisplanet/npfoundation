NPFoundation
===

# Installation
## Installation with Swift Package Manager
```Swift
dependencies: [
    .package(url: "https://github.com/noctisplanet/npfoundation.git", branch: "main")
]
```

# Usage

## objc
### NSObjCRuntime
Add new methods to NSObject and its subclasses: place method implementations  
after BEGIN, then read method addition success status after PROCESS.
```Objective-C
#import <NPFoundation/NPFoundation.h>

NP_CLASS_ADDMETHOD_BEGIN([Object class], @selector(name), NULL, 
        NP_RETURN(NSString *), NP_ARGS(id self, SEL name)) {
    return @"ObjectName";
}
NP_CLASS_ADDMETHOD_PROCESS {
    NSLog(@"  class: %@", _np_cls);
    NSLog(@"    sel: %s", sel_getName(_np_sel));
    NSLog(@"  types: %s", _np_types);
    NSLog(@"success: %d", _np_success);
}
NP_CLASS_ADDMETHOD_END

```
Replace the original method of NSObject and its subclasses, where  
the original method can be called via `_np_next_imp`.
```Objective-C
NP_CLASS_REPLACEMETHOD_BEGIN([Object class], @selector(name), NULL, 
        NP_RETURN(NSString *), NP_ARGS(id self, SEL name)) {
    NSString *name = NP_METHOD_OVERLOAD(self, _np_sel);
    return name;
}
NP_CLASS_REPLACEMETHOD_PROCESS {
    NSLog(@"   class: %@", _np_cls);
    NSLog(@"     sel: %s", sel_getName(_np_sel));
    NSLog(@"   types: %s", _np_types);
    NSLog(@"NEXT_IMP: %p", _np_next_imp);
}
NP_CLASS_REPLACEMETHOD_END
```

Rewrite the method of the superclass, simulating the call to [super method] 
using `NP_MAKE_OBJC_SUPER` & `NP_METHOD_OVERRIDE`.
```Objective-C
NP_CLASS_OVERRIDEMETHOD_BEGIN([Subobject class], @selector(name), NULL, 
        NP_RETURN(NSString *), NP_ARGS(id self, SEL name)) {
    NP_MAKE_OBJC_SUPER(self);
    NSString *name = NP_METHOD_OVERRIDE(_np_sel);
    return name;
}
NP_CLASS_OVERRIDEMETHOD_PROCESS {
    NSLog(@"   class: %@", _np_cls);
    NSLog(@"     sel: %s", sel_getName(_np_sel));
    NSLog(@"   types: %s", _np_types);
    NSLog(@"  method: %p", _np_super_method);
}
NP_CLASS_OVERRIDEMETHOD_END
```
