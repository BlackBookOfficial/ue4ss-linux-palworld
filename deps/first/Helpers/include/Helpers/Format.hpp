#pragma once

#include <string>
#include <cstdio>
#include <cstring>
#include <cwchar>

#include <String/StringType.hpp>

#ifndef _WIN32
#define sprintf_s(buf, bufsz, fmt, ...) snprintf(buf, bufsz, fmt, __VA_ARGS__)
#define swprintf_s(buf, bufsz, fmt, ...) swprintf(buf, bufsz, fmt, __VA_ARGS__)
#endif

namespace RC
{
    template <typename... Args>
    auto static fmt(const char* fmt, Args... args) -> std::string
    {
        constexpr size_t out_string_length = 1000;
        char out_string[out_string_length];

        size_t msg_len = strlen(fmt);

        // Attempt to give a hint if the buffer is too small
        if (msg_len > out_string_length)
        {
            fmt = "An error occurred but the message was too long for the buffer.";
            msg_len = strlen(fmt);
        }

        // If the buffer is too small for the hint message then I guess we do nothing
        // The default message will be used which can't be too small since it's calculated at compile-time
        if (msg_len < out_string_length)
        {
            sprintf_s(out_string, out_string_length, fmt, args...);
        }

        return out_string;
    }

    template <typename... Args>
    auto static fmt(const CharType* fmt, Args... args) -> StringType
    {
        constexpr size_t out_string_length = 1000;
        CharType out_string[out_string_length];

        size_t msg_len = 0;
        while (fmt[msg_len]) msg_len++;

        // Attempt to give a hint if the buffer is too small
        if (msg_len > out_string_length)
        {
            fmt = STR("An error occurred but the message was too long for the buffer.");
            msg_len = 0;
            while (fmt[msg_len]) msg_len++;
        }

        // If the buffer is too small for the hint message then I guess we do nothing
        // The default message will be used which can't be too small since it's calculated at compile-time
        if (msg_len < out_string_length)
        {
#ifdef _WIN32
            swprintf_s(out_string, out_string_length, fmt, args...);
#else
            // For char16_t, convert to a format call with char
            // Simple approach: no formatting on Linux for CharType
            size_t i = 0;
            while (fmt[i] && i < out_string_length - 1) { out_string[i] = fmt[i]; i++; }
            out_string[i] = 0;
#endif
        }

        return out_string;
    }
} // namespace RC
