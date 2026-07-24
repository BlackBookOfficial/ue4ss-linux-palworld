#pragma once

// Compatibility shims for Windows CRT secure functions on Linux.
// Provides: strncpy_s, localtime_s, printf_s, sscanf_s, _TRUNCATE

#ifdef __linux__

#include <cstdio>
#include <cstring>
#include <ctime>

// _TRUNCATE: Special value indicating truncation is acceptable
static constexpr size_t _TRUNCATE = static_cast<size_t>(-1);

// strncpy_s: Windows secure string copy with truncation
// dest:      Destination buffer
// destSize:  Size of destination buffer in bytes
// src:       Source string
// count:     Number of characters to copy, or _TRUNCATE
// Returns:   0 on success, errno on error
inline int strncpy_s(char* dest, size_t destSize, const char* src, size_t count)
{
    if (!dest || !src || destSize == 0) return EINVAL;
    if (count == _TRUNCATE) count = destSize - 1;
    if (count >= destSize)
    {
        // Truncate
        count = destSize - 1;
    }
    std::memmove(dest, src, count);
    dest[count] = '\0';
    return 0;
}

// localtime_s: Windows secure localtime (reversed args vs POSIX localtime_r)
// tm:   Destination tm struct
// time: Source time_t
// Returns: 0 on success, errno on error
inline int localtime_s(std::tm* tm, const std::time_t* time)
{
    if (!tm || !time) return EINVAL;
    localtime_r(time, tm);
    return 0;
}

// printf_s, sscanf_s: same as printf, sscanf on Linux
#define printf_s printf
#define sscanf_s sscanf

#endif // __linux__
