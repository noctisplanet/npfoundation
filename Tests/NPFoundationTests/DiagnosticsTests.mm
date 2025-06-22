//
//  DiagnosticsTests.mm
//  npfoundation
//
//  Created by Jonathan Lee on 6/22/25.
//

#import <XCTest/XCTest.h>
#import <NPFoundation/NPFoundation.h>

using namespace NP;

@interface DiagnosticsTests : XCTestCase

@end

@implementation DiagnosticsTests

- (void)testNode {
    Diagnostics diagnostics;
    diagnostics.note("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

- (void)testPrefixNode {
    Diagnostics diagnostics{"test"};
    diagnostics.note("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

- (void)testWarning {
    Diagnostics diagnostics;
    diagnostics.warning("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

- (void)testPrefixWarning {
    Diagnostics diagnostics{"test"};
    diagnostics.warning("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

- (void)testVerboseWarning {
    Diagnostics diagnostics{"test", stderr, true};
    diagnostics.warning("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

- (void)testError {
    Diagnostics diagnostics;
    diagnostics.error("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertTrue(diagnostics.hasError());
    XCTAssertFalse(diagnostics.noError());
    diagnostics.clearError();
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

- (void)testPrefixError {
    Diagnostics diagnostics{"test"};
    diagnostics.error("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertTrue(diagnostics.hasError());
    XCTAssertFalse(diagnostics.noError());
    diagnostics.clearError();
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

- (void)testVerboseError {
    Diagnostics diagnostics{"test", stderr, true};
    diagnostics.error("%fs", CFAbsoluteTimeGetCurrent());
    XCTAssertTrue(diagnostics.hasError());
    XCTAssertFalse(diagnostics.noError());
    diagnostics.clearError();
    XCTAssertFalse(diagnostics.hasError());
    XCTAssertTrue(diagnostics.noError());
}

@end
