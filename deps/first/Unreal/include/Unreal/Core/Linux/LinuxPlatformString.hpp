// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/Misc/Char.hpp"
#include "Unreal/Core/GenericPlatform/GenericPlatformString.hpp"
#include "Unreal/Core/GenericPlatform/GenericPlatformStricmp.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>

namespace RC::Unreal {

    struct FLinuxPlatformString : public FGenericPlatformString
    {
        using Super = FGenericPlatformString;

        using FGenericPlatformString::Stricmp;
        using FGenericPlatformString::Strncmp;
        using FGenericPlatformString::Strnicmp;

        template <typename CharType>
        static CharType* Strupr(CharType* Dest, SIZE_T DestCount)
        {
            for (CharType* Char = Dest; *Char && DestCount > 0; Char++, DestCount--)
            {
                *Char = TChar<CharType>::ToUpper(*Char);
            }
            return Dest;
        }

        /** WIDECHAR implementation (char16_t) - custom since POSIX wchar_t functions don't work with char16_t **/
        static FORCEINLINE WIDECHAR* Strcpy(WIDECHAR* Dest, SIZE_T DestCount, const WIDECHAR* Src) { WIDECHAR* Orig = Dest; while (DestCount > 1 && *Src) { *Dest++ = *Src++; DestCount--; } *Dest = 0; return Orig; }
        static FORCEINLINE WIDECHAR* Strncpy(WIDECHAR* Dest, const WIDECHAR* Src, SIZE_T MaxLen) { SIZE_T i = 0; for (; i < MaxLen - 1 && Src[i]; i++) Dest[i] = Src[i]; Dest[i] = 0; return Dest; }
        static FORCEINLINE WIDECHAR* Strcat(WIDECHAR* Dest, SIZE_T DestCount, const WIDECHAR* Src) { WIDECHAR* Orig = Dest; while (*Dest) Dest++; while (*Src) *Dest++ = *Src++; *Dest = 0; return Orig; }
        static FORCEINLINE int32 Strcmp(const WIDECHAR* String1, const WIDECHAR* String2) { while (*String1 && *String1 == *String2) { String1++; String2++; } return (int32)(*String1 - *String2); }
        static FORCEINLINE int32 Strncmp(const WIDECHAR* String1, const WIDECHAR* String2, SIZE_T Count) { for (SIZE_T i = 0; i < Count; i++) { if (String1[i] != String2[i]) return (int32)(String1[i] - String2[i]); if (!String1[i]) return 0; } return 0; }
        static FORCEINLINE int32 Strlen(const WIDECHAR* String) { int32 Count = 0; while (*String++) Count++; return Count; }
        static FORCEINLINE int32 Strnlen(const WIDECHAR* String, SIZE_T StringSize) { SIZE_T Count = 0; while (Count < StringSize && String[Count]) Count++; return (int32)Count; }
        static FORCEINLINE const WIDECHAR* Strstr(const WIDECHAR* String, const WIDECHAR* Find) { if (!*Find) return String; for (; *String; String++) { const WIDECHAR* s = String; const WIDECHAR* f = Find; while (*s && *f && *s == *f) { s++; f++; } if (!*f) return String; } return nullptr; }
        static FORCEINLINE const WIDECHAR* Strchr(const WIDECHAR* String, WIDECHAR C) { while (*String) { if (*String == C) return String; String++; } return C == 0 ? String : nullptr; }
        static FORCEINLINE const WIDECHAR* Strrchr(const WIDECHAR* String, WIDECHAR C) { const WIDECHAR* Last = nullptr; while (*String) { if (*String == C) Last = String; String++; } return Last; }
        static FORCEINLINE int32 Atoi(const WIDECHAR* String) { int32 Result = 0; int32 Sign = 1; if (*String == u'-') { Sign = -1; String++; } else if (*String == u'+') { String++; } while (*String >= u'0' && *String <= u'9') { Result = Result * 10 + (*String - u'0'); String++; } return Result * Sign; }
        static FORCEINLINE int64 Atoi64(const WIDECHAR* String) { int64 Result = 0; int64 Sign = 1; if (*String == u'-') { Sign = -1; String++; } else if (*String == u'+') { String++; } while (*String >= u'0' && *String <= u'9') { Result = Result * 10 + (*String - u'0'); String++; } return Result * Sign; }
        static FORCEINLINE float Atof(const WIDECHAR* String) { char buf[64]; int i = 0; while (String[i] && i < 63) { buf[i] = (char)String[i]; i++; } buf[i] = 0; return (float)atof(buf); }
        static FORCEINLINE double Atod(const WIDECHAR* String) { char buf[64]; int i = 0; while (String[i] && i < 63) { buf[i] = (char)String[i]; i++; } buf[i] = 0; return atof(buf); }
        static FORCEINLINE int32 Strtoi(const WIDECHAR* Start, WIDECHAR** End, int32 Base) { int32 Result = 0; while (*Start >= u'0' && *Start <= u'9') { Result = Result * Base + (*Start - u'0'); Start++; } if (End) *End = const_cast<WIDECHAR*>(Start); return Result; }
        static FORCEINLINE int64 Strtoi64(const WIDECHAR* Start, WIDECHAR** End, int32 Base) { int64 Result = 0; while (*Start >= u'0' && *Start <= u'9') { Result = Result * Base + (*Start - u'0'); Start++; } if (End) *End = const_cast<WIDECHAR*>(Start); return Result; }
        static FORCEINLINE uint64 Strtoui64(const WIDECHAR* Start, WIDECHAR** End, int32 Base) { uint64 Result = 0; while (*Start >= u'0' && *Start <= u'9') { Result = Result * Base + (*Start - u'0'); Start++; } if (End) *End = const_cast<WIDECHAR*>(Start); return Result; }
        static FORCEINLINE WIDECHAR* Strtok(WIDECHAR* StrToken, const WIDECHAR* Delim, WIDECHAR** Context) { WIDECHAR* Token = *Context ? *Context : StrToken; if (!*Token) return nullptr; const WIDECHAR* d; while (*Token) { for (d = Delim; *d; d++) if (*Token == *d) break; if (!*d) break; Token++; } if (!*Token) { *Context = Token; return nullptr; } WIDECHAR* Start = Token; while (*Token) { for (d = Delim; *d; d++) if (*Token == *d) break; if (*d) { *Token = 0; *Context = Token + 1; return Start; } Token++; } *Context = Token; return Start; }
        static FORCEINLINE int32 GetVarArgs(WIDECHAR* Dest, SIZE_T DestSize, const WIDECHAR*& Fmt, va_list ArgPtr) { int32 Result = 0; while (*Fmt && (SIZE_T)Result < DestSize - 1) { if (*Fmt == u'%') { Fmt++; if (*Fmt == u's') { const WIDECHAR* s = va_arg(ArgPtr, const WIDECHAR*); while (*s && (SIZE_T)Result < DestSize - 1) Dest[Result++] = *s++; } else if (*Fmt == u'd') { int32 val = va_arg(ArgPtr, int32); char buf[16]; snprintf(buf, sizeof(buf), "%d", val); for (int i = 0; buf[i] && (SIZE_T)Result < DestSize - 1; i++) Dest[Result++] = (WIDECHAR)buf[i]; } else { Dest[Result++] = *Fmt; } } else { Dest[Result++] = *Fmt; } Fmt++; } Dest[Result] = 0; return Result; }

