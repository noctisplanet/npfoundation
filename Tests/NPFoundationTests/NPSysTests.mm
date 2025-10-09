//
//  NPSysTests.m
//  npfoundation
//
//  Created by Jonathan Lee on 10/7/25.
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

@interface NPSysTests : XCTestCase

@property (nonatomic, strong) NSString *temporaryDirectory;
@property (nonatomic, strong) NSString *testFile;

@end

@implementation NPSysTests

- (void)setUp {
    [super setUp];
    self.temporaryDirectory = NSTemporaryDirectory();
    self.testFile = [self.temporaryDirectory stringByAppendingPathComponent:NSUUID.UUID.UUIDString];
    [[NSFileManager defaultManager] removeItemAtPath:self.testFile error:nil];
}

- (void)tearDown {
    [[NSFileManager defaultManager] removeItemAtPath:self.testFile error:nil];
    [super tearDown];
}

- (void)testOpenCreateNewFile {
    NP::Diagnostics diag;
    int fd = NP::Sys::open(diag, [self.testFile UTF8String], O_CREAT | O_RDWR, 0644);
    XCTAssertFalse(diag.hasError());
    XCTAssertTrue(fd >= 0);
    XCTAssertTrue([[NSFileManager defaultManager] fileExistsAtPath:self.testFile]);
    if (fd >= 0) {
        NP::Sys::close(diag, fd);
    }
}

- (void)testOpenExistingFileForReading {
    [@"Hello, World!" writeToFile:self.testFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
    
    NP::Diagnostics diag;
    int fd = NP::Sys::open(diag, [self.testFile UTF8String], O_RDONLY, 0);
    XCTAssertFalse(diag.hasError());
    XCTAssertTrue(fd >= 0);
    if (fd >= 0) {
        NP::Sys::close(diag, fd);
    }
}

- (void)testOpenNonExistentFileWithoutCreate {
    NP::Diagnostics diag;
    int fd = NP::Sys::open(diag, [self.testFile UTF8String], O_RDONLY, 0);
    XCTAssertTrue(fd < 0);
    XCTAssertTrue(diag.hasError());
    XCTAssertEqual(errno, ENOENT);
}

- (void)testOpenWithExclusiveCreate {
    [@"Hello, World!" writeToFile:self.testFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
    
    NP::Diagnostics diag;
    int fd = NP::Sys::open(diag, [self.testFile UTF8String], O_CREAT | O_EXCL | O_RDWR, 0);
    XCTAssertTrue(fd < 0);
    XCTAssertTrue(diag.hasError());
    XCTAssertEqual(errno, EEXIST);
}

- (void)testOpenWithInvalidPath {
    NP::Diagnostics diag;
    int fd = NP::Sys::open(diag, "x", O_RDONLY, 0);
    XCTAssertTrue(fd < 0);
    XCTAssertTrue(diag.hasError());
}

- (void)testMmapReadOnlySuccess {
    [@"Hello, World!" writeToFile:self.testFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
    
    NP::Diagnostics diag;
    size_t size = 0;
    const void *mapping = NP::Sys::mmapReadOnly(diag, [self.testFile UTF8String], &size, nullptr);
    XCTAssertNotEqual(mapping, nullptr);
    XCTAssertFalse(diag.hasError());
    XCTAssertTrue(size == 13);
    XCTAssertTrue(::strncmp("Hello, World!", (char *)mapping, size) == 0);
    NP::Sys::munmap(diag, (char *)mapping, size);
    XCTAssertFalse(diag.hasError());
}

- (void)testMmapReadOnlyFailed {
    NP::Diagnostics diag;
    size_t size = 0;
    const void *mapping = NP::Sys::mmapReadOnly(diag, [self.testFile UTF8String], &size, nullptr);
    XCTAssertEqual(mapping, nullptr);
    XCTAssertTrue(diag.hasError());
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
