//
//  CopyOnWritePointer.hpp
//  knfoundation
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

#ifndef KN_COPYONWRITEPOINTER_H
#define KN_COPYONWRITEPOINTER_H

#ifdef __cplusplus

#include <KNFoundation/Definitions.h>
#include <atomic>

KN_NAMESPACE_BEGIN(KN)

template <typename T>
class CopyOnWritePointer {
    
private:
    
    struct ControlBlock {
        
        T *pointer;
        
        mutable std::atomic<uint32_t> retainCount;
        
        explicit ControlBlock(T *pointer) : retainCount(1), pointer(pointer) {
            
        }
        
        void retain() noexcept {
            retainCount.fetch_add(1);
        }
        
        void release() noexcept {
            const auto count = retainCount.fetch_sub(1);
        }
        
        uint32_t getRetainCount() const noexcept {
            return retainCount.load();
        }
    };
    
    ControlBlock *controlBlock;
    
public:
    
    explicit CopyOnWritePointer(T *pointer) : controlBlock(new ControlBlock(pointer)) {
        
    }
    
private:
    
    /// Read T *pointer
    T * read() const {
        return controlBlock->pointer;
    }
    
    T * write() {
        controlBlock->retain();
        controlBlock->release();
        
    }
};

KN_NAMESPACE_END

#endif /* __cplusplus */

#endif /* KN_COPYONWRITEPOINTER_H */
