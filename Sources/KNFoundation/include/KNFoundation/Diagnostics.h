//
//  Diagnostics.h
//  npfoundation
//
//  Created by Jonathan Lee on 6/22/25.
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

#ifndef KN_DIAGNOSTICS_H
#define KN_DIAGNOSTICS_H

#ifdef __cplusplus

#include <KNFoundation/Definitions.h>
#include <stdarg.h>
#include <string>
#include <set>

KN_NAMESPACE_BEGIN(KN)

class Diagnostics {
    
private:
    
    FILE *Stream;
    
    const bool Verbose = false;
    
    const std::string Prefix;
    
    std::set<std::string> Errors;
    
public:
    
    Diagnostics(FILE *Stream = stderr, bool verbose=false);
    
    Diagnostics(const std::string& prefix, FILE *stream = stderr, bool verbose=false);
    
public:
    
    void note(const char* format, ...) __attribute__((format(printf, 2, 3)));
    
    void verbose(const char* format, ...) __attribute__((format(printf, 2, 3)));
    
    void warning(const char* format, ...) __attribute__((format(printf, 2, 3)));
    
    void error(const char* format, ...) __attribute__((format(printf, 2, 3)));
    
public:
    
    bool hasError() const;
    
    bool noError() const;
    
    void clearError();
    
    void assertNoError() const;
};

KN_NAMESPACE_END

#endif /* __cplusplus */

#endif /* KN_DIAGNOSTICS_H */
