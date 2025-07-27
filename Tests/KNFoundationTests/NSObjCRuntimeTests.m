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
#import <KNFoundation/KNFoundation.h>

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

@end

@implementation KNSubObject

- (void)overrideKNSubObject {
    self.subObject = @"KNSubObject";
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

- (void)testOverrideMethod {
    __block NSString *value = nil;
    KNSubObject *objc = [KNSubObject new];
    KN_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideKNObjectMethod), NULL, KN_RETURN(void), KN_ARGS(id self, SEL name)) {
        value = @"TestValue";
        KN_MAKE_OBJC_SUPER(self);
        KN_METHOD_OVERRIDE(_kn_sel);
    }
    KN_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"  method: %p", _kn_super_method);
        XCTAssertTrue(_kn_types);
        XCTAssertTrue(_kn_super_method);
    }
    KN_CLASS_OVERRIDEMETHOD_END
    [objc overrideKNObjectMethod];
    XCTAssertEqual(@"TestValue", value);
    XCTAssertEqual(@"KNObjectMethod", objc.npObject);
    
    KN_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideKNSuperObject), NULL, KN_RETURN(void), KN_ARGS(id self, SEL name)) {
        value = @"TestValue:";
        KN_MAKE_OBJC_SUPER(self);
        KN_METHOD_OVERRIDE(_kn_sel);
    }
    KN_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"  method: %p", _kn_super_method);
        XCTAssertTrue(_kn_types);
        XCTAssertTrue(_kn_super_method);
    }
    KN_CLASS_OVERRIDEMETHOD_END
    [objc overrideKNSuperObject];
    XCTAssertEqual(@"TestValue:", value);
    XCTAssertEqual(@"KNSuperObject", objc.superObject);
    
    KN_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideMethod:), NULL, KN_RETURN(NSString *), KN_ARGS(id self, SEL name, NSString *newValue)) {
        KN_MAKE_OBJC_SUPER(self);
        XCTAssertEqual(newValue, KN_METHOD_OVERRIDE(_kn_sel, newValue));
        value = @"TestValue:NewValue";
        return @"ReturnValue";
    }
    KN_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"  method: %p", _kn_super_method);
        XCTAssertTrue(_kn_types);
        XCTAssertTrue(_kn_super_method);
    }
    KN_CLASS_OVERRIDEMETHOD_END
    XCTAssertEqual(@"ReturnValue", [objc overrideMethod:@"NewValue"]);
    XCTAssertEqual(@"TestValue:NewValue", value);
    
    KN_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideMethodSum:y:z:), NULL, KN_RETURN(int64_t), KN_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        KN_MAKE_OBJC_SUPER(self);
        XCTAssertEqual(x + y + z, KN_METHOD_OVERRIDE(_kn_sel, x, y, z));
        value = @"TestValue:Sum";
        return x + y + z + 2;
    }
    KN_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"  method: %p", _kn_super_method);
        XCTAssertTrue(_kn_types);
        XCTAssertTrue(_kn_super_method);
    }
    KN_CLASS_OVERRIDEMETHOD_END
    
    XCTAssertEqual(20 + 21 + 22 + 2, [objc overrideMethodSum:20 y:21 z:22]);
    XCTAssertEqual(@"TestValue:Sum", value);
    
    KN_CLASS_OVERRIDEMETHOD_BEGIN(KNSubObject.class, @selector(overrideKNSubObject), NULL, KN_RETURN(void), KN_ARGS(id self, SEL name)) {
        KN_MAKE_OBJC_SUPER(self);
        KN_METHOD_OVERRIDE(_kn_sel);
    }
    KN_CLASS_OVERRIDEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"  method: %p", _kn_super_method);
        XCTAssertFalse(_kn_types);
        XCTAssertFalse(_kn_super_method);
    }
    KN_CLASS_OVERRIDEMETHOD_END
    [objc overrideKNSubObject];
    XCTAssertEqual(@"KNSubObject", objc.subObject);
}

