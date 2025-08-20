//
//  NSObjCRuntimeTests.m
//  npfoundation
//
//  Created by Jonathan Lee on 6/14/25.
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

#import <XCTest/XCTest.h>
#import <NPFoundation/NPFoundation.h>

@protocol KNObjectProtocol <NSObject>

- (void)addMethod;

- (NSString *)addMethod:(NSString *)newValue;

- (int64_t)addMethodSum:(int64_t)x y:(int64_t)y z:(int64_t)z;

@end

@interface KNObject : NSObject

@property (nonatomic, strong) NSString *npObject;

@end

@interface KNSuperObject : KNObject

@property (nonatomic, strong) NSString *superObject;

@end

@interface KNSubObject : KNSuperObject

@property (nonatomic, strong) NSString *subObject;

@end

@implementation KNObject

- (void)overrideKNObjectMethod {
    self.npObject = @"KNObjectMethod";
}

- (NSString *)overrideMethod:(NSString *)newValue {
    return newValue;
}

- (int64_t)overrideMethodSum:(int64_t)x y:(int64_t)y z:(int64_t)z {
    return x + y + z;
}

+ (void)overrideKNObjectMethod {
    
}

+ (NSString *)overrideMethod:(NSString *)newValue {
    return newValue;
}

+ (int64_t)overrideMethodSum:(int64_t)x y:(int64_t)y z:(int64_t)z {
    return x + y + z;
}

@end

@implementation KNSuperObject

- (void)replaceMethod {
    self.superObject = @"KNSuperObject";
}

- (NSString *)replaceMethod:(NSString *)newValue {
    return newValue;
}

- (int64_t)replaceMethodSum:(int64_t)x y:(int64_t)y z:(int64_t)z {
    return x + y + z;
}

- (void)overrideKNSuperObject {
    self.superObject = @"KNSuperObject";
}

+ (void)overrideKNSuperObject {
    
}

@end

@implementation KNSubObject

- (void)overrideKNSubObject {
    self.subObject = @"KNSubObject";
}

+ (void)overrideKNSubObject {
    
}

@end

@interface NSObjCRuntimeTests : XCTestCase

@end

@implementation NSObjCRuntimeTests

