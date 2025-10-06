//
//  Heap.h
//  npfoundation
//
//  Created by Jonathan Lee on 9/20/25.
//
//  MIT License
//
//  Copyright (c) 2025 Jonathan Lee
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

#ifndef NP_DATASTRUCTURES_HEAP_H
#define NP_DATASTRUCTURES_HEAP_H

#ifdef __cplusplus

#include <NPFoundation/Definitions.h>

NP_NAMESPACE_BEGIN(NP)

enum class HeapType {
    max, min
};

template<class T>
class Heap {
    
private:
    
    std::vector<T> storage;
    
public:
    
    typedef int64_t Index;
    
    const HeapType type;
    
    Heap(HeapType type = HeapType::max) : type(type) {
        
    }
    
    Heap(const std::vector<T> &list, HeapType type = HeapType::max) : storage(list), type(type) {
        Index size = storage.size();
        Index idx = size / 2 - 1;
        for (; idx >= 0; idx --) {
            heapify(idx, size);
        }
    }
    
public:
    
    Index size() const {
        return storage.size();
    }
    
    bool empty() const {
        return storage.size() == 0;
    }
    
    const std::optional<T> top() const {
        if (storage.size() > 0) {
            return storage[0];
        } else {
            return std::nullopt;
        }
    }
    
private:
    
    bool lessThan(Index lhs, Index rhs) {
        return storage[lhs] < storage[rhs];
    }
    
    bool greaterThan(Index lhs, Index rhs) {
        return storage[lhs] > storage[rhs];
    }
    
    Index parentIndex(Index idx) const {
        return (idx - 1) / 2;
    }

    Index leftIndex(Index idx) const {
        return 2 * idx + 1;
    }
    
    Index rightIndex(Index idx) const {
        return 2 * idx + 2;
    }
    
private:
    
    void swap(Index lhs, Index rhs) {
        std::swap(storage[lhs], storage[rhs]);
    }
    
    bool comparator(Index lhs, Index rhs) {
        if (type == HeapType::min) {
            return lessThan(lhs, rhs);
        } else {
            return greaterThan(lhs, rhs);
        }
    }
    
    void heapify(Index idx, Index size) {
        Index left = leftIndex(idx);
        while (left < size) {
            Index next = 0;
            if (comparator(left, idx)) {
                next = left;
            } else {
                next = idx;
            }
            Index right = rightIndex(idx);
            if (right < size && comparator(right, next)) {
                next = right;
            }
            if (next != idx) {
                swap(idx, next);
                idx = next;
                left = leftIndex(idx);
            } else {
                break;
            }
        }
    }
    
public:
    
    void push(T && value) {
        Index idx = storage.size();
        storage.push_back(value);
        while (idx > 0) {
            Index parent = parentIndex(idx);
            if (comparator(idx, parent)) {
                std::swap(storage[idx], storage[parent]);
                idx = parent;
            } else {
                break;
            }
        }
    }
    
    const std::optional<T> pop() {
        Index size = storage.size();
        if (size < 1) {
            return std::nullopt;
        }
        
        size -= 1;
        if (size > 0) {
            swap(0, size);
            heapify(0, size);
        }
        
        T value = storage[size];
        storage.pop_back();
        return value;
    }
};

NP_NAMESPACE_END

#endif /* __cplusplus */

#endif /* NP_DATASTRUCTURES_HEAP_H */