- (void)testReplaceMethod {
    __block NSString *value = nil;
    KNSuperObject *obj = [KNSuperObject new];
    KN_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(replaceMethod), NULL, KN_RETURN(void), KN_ARGS(id self, SEL name)) {
        value = @"TestValue";
        KN_METHOD_OVERLOAD(self, _kn_sel);
    }
    KN_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"NEXT_IMP: %p", _kn_next_imp);
        XCTAssertTrue(_kn_types);
        XCTAssertTrue(_kn_next_imp);
    }
    KN_CLASS_REPLACEMETHOD_END
    [obj replaceMethod];
    XCTAssertEqual(@"TestValue", value);
    XCTAssertEqual(@"KNSuperObject", obj.superObject);
    
    KN_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(replaceMethod:), NULL, KN_RETURN(NSString *), KN_ARGS(id self, SEL name, NSString *newValue)) {
        value = @"TestValue:";
        XCTAssertEqual(newValue, KN_METHOD_OVERLOAD(self, _kn_sel, newValue));
        return @"ReturnValue";
    }
    KN_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"NEXT_IMP: %p", _kn_next_imp);
        XCTAssertTrue(_kn_types);
        XCTAssertTrue(_kn_next_imp);
    }
    KN_CLASS_REPLACEMETHOD_END
    XCTAssertEqual(@"ReturnValue", [obj replaceMethod:@"argValue"]);
    XCTAssertEqual(@"TestValue:", value);
    
    KN_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(replaceMethodSum:y:z:), NULL, KN_RETURN(int64_t), KN_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        value = @"replaceMethodSum:y:z:";
        XCTAssertEqual(x + y + z, KN_METHOD_OVERLOAD(self, _kn_sel, x, y, z));
        return x + y + z + 1;
    }
    KN_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"NEXT_IMP: %p", _kn_next_imp);
        XCTAssertTrue(_kn_types);
        XCTAssertTrue(_kn_next_imp);
    }
    KN_CLASS_REPLACEMETHOD_END
    XCTAssertEqual(10 + 11 + 12 + 1, [obj replaceMethodSum:10 y:11 z:12]);
    XCTAssertEqual(@"replaceMethodSum:y:z:", value);
    
    KN_CLASS_REPLACEMETHOD_BEGIN(KNSuperObject.class, @selector(setNpObject:), NULL, KN_RETURN(NSString *), KN_ARGS(id self, SEL name, NSString *newValue)) {
        return KN_METHOD_OVERLOAD(self, _kn_sel, newValue);
    }
    KN_CLASS_REPLACEMETHOD_PROCESS {
        NSLog(@"   class: %@", _kn_cls);
        NSLog(@"     sel: %s", sel_getName(_kn_sel));
        NSLog(@"   types: %s", _kn_types);
        NSLog(@"NEXT_IMP: %p", _kn_next_imp);
        XCTAssertFalse(_kn_types);
        XCTAssertFalse(_kn_next_imp);
    }
    KN_CLASS_REPLACEMETHOD_END
}

- (void)testAddMethod {
    __block NSString *value = nil;
    KNObject *obj = [KNObject new];
    KN_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(addMethod), NULL, KN_RETURN(void), KN_ARGS(id self, SEL name)) {
        value = @"TestValue";
    }
    KN_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _kn_cls);
        NSLog(@"    sel: %s", sel_getName(_kn_sel));
        NSLog(@"  types: %s", _kn_types);
        NSLog(@"success: %d", _kn_success);
        XCTAssertTrue(_kn_success);
    }
    KN_CLASS_ADDMETHOD_END
    XCTAssertNil(value);
    [(id<KNObjectProtocol>)obj addMethod];
    XCTAssertEqual(@"TestValue", value);
    
    KN_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(addMethod:), NULL, KN_RETURN(NSString *), KN_ARGS(id self, SEL name, NSString *newValue)) {
        value = newValue;
        return @"ReturnTestValue";
    }
    KN_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _kn_cls);
        NSLog(@"    sel: %s", sel_getName(_kn_sel));
        NSLog(@"  types: %s", _kn_types);
        NSLog(@"success: %d", _kn_success);
        XCTAssertTrue(_kn_success);
    }
    KN_CLASS_ADDMETHOD_END
    NSString *returnValue = [(id<KNObjectProtocol>)obj addMethod:@"argValue"];
    XCTAssertEqual(@"ReturnTestValue", returnValue);
    XCTAssertEqual(@"argValue", value);
    
    KN_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(addMethodSum:y:z:), NULL, KN_RETURN(int64_t), KN_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        value = @"addMethodSum:y:z:";
        return x + y + z;
    }
    KN_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _kn_cls);
        NSLog(@"    sel: %s", sel_getName(_kn_sel));
        NSLog(@"  types: %s", _kn_types);
        NSLog(@"success: %d", _kn_success);
        XCTAssertTrue(_kn_success);
    }
    KN_CLASS_ADDMETHOD_END
    int64_t sum = [(id<KNObjectProtocol>)obj addMethodSum:1 y:2 z:3];
    XCTAssertEqual(1 + 2 + 3, sum);
    XCTAssertEqual(@"addMethodSum:y:z:", value);
    
    KN_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(npObject), NULL, KN_RETURN(NSString *), KN_ARGS(id self, SEL name)) {
        return @"";
    }
    KN_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _kn_cls);
        NSLog(@"    sel: %s", sel_getName(_kn_sel));
        NSLog(@"  types: %s", _kn_types);
        NSLog(@"success: %d", _kn_success);
        XCTAssertFalse(_kn_success);
    }
    KN_CLASS_ADDMETHOD_END
    
    KN_CLASS_ADDMETHOD_BEGIN(KNObject.class, @selector(setNpObject:), NULL, KN_RETURN(void), KN_ARGS(id self, SEL name, NSString *newValue)) {
        
    }
    KN_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", _kn_cls);
        NSLog(@"    sel: %s", sel_getName(_kn_sel));
        NSLog(@"  types: %s", _kn_types);
        NSLog(@"success: %d", _kn_success);
        XCTAssertFalse(_kn_success);
    }
    KN_CLASS_ADDMETHOD_END
}

@end