        /** ANSICHAR implementation (char) **/
        static FORCEINLINE ANSICHAR* Strcpy(ANSICHAR* Dest, SIZE_T DestCount, const ANSICHAR* Src) { return strcpy(Dest, Src); }
        static FORCEINLINE ANSICHAR* Strncpy(ANSICHAR* Dest, const ANSICHAR* Src, SIZE_T MaxLen) { strncpy(Dest, Src, MaxLen); Dest[MaxLen-1] = 0; return Dest; }
        static FORCEINLINE ANSICHAR* Strcat(ANSICHAR* Dest, SIZE_T DestCount, const ANSICHAR* Src) { return strcat(Dest, Src); }
        static FORCEINLINE int32 Strcmp(const ANSICHAR* String1, const ANSICHAR* String2) { return strcmp(String1, String2); }
        static FORCEINLINE int32 Strncmp(const ANSICHAR* String1, const ANSICHAR* String2, SIZE_T Count) { return strncmp(String1, String2, Count); }
        static FORCEINLINE int32 Strlen(const ANSICHAR* String) { return (int32)strlen(String); }
        static FORCEINLINE int32 Strnlen(const ANSICHAR* String, SIZE_T StringSize) { return (int32)strnlen(String, StringSize); }
        static FORCEINLINE const ANSICHAR* Strstr(const ANSICHAR* String, const ANSICHAR* Find) { return strstr(String, Find); }
        static FORCEINLINE const ANSICHAR* Strchr(const ANSICHAR* String, ANSICHAR C) { return strchr(String, C); }
        static FORCEINLINE const ANSICHAR* Strrchr(const ANSICHAR* String, ANSICHAR C) { return strrchr(String, C); }
        static FORCEINLINE int32 Atoi(const ANSICHAR* String) { return atoi(String); }
        static FORCEINLINE int64 Atoi64(const ANSICHAR* String) { return strtoll(String, nullptr, 10); }
        static FORCEINLINE float Atof(const ANSICHAR* String) { return (float)atof(String); }
        static FORCEINLINE double Atod(const ANSICHAR* String) { return atof(String); }
        static FORCEINLINE int32 Strtoi(const ANSICHAR* Start, ANSICHAR** End, int32 Base) { return (int32)strtol(Start, End, Base); }
        static FORCEINLINE int64 Strtoi64(const ANSICHAR* Start, ANSICHAR** End, int32 Base) { return strtoll(Start, End, Base); }
        static FORCEINLINE uint64 Strtoui64(const ANSICHAR* Start, ANSICHAR** End, int32 Base) { return strtoull(Start, End, Base); }
        static FORCEINLINE ANSICHAR* Strtok(ANSICHAR* StrToken, const ANSICHAR* Delim, ANSICHAR** Context) { return strtok_r(StrToken, Delim, Context); }
        static FORCEINLINE int32 GetVarArgs(ANSICHAR* Dest, SIZE_T DestSize, const ANSICHAR*& Fmt, va_list ArgPtr) { int32 Result = vsnprintf(Dest, DestSize, Fmt, ArgPtr); return (Result != -1 && Result < (int32)DestSize) ? Result : -1; }

#if !PLATFORM_UCS2CHAR_IS_UTF16CHAR
        /** UCS2CHAR implementation (char16_t) **/
        static FORCEINLINE int32 Strlen(const UCS2CHAR* String) { int32 Count = 0; while (*String++) Count++; return Count; }
        static FORCEINLINE int32 Strnlen(const UCS2CHAR* String, SIZE_T StringSize) { SIZE_T Count = 0; while (Count < StringSize && String[Count]) Count++; return (int32)Count; }
        static FORCEINLINE UCS2CHAR* Strcpy(UCS2CHAR* Dest, SIZE_T DestCount, const UCS2CHAR* Src) { UCS2CHAR* Orig = Dest; while (DestCount > 1 && *Src) { *Dest++ = *Src++; DestCount--; } *Dest = 0; return Orig; }
        static FORCEINLINE UCS2CHAR* Strncpy(UCS2CHAR* Dest, const UCS2CHAR* Src, SIZE_T MaxLen) { SIZE_T i = 0; for (; i < MaxLen - 1 && Src[i]; i++) Dest[i] = Src[i]; Dest[i] = 0; return Dest; }
        static FORCEINLINE UCS2CHAR* Strcat(UCS2CHAR* Dest, SIZE_T DestCount, const UCS2CHAR* Src) { UCS2CHAR* Orig = Dest; while (*Dest) Dest++; while (*Src) *Dest++ = *Src++; *Dest = 0; return Orig; }
        static FORCEINLINE int32 Strcmp(const UCS2CHAR* String1, const UCS2CHAR* String2) { while (*String1 && *String1 == *String2) { String1++; String2++; } return (int32)(*String1 - *String2); }
        static FORCEINLINE int32 Strncmp(const UCS2CHAR* String1, const UCS2CHAR* String2, SIZE_T Count) { for (SIZE_T i = 0; i < Count; i++) { if (String1[i] != String2[i]) return (int32)(String1[i] - String2[i]); if (!String1[i]) return 0; } return 0; }
        static FORCEINLINE const UCS2CHAR* Strstr(const UCS2CHAR* String, const UCS2CHAR* Find) { if (!*Find) return String; for (; *String; String++) { const UCS2CHAR* s = String; const UCS2CHAR* f = Find; while (*s && *f && *s == *f) { s++; f++; } if (!*f) return String; } return nullptr; }
        static FORCEINLINE const UCS2CHAR* Strchr(const UCS2CHAR* String, UCS2CHAR C) { while (*String) { if (*String == C) return String; String++; } return C == 0 ? String : nullptr; }
        static FORCEINLINE const UCS2CHAR* Strrchr(const UCS2CHAR* String, UCS2CHAR C) { const UCS2CHAR* Last = nullptr; while (*String) { if (*String == C) Last = String; String++; } return Last; }
        static FORCEINLINE int32 Atoi(const UCS2CHAR* String) { int32 Result = 0; int32 Sign = 1; if (*String == u'-') { Sign = -1; String++; } else if (*String == u'+') { String++; } while (*String >= u'0' && *String <= u'9') { Result = Result * 10 + (*String - u'0'); String++; } return Result * Sign; }
        static FORCEINLINE int64 Atoi64(const UCS2CHAR* String) { int64 Result = 0; int64 Sign = 1; if (*String == u'-') { Sign = -1; String++; } else if (*String == u'+') { String++; } while (*String >= u'0' && *String <= u'9') { Result = Result * 10 + (*String - u'0'); String++; } return Result * Sign; }
        static FORCEINLINE float Atof(const UCS2CHAR* String) { char buf[64]; int i = 0; while (String[i] && i < 63) { buf[i] = (char)String[i]; i++; } buf[i] = 0; return (float)atof(buf); }
        static FORCEINLINE double Atod(const UCS2CHAR* String) { char buf[64]; int i = 0; while (String[i] && i < 63) { buf[i] = (char)String[i]; i++; } buf[i] = 0; return atof(buf); }
        static FORCEINLINE int32 Strtoi(const UCS2CHAR* Start, UCS2CHAR** End, int32 Base) { int32 Result = 0; while (*Start >= u'0' && *Start <= u'9') { Result = Result * Base + (*Start - u'0'); Start++; } if (End) *End = const_cast<UCS2CHAR*>(Start); return Result; }
        static FORCEINLINE int64 Strtoi64(const UCS2CHAR* Start, UCS2CHAR** End, int32 Base) { int64 Result = 0; while (*Start >= u'0' && *Start <= u'9') { Result = Result * Base + (*Start - u'0'); Start++; } if (End) *End = const_cast<UCS2CHAR*>(Start); return Result; }
        static FORCEINLINE uint64 Strtoui64(const UCS2CHAR* Start, UCS2CHAR** End, int32 Base) { uint64 Result = 0; while (*Start >= u'0' && *Start <= u'9') { Result = Result * Base + (*Start - u'0'); Start++; } if (End) *End = const_cast<UCS2CHAR*>(Start); return Result; }
        static FORCEINLINE UCS2CHAR* Strtok(UCS2CHAR* StrToken, const UCS2CHAR* Delim, UCS2CHAR** Context) { UCS2CHAR* Token = *Context ? *Context : StrToken; if (!*Token) return nullptr; const UCS2CHAR* d; while (*Token) { for (d = Delim; *d; d++) if (*Token == *d) break; if (!*d) break; Token++; } if (!*Token) { *Context = Token; return nullptr; } UCS2CHAR* Start = Token; while (*Token) { for (d = Delim; *d; d++) if (*Token == *d) break; if (*d) { *Token = 0; *Context = Token + 1; return Start; } Token++; } *Context = Token; return Start; }
        static FORCEINLINE int32 GetVarArgs(UCS2CHAR* Dest, SIZE_T DestSize, const UCS2CHAR*& Fmt, va_list ArgPtr) { int32 Result = 0; while (*Fmt && (SIZE_T)Result < DestSize - 1) { if (*Fmt == u'%') { Fmt++; if (*Fmt == u's') { const UCS2CHAR* s = va_arg(ArgPtr, const UCS2CHAR*); while (*s && (SIZE_T)Result < DestSize - 1) Dest[Result++] = *s++; } else if (*Fmt == u'd') { int32 val = va_arg(ArgPtr, int32); char buf[16]; snprintf(buf, sizeof(buf), "%d", val); for (int i = 0; buf[i] && (SIZE_T)Result < DestSize - 1; i++) Dest[Result++] = (UCS2CHAR)buf[i]; } else { Dest[Result++] = *Fmt; } } else { Dest[Result++] = *Fmt; } Fmt++; } Dest[Result] = 0; return Result; }
#endif

