//
//  NPHeapTests.m
//  npfoundation
//
//  Created by Jonathan Lee on 10/6/25.
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
#import <XCTest/XCTest.h>

@interface NPHeapTests : XCTestCase {
    std::vector<int> _list;
}

@end

@implementation NPHeapTests

- (void)setUp {
    size_t size = 1000000;
    if (_list.size() < size) {
        for (int idx = 0; idx < size; idx ++) {
            _list.push_back(arc4random_uniform((uint32_t)size) - 50000);
        }
    }
}

- (void)testMinHeapPushAndPop {
    NP::Heap<int> heap{NP::HeapType::min};
    heap.push(10);
    heap.push(11);
    heap.push(2);
    heap.push(7);
    heap.push(20);
    heap.push(18);
    XCTAssertEqual(heap.size(), 6);
    XCTAssertEqual(heap.top(), 2);
    XCTAssertEqual(heap.pop(), 2);
    XCTAssertEqual(heap.pop(), 7);
    XCTAssertEqual(heap.pop(), 10);
    XCTAssertEqual(heap.pop(), 11);
    XCTAssertEqual(heap.pop(), 18);
    XCTAssertEqual(heap.pop(), 20);
    XCTAssertFalse(heap.pop().has_value());
    XCTAssertTrue(heap.empty());
}

- (void)testMaxHeapPushAndPop {
    NP::Heap<int> heap{NP::HeapType::max};
    heap.push(10);
    heap.push(11);
    heap.push(2);
    heap.push(7);
    heap.push(20);
    heap.push(18);
    XCTAssertEqual(heap.size(), 6);
    XCTAssertEqual(heap.top(), 20);
    XCTAssertEqual(heap.pop(), 20);
    XCTAssertEqual(heap.pop(), 18);
    XCTAssertEqual(heap.pop(), 11);
    XCTAssertEqual(heap.pop(), 10);
    XCTAssertEqual(heap.pop(), 7);
    XCTAssertEqual(heap.pop(), 2);
    XCTAssertFalse(heap.pop().has_value());
    XCTAssertTrue(heap.empty());
}

- (void)testBuildMinHeap {
    NP::Heap<int32_t> heap{_list, NP::HeapType::min};
    XCTAssertEqual(heap.size(), _list.size());
    int32_t cur = INT32_MIN;
    while (heap.size() > 0) {
        const auto element = heap.pop();
        XCTAssertTrue(element >= cur);
        cur = element.value();
    }
    XCTAssertEqual(heap.size(), 0);
}

- (void)testBuildMaxHeap {
    NP::Heap<int32_t> heap{_list, NP::HeapType::max};
    XCTAssertEqual(heap.size(), _list.size());
    int32_t cur = INT32_MAX;
    while (heap.size() > 0) {
        const auto element = heap.pop();
        XCTAssertTrue(element <= cur);
        cur = element.value();
    }
    XCTAssertEqual(heap.size(), 0);
}

@end
