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

@end

@implementation NPSysTests

- (void)setUp {
    struct stat buf;
    NP::Diagnostics diag;
    NP::Sys::stat(diag, ".", &buf);
    char cwd[PATH_MAX];
    NP::Sys::cwd(diag, cwd);
    
    bool w = NP::Sys::dirExists("/Users/jon/Downloads/CertificateSigningRequest");
    bool x = NP::Sys::dirExists("/Users/jon/Downloads/CertificateSigningRequest.certSigningRequest");
    bool y = NP::Sys::dirExists("/Users/jon/Downloads");
    bool z = NP::Sys::dirExists(".");
    
    bool w1 = NP::Sys::fileExists("/Users/jon/Downloads/CertificateSigningRequest");
    bool x1 = NP::Sys::fileExists("/Users/jon/Downloads/CertificateSigningRequest.certSigningRequest");
    bool y1 = NP::Sys::fileExists("/Users/jon/Downloads");
    bool z1 = NP::Sys::fileExists(".");
    
    printf("");
    // Put setup code here. This method is called before the invocation of each test method in the class.
}


- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
