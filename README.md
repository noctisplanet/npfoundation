NPFoundation
===

# Installation
## Installation with Swift Package Manager
```
dependencies: [
    .package(url: "https://github.com/nextpangea/npfoundation.git", branch: "main")
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
    NSLog(@"  class: %@", __cls);
    NSLog(@"    sel: %s", sel_getName(__sel));
    NSLog(@"  types: %s", __types);
    NSLog(@"success: %d", __success);
}
NP_CLASS_ADDMETHOD_END

```
Replace the original method of NSObject and its subclasses, where  
the original method can be called via `__next_imp`.
```Objective-C
NP_CLASS_REPLACEMETHOD_BEGIN([Object class], @selector(name), NULL, 
        NP_RETURN(NSString *), NP_ARGS(id self, SEL name)) {
    return @"NewObjectName";
}
NP_CLASS_REPLACEMETHOD_PROCESS {
    NSLog(@"  class: %@", __cls);
    NSLog(@"    sel: %s", sel_getName(__sel));
    NSLog(@"  types: %s", __types);
    NSLog(@"   func: %p", __next_imp);
}
NP_CLASS_REPLACEMETHOD_END
```
