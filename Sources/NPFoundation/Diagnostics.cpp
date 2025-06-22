//
//  Diagnostics.cpp
//  npfoundation
//
//  Created by Jonathan Lee on 6/22/25.
//

#include <NPFoundation/Diagnostics.h>
#include <stdio.h>
#include <stdlib.h>

NP_NAMESPACE_BEGIN(NP)

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

NP_NAMESPACE_END