        /** UTF8CHAR implementation - delegates to ANSICHAR **/
        static FORCEINLINE UTF8CHAR* Strcpy(UTF8CHAR* Dest, SIZE_T DestCount, const UTF8CHAR* Src) { return (UTF8CHAR*)Strcpy((ANSICHAR*)Dest, DestCount, (const ANSICHAR*)Src); }
        static FORCEINLINE UTF8CHAR* Strncpy(UTF8CHAR* Dest, const UTF8CHAR* Src, SIZE_T MaxLen) { return (UTF8CHAR*)Strncpy((ANSICHAR*)Dest, (const ANSICHAR*)Src, MaxLen); }
        static FORCEINLINE UTF8CHAR* Strcat(UTF8CHAR* Dest, SIZE_T DestCount, const UTF8CHAR* Src) { return (UTF8CHAR*)Strcat((ANSICHAR*)Dest, DestCount, (const ANSICHAR*)Src); }
        static FORCEINLINE int32 Strcmp(const UTF8CHAR* String1, const UTF8CHAR* String2) { return Strcmp((const ANSICHAR*)String1, (const ANSICHAR*)String2); }
        static FORCEINLINE int32 Strncmp(const UTF8CHAR* String1, const UTF8CHAR* String2, SIZE_T Count) { return Strncmp((const ANSICHAR*)String1, (const ANSICHAR*)String2, Count); }
        static FORCEINLINE int32 Strlen(const UTF8CHAR* String) { return Strlen((const ANSICHAR*)String); }
        static FORCEINLINE int32 Strnlen(const UTF8CHAR* String, SIZE_T StringSize) { return Strnlen((const ANSICHAR*)String, StringSize); }
        static FORCEINLINE const UTF8CHAR* Strstr(const UTF8CHAR* String, const UTF8CHAR* Find) { return (const UTF8CHAR*)Strstr((const ANSICHAR*)String, (const ANSICHAR*)Find); }
        static FORCEINLINE const UTF8CHAR* Strchr(const UTF8CHAR* String, UTF8CHAR C) { return (const UTF8CHAR*)Strchr((const ANSICHAR*)String, (ANSICHAR)C); }
        static FORCEINLINE const UTF8CHAR* Strrchr(const UTF8CHAR* String, UTF8CHAR C) { return (const UTF8CHAR*)Strrchr((const ANSICHAR*)String, (ANSICHAR)C); }
        static FORCEINLINE int32 Atoi(const UTF8CHAR* String) { return Atoi((const ANSICHAR*)String); }
        static FORCEINLINE int64 Atoi64(const UTF8CHAR* String) { return Atoi64((const ANSICHAR*)String); }
        static FORCEINLINE float Atof(const UTF8CHAR* String) { return Atof((const ANSICHAR*)String); }
        static FORCEINLINE double Atod(const UTF8CHAR* String) { return Atod((const ANSICHAR*)String); }
        static FORCEINLINE int32 Strtoi(const UTF8CHAR* Start, UTF8CHAR** End, int32 Base) { return Strtoi((const ANSICHAR*)Start, (ANSICHAR**)End, Base); }
        static FORCEINLINE int64 Strtoi64(const UTF8CHAR* Start, UTF8CHAR** End, int32 Base) { return Strtoi64((const ANSICHAR*)Start, (ANSICHAR**)End, Base); }
        static FORCEINLINE uint64 Strtoui64(const UTF8CHAR* Start, UTF8CHAR** End, int32 Base) { return Strtoui64((const ANSICHAR*)Start, (ANSICHAR**)End, Base); }
        static FORCEINLINE UTF8CHAR* Strtok(UTF8CHAR* StrToken, const UTF8CHAR* Delim, UTF8CHAR** Context) { return (UTF8CHAR*)Strtok((ANSICHAR*)StrToken, (const ANSICHAR*)Delim, (ANSICHAR**)Context); }
        static FORCEINLINE int32 GetVarArgs(UTF8CHAR* Dest, SIZE_T DestSize, const UTF8CHAR*& Fmt, va_list ArgPtr) { return GetVarArgs((ANSICHAR*)Dest, DestSize, *(const ANSICHAR**)&Fmt, ArgPtr); }
    };

