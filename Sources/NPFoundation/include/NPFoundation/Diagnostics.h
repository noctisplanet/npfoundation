//
//  Diagnostics.h
//  npfoundation
//
//  Created by Jonathan Lee on 6/22/25.
//

#ifndef NP_DIAGNOSTICS_H
#define NP_DIAGNOSTICS_H

#ifdef __cplusplus

#include <NPFoundation/Definitions.h>
#include <stdarg.h>
#include <string>
#include <set>

NP_NAMESPACE_BEGIN(NP)

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

NP_NAMESPACE_END

#endif /* __cplusplus */

#endif /* NP_DIAGNOSTICS_H */
