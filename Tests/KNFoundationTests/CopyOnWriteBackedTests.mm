//
//  CopyOnWriteBackedTests.m
//  knfoundation
//
//  Created by Jonathan Lee on 8/11/25.
//

#import <XCTest/XCTest.h>
#import <KNFoundation/KNFoundation.h>

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

using namespace KN;

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
    cow1->ctest();
    XCTAssertTrue(cow1.retainCount() == 1);
    cow2->test();
    XCTAssertTrue(cow2.retainCount() == 1);
}

@end
