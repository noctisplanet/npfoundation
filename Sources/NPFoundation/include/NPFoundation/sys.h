//
//  sys.h
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

#ifndef NP_SYS_H
#define NP_SYS_H

#ifdef __cplusplus

#include <NPFoundation/Definitions.h>
#include <NPFoundation/Diagnostics.h>
#include <sys/stat.h>

NP_NAMESPACE_BEGIN(NP)
NP_NAMESPACE_BEGIN(Sys)

int open(Diagnostics &diag, const char *path, int flag, int other) noexcept;

void close(Diagnostics &diag, int fd) noexcept;

void stat(Diagnostics &diag, const char *path, struct ::stat *buf) noexcept;

void fstatat(Diagnostics &diag, int fd, const char *path, struct ::stat *buf, int flag) noexcept;

void truncate(Diagnostics &diag, const char *path, size_t size) noexcept;

void ftruncate(Diagnostics &diag, int fd, size_t size) noexcept;

void cwd(Diagnostics &diag, char *output) noexcept;

void realpath(Diagnostics &diag, const char *input, char *output) noexcept;

bool dirExists(const char *path) noexcept;

bool fileExists(const char *path) noexcept;

const void * mmapReadOnly(Diagnostics &diag, const char *path, size_t *size, char *realerPath) noexcept;

void * mmapReadWrite(Diagnostics &diag, const char *path, size_t *size, char *realerPath) noexcept;

void munmap(Diagnostics &diag, void *buf, size_t size) noexcept;

const void * read(Diagnostics &diag, const char *path, size_t *size) noexcept;

NP_NAMESPACE_END
NP_NAMESPACE_END

#endif /* __cplusplus */

#endif /* NP_SYS_H */
