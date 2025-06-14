//
//  NSObjCRuntimeTests.m
//  npfoundation
//
//  Created by Jonathan Lee on 6/14/25.
//

#import <XCTest/XCTest.h>
#import <NPFoundation/NPFoundation.h>

@protocol NSObjCRuntimeTestsProtocol <NSObject>

- (void)_testAddMethod1;

- (double)_testAddMethod2;

- (int64_t)_testAddMethod3:(int64_t)x y:(int64_t)y z:(int64_t)z;

@end

@interface NSObjCRuntimeTests : XCTestCase

@property (nonatomic, assign) double _testValue;

@end

@implementation NSObjCRuntimeTests

- (void)setUp {
    self._testValue = 0;
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testAddMethod {
    NSObjCRuntimeTests *tests = self;
    id<NSObjCRuntimeTestsProtocol> prot = (id<NSObjCRuntimeTestsProtocol>)self;
    
    NP_CLASS_ADDMETHOD_BEGIN(tests.class, @selector(_testAddMethod1), NULL, NP_RETURN(void), NP_ARGS(id self, SEL name)) {
        tests._testValue = 10;
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", __cls);
        NSLog(@"    sel: %s", sel_getName(__sel));
        NSLog(@"  types: %s", __types);
        NSLog(@"success: %d", __success);
    }
    NP_CLASS_ADDMETHOD_END
    XCTAssertTrue(tests._testValue == 0);
    [prot _testAddMethod1];
    XCTAssertTrue(tests._testValue == 10);
    
    NP_CLASS_ADDMETHOD_BEGIN(tests.class, @selector(_testAddMethod2), NULL, NP_RETURN(double), NP_ARGS(id self, SEL name)) {
        tests._testValue = 20;
        return 3.14;
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", __cls);
        NSLog(@"    sel: %s", sel_getName(__sel));
        NSLog(@"  types: %s", __types);
        NSLog(@"success: %d", __success);
    }
    NP_CLASS_ADDMETHOD_END
    XCTAssertTrue([prot _testAddMethod2] == 3.14);
    XCTAssertTrue(tests._testValue == 20);
    
    NP_CLASS_ADDMETHOD_BEGIN(tests.class, @selector(_testAddMethod3:y:z:), NULL, NP_RETURN(int64_t), NP_ARGS(id self, SEL name, int64_t x, int64_t y, int64_t z)) {
        tests._testValue = x + y + z;
        XCTAssertTrue(x == 1);
        XCTAssertTrue(y == 2);
        XCTAssertTrue(z == 3);
        return x + y +z;
    }
    NP_CLASS_ADDMETHOD_PROCESS {
        NSLog(@"  class: %@", __cls);
        NSLog(@"    sel: %s", sel_getName(__sel));
        NSLog(@"  types: %s", __types);
        NSLog(@"success: %d", __success);
    }
    NP_CLASS_ADDMETHOD_END
    XCTAssertTrue([prot _testAddMethod3:1 y:2 z:3] == 1 + 2 + 3);
    XCTAssertTrue(tests._testValue == 1 + 2 + 3);
}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
