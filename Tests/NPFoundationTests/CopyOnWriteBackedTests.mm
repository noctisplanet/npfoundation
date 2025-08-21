//
//  CopyOnWriteBackedTests.m
//  npfoundation
//
//  Created by Jonathan Lee on 8/11/25.
//

#import <XCTest/XCTest.h>
#import <NPFoundation/NPFoundation.h>

struct DataSources {
    
    DataSources() {
        
    }
    
    DataSources(DataSources &ds) {
        
    }
    
    ~DataSources() {
        
    }
    
    void ctest() const {
        
    }
  
    void test() {
        
    }
};

using namespace NP;

@interface CopyOnWriteBackedTests : XCTestCase

@end

@implementation CopyOnWriteBackedTests

- (void)testMake {
    const auto cow = CopyOnWriteMake<DataSources>();
    XCTAssertTrue(cow.get() != nullptr);
}

- (void)testRead {
    const auto cow1 = CopyOnWriteMake<DataSources>();
    const auto cow2 = cow1;
    XCTAssertTrue(cow1.get() == cow2.get());
    XCTAssertTrue(cow1.retainCount() == 2);
    XCTAssertTrue(cow2.retainCount() == 2);
}

- (void)testWrite {
    auto cow1 = CopyOnWriteMake<DataSources>();
    auto cow2 = cow1;
    XCTAssertTrue(cow1.get() == cow2.get());
    XCTAssertTrue(cow1.retainCount() == 2);
    XCTAssertTrue(cow2.retainCount() == 2);
    cow1.acquireUnique()->ctest();
    XCTAssertTrue(cow1.retainCount() == 1);
    cow2.acquireUnique()->test();
    XCTAssertTrue(cow2.retainCount() == 1);
}

@end