    typedef FLinuxPlatformString FPlatformString;

    #if PLATFORM_64BITS
    #define SIZE_T_FMT "lu"
    #define SIZE_T_x_FMT "lx"
    #define SIZE_T_X_FMT "lX"
    #define SSIZE_T_FMT "ld"
    #define SSIZE_T_x_FMT "lx"
    #define SSIZE_T_X_FMT "lX"
    #define PTRINT_FMT "ld"
    #define PTRINT_x_FMT "lx"
    #define PTRINT_X_FMT "lX"
    #define UPTRINT_FMT "lu"
    #define UPTRINT_x_FMT "lx"
    #define UPTRINT_X_FMT "lX"
    #else
    #define SIZE_T_FMT "u"
    #define SIZE_T_x_FMT "x"
    #define SIZE_T_X_FMT "X"
    #define SSIZE_T_FMT "d"
    #define SSIZE_T_x_FMT "x"
    #define SSIZE_T_X_FMT "X"
    #define PTRINT_FMT "d"
    #define PTRINT_x_FMT "x"
    #define PTRINT_X_FMT "X"
    #define UPTRINT_FMT "u"
    #define UPTRINT_x_FMT "x"
    #define UPTRINT_X_FMT "X"
    #endif

    #define INT64_FMT "lld"
    #define INT64_x_FMT "llx"
    #define INT64_X_FMT "llX"
    #define UINT64_FMT "llu"
    #define UINT64_x_FMT "llx"
    #define UINT64_X_FMT "llX"
}
