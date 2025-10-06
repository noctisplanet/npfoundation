//
//  CopyOnWriteBacked.hpp
//  npfoundation
//
//  Created by Jonathan Lee on 8/9/25.
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

#ifndef NP_COPYONWRITEBACKED_H
#define NP_COPYONWRITEBACKED_H

#ifdef __cplusplus

#include <atomic>
#include <forward_list>
#include <NPFoundation/Definitions.h>

NP_NAMESPACE_BEGIN(NP)

template <typename T>
class CopyOnWriteBacked {
    
private:
    
    struct Block: Nocopy {
        
        T *pointer;
        
        mutable std::atomic<uint32_t> retainCount;
        
        explicit Block(T *pointer) : retainCount(1), pointer(pointer) {
            
        }
        
        Block * retain() noexcept {
            this->retainCount.fetch_add(1);
            return this;
        }
        
        void release() noexcept {
            this->retainCount.fetch_sub(1);
            uint32_t rc = this->retainCount.load();
            if (rc == 0) {
                delete this->pointer;
                delete this;
            }
        }
        
        T* get() const noexcept {
            return this->pointer;
        }
    };
    
private:
    
    Block *block;
    
public:
    
    explicit CopyOnWriteBacked(T *pointer) : block(new Block(pointer)) {
        
    }
    
    ~CopyOnWriteBacked() {
        this->block->release();
    }
    
    CopyOnWriteBacked(const CopyOnWriteBacked &dataSource) : block(dataSource.block->retain()) {
        
    }
    
    CopyOnWriteBacked & operator=(const CopyOnWriteBacked& cowp) {
        if (this->block != cowp.block) {
            this->block->release();
            this->block = cowp.block->retain();
        }
        return *this;
    }
    
public:
    
    uint32_t retainCount() const {
        return this->block->retainCount.load(std::memory_order_relaxed);
    }
    
    const T * get() const {
        return this->block->get();
    }
    
    const T * operator->() const {
        return this->block->get();
    }
    
    T * acquireUnique() {
        if (this->retainCount() > 1) {
            T *pointer = new T(*this->block->get());
            this->block->release();
            this->block = new Block(pointer);
        }
        return this->block->get();
    }
};

template <typename T, typename... Args>
CopyOnWriteBacked<T> CopyOnWriteMake(Args&&... args) {
    return CopyOnWriteBacked<T>(new T(std::forward<Args>(args)...));
}

NP_NAMESPACE_END

#endif /* __cplusplus */

#endif /* NP_COPYONWRITEBACKED_H */
