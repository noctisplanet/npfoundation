//
//  Diagnostics.cpp
//  knfoundation
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

#include <KNFoundation/Diagnostics.h>
#include <stdio.h>
#include <stdlib.h>

KN_NAMESPACE_BEGIN(KN)

Diagnostics::Diagnostics(FILE *stream, bool verbose) : Stream(stream), Verbose(verbose) {
    
}

Diagnostics::Diagnostics(const std::string& prefix, FILE *stream, bool verbose) : Prefix(prefix), Stream(stream), Verbose(verbose) {
    
}

void Diagnostics::note(const char* format, ...) {
    va_list args;
    va_start(args, format);
    if (!Prefix.empty()) {
        ::fprintf(Stream, "[%s] ", Prefix.c_str());
    }
    ::vfprintf(Stream, format, args);
    va_end(args);
    ::fprintf(Stream, "\n");
}

void Diagnostics::verbose(const char* format, ...) {
    if (Verbose) {
        va_list args;
        va_start(args, format);
        if (!Prefix.empty()) {
            ::fprintf(Stream, "[%s] ", Prefix.c_str());
        }
        ::vfprintf(Stream, format, args);
        va_end(args);
        ::fprintf(Stream, "\n");
    }
}

void Diagnostics::warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    if (Verbose) {
        ::fprintf(Stream, "[warning]");
    }
    if (!Prefix.empty()) {
        ::fprintf(Stream, "[%s] ", Prefix.c_str());
    }
    ::vfprintf(Stream, format, args);
    va_end(args);
    ::fprintf(Stream, "\n");
}

void Diagnostics::error(const char* format, ...) {
    std::string str;
    va_list args;
    va_start(args, format);
    auto len = vsnprintf(nullptr, 0, format, args);
    va_end(args);
    if (len > 0) {
        auto size = len + 1;
        str.resize(size);
        va_start(args, format);
        vsnprintf((char *)str.data(), size, format, args);
        va_end(args);
        Errors.insert(str);
        if (Verbose) {
            ::fprintf(Stream, "[error]");
        }
        if (!Prefix.empty()) {
            ::fprintf(Stream, "[%s] ", Prefix.c_str());
        }
        ::fprintf(Stream, "%s", str.c_str());
        ::fprintf(Stream, "\n");
    }
}

bool Diagnostics::hasError() const {
    return !Errors.empty();
}

bool Diagnostics::noError() const {
    return Errors.empty();
}

void Diagnostics::clearError() {
    return Errors.clear();
}

void Diagnostics::assertNoError() const {
    if (hasError()) {
        
    }
}

KN_NAMESPACE_END