- (void)setUp {
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testClassOverrideMethod {
    __block NSString *value = nil;
    NP_CLASS_OVERRIDEMETHOD_BEGIN(object_getClass(KNSubObject.class), @selector(overrideKNObjectMethod), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        value = @"TestValue";
        NP_MAKE_OBJC_SUPER(self);
        NP_METHOD_OVERRIDE(_np_sel);
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    [KNSubObject overrideKNObjectMethod];
    XCTAssertEqual(@"TestValue", value);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(object_getClass(KNSubObject.class), @selector(overrideKNSuperObject), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        value = @"TestValue:";
        NP_MAKE_OBJC_SUPER(self);
        NP_METHOD_OVERRIDE(_np_sel);
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    [KNSubObject overrideKNSuperObject];
    XCTAssertEqual(@"TestValue:", value);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(object_getClass(KNSuperObject.class), @selector(overrideMethod:), NULL, NP_RETURN(NSString *), NP_ARGS(id self, SEL name, NSString *newValue)) {
        NP_MAKE_OBJC_SUPER(self);
        XCTAssertEqual(newValue, NP_METHOD_OVERRIDE(_np_sel, newValue));
        value = @"TestValue:NewValue";
        return @"ReturnValue";
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    XCTAssertEqual(@"ReturnValue", [KNSuperObject overrideMethod:@"NewValue"]);
    XCTAssertEqual(@"TestValue:NewValue", value);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(object_getClass(KNSuperObject.class), @selector(overrideMethodSum:y:z:), NULL, NP_RETURN(int64_t), NP_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        NP_MAKE_OBJC_SUPER(self);
        XCTAssertEqual(x + y + z, NP_METHOD_OVERRIDE(_np_sel, x, y, z));
        value = @"TestValue:Sum";
        return x + y + z + 2;
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    
    XCTAssertEqual(20 + 21 + 22 + 2, [KNSuperObject overrideMethodSum:20 y:21 z:22]);
    XCTAssertEqual(@"TestValue:Sum", value);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(object_getClass(KNSubObject.class), @selector(overrideKNSubObject), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        NP_MAKE_OBJC_SUPER(self);
        NP_METHOD_OVERRIDE(_np_sel);
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertFalse(_np_types);
        XCTAssertFalse(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    [KNSubObject overrideKNSubObject];
}

- (void)testOverrideMethod {
    __block NSString *value = nil;
    KNSubObject *objc = [KNSubObject new];
    NP_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideKNObjectMethod), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        value = @"TestValue";
        NP_MAKE_OBJC_SUPER(self);
        NP_METHOD_OVERRIDE(_np_sel);
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    [objc overrideKNObjectMethod];
    XCTAssertEqual(@"TestValue", value);
    XCTAssertEqual(@"KNObjectMethod", objc.npObject);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideKNSuperObject), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        value = @"TestValue:";
        NP_MAKE_OBJC_SUPER(self);
        NP_METHOD_OVERRIDE(_np_sel);
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    [objc overrideKNSuperObject];
    XCTAssertEqual(@"TestValue:", value);
    XCTAssertEqual(@"KNSuperObject", objc.superObject);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideMethod:), NULL, NP_RETURN(NSString *), NP_ARGS(id self, SEL name, NSString *newValue)) {
        NP_MAKE_OBJC_SUPER(self);
        XCTAssertEqual(newValue, NP_METHOD_OVERRIDE(_np_sel, newValue));
        value = @"TestValue:NewValue";
        return @"ReturnValue";
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    XCTAssertEqual(@"ReturnValue", [objc overrideMethod:@"NewValue"]);
    XCTAssertEqual(@"TestValue:NewValue", value);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideMethodSum:y:z:), NULL, NP_RETURN(int64_t), NP_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        NP_MAKE_OBJC_SUPER(self);
        XCTAssertEqual(x + y + z, NP_METHOD_OVERRIDE(_np_sel, x, y, z));
        value = @"TestValue:Sum";
        return x + y + z + 2;
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    
    XCTAssertEqual(20 + 21 + 22 + 2, [objc overrideMethodSum:20 y:21 z:22]);
    XCTAssertEqual(@"TestValue:Sum", value);
    
    NP_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideKNSubObject), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        NP_MAKE_OBJC_SUPER(self);
        NP_METHOD_OVERRIDE(_np_sel);
    }
    NP_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"  method: %p", _np_super_method);
        XCTAssertFalse(_np_types);
        XCTAssertFalse(_np_super_method);
    }
    NP_CLASS_OVERRIDEMETHOD_END
    [objc overrideKNSubObject];
    XCTAssertEqual(@"KNSubObject", objc.subObject);
}

- (void)testReplaceMethod {
    __block NSString *value = nil;
    KNSuperObject *obj = [KNSuperObject new];
    NP_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(replaceMethod), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        value = @"TestValue";
        NP_METHOD_OVERLOAD(self, _np_sel);
    }
    NP_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"NEXT_IMP: %p", _np_next_imp);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_next_imp);
    }
    NP_CLASS_REPLACEMETHOD_END
    [obj replaceMethod];
    XCTAssertEqual(@"TestValue", value);
    XCTAssertEqual(@"KNSuperObject", obj.superObject);
    
    NP_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(replaceMethod:), NULL, NP_RETURN(NSString *), NP_ARGS(id self, SEL name, NSString *newValue)) {
        value = @"TestValue:";
        XCTAssertEqual(newValue, NP_METHOD_OVERLOAD(self, _np_sel, newValue));
        return @"ReturnValue";
    }
    NP_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"NEXT_IMP: %p", _np_next_imp);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_next_imp);
    }
    NP_CLASS_REPLACEMETHOD_END
    XCTAssertEqual(@"ReturnValue", [obj replaceMethod:@"argValue"]);
    XCTAssertEqual(@"TestValue:", value);
    
    NP_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(replaceMethodSum:y:z:), NULL, NP_RETURN(int64_t), NP_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        value = @"replaceMethodSum:y:z:";
        XCTAssertEqual(x + y + z, NP_METHOD_OVERLOAD(self, _np_sel, x, y, z));
        return x + y + z + 1;
    }
    NP_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"NEXT_IMP: %p", _np_next_imp);
        XCTAssertTrue(_np_types);
        XCTAssertTrue(_np_next_imp);
    }
    NP_CLASS_REPLACEMETHOD_END
    XCTAssertEqual(10 + 11 + 12 + 1, [obj replaceMethodSum:10 y:11 z:12]);
    XCTAssertEqual(@"replaceMethodSum:y:z:", value);
    
    NP_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(setNpObject:), NULL, NP_RETURN(NSString *), NP_ARGS(id self, SEL name, NSString *newValue)) {
        return NP_METHOD_OVERLOAD(self, _np_sel, newValue);
    }
    NP_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _np_cls);
        NSLog(@"     sel: %s", sel_getName(_np_sel));
        NSLog(@"   types: %s", _np_types);
        NSLog(@"NEXT_IMP: %p", _np_next_imp);
        XCTAssertFalse(_np_types);
        XCTAssertFalse(_np_next_imp);
    }
    NP_CLASS_REPLACEMETHOD_END
}

