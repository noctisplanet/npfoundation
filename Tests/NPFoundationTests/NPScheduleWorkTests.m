//
//  NPScheduleWorkTests.m
//  npfoundation
//
//  Created by Jonathan Lee on 9/17/25.
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

@interface NPScheduleWorkTests : XCTestCase

@end

@implementation NPScheduleWorkTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testThrottle {
    NP_BLOCK(int) index = 0;
    XCTestExpectation *expectation = [self expectationWithDescription:@"TIME_FOREVER"];
    NPScheduleWork scheduleWork = NPDispatchScheduleThrottle(1, dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0), ^{
        index += 1;
        [expectation fulfill];
    });
    scheduleWork.resume();
    scheduleWork.resume();
    scheduleWork.resume();
    scheduleWork.resume();
    [self waitForExpectations:@[expectation] timeout:5];
    XCTAssertTrue(index = 1);
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