- (void)testAddMethod {
    __block NSString *value = nil;
    KNObject *obj = [KNObject new];
    NP_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(addMethod), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        value = @"TestValue";
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _np_cls);
        NSLog(@"    sel: %s", sel_getName(_np_sel));
        NSLog(@"  types: %s", _np_types);
        NSLog(@"success: %d", _np_success);
        XCTAssertTrue(_np_success);
    }
    NP_CLASS_ADDMETHOD_END
    XCTAssertNil(value);
    [(id<KNObjectProtocol>)obj addMethod];
    XCTAssertEqual(@"TestValue", value);
    
    NP_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(addMethod:), NULL, NP_RETURN(NSString *), NP_ARGS(id self, SEL name, NSString *newValue)) {
        value = newValue;
        return @"ReturnTestValue";
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _np_cls);
        NSLog(@"    sel: %s", sel_getName(_np_sel));
        NSLog(@"  types: %s", _np_types);
        NSLog(@"success: %d", _np_success);
        XCTAssertTrue(_np_success);
    }
    NP_CLASS_ADDMETHOD_END
    NSString *returnValue = [(id<KNObjectProtocol>)obj addMethod:@"argValue"];
    XCTAssertEqual(@"ReturnTestValue", returnValue);
    XCTAssertEqual(@"argValue", value);
    
    NP_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(addMethodSum:y:z:), NULL, NP_RETURN(int64_t), NP_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        value = @"addMethodSum:y:z:";
        return x + y + z;
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _np_cls);
        NSLog(@"    sel: %s", sel_getName(_np_sel));
        NSLog(@"  types: %s", _np_types);
        NSLog(@"success: %d", _np_success);
        XCTAssertTrue(_np_success);
    }
    NP_CLASS_ADDMETHOD_END
    int64_t sum = [(id<KNObjectProtocol>)obj addMethodSum:1 y:2 z:3];
    XCTAssertEqual(1 + 2 + 3, sum);
    XCTAssertEqual(@"addMethodSum:y:z:", value);
    
    NP_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(npObject), NULL, NP_RETURN(NSString *), NP_ARGS(id self, SEL name)) {
        return @"";
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _np_cls);
        NSLog(@"    sel: %s", sel_getName(_np_sel));
        NSLog(@"  types: %s", _np_types);
        NSLog(@"success: %d", _np_success);
        XCTAssertFalse(_np_success);
    }
    NP_CLASS_ADDMETHOD_END
    
    NP_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(setNpObject:), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name, NSString *newValue)) {
        
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _np_cls);
        NSLog(@"    sel: %s", sel_getName(_np_sel));
        NSLog(@"  types: %s", _np_types);
        NSLog(@"success: %d", _np_success);
        XCTAssertFalse(_np_success);
    }
    NP_CLASS_ADDMETHOD_END
}

@end
