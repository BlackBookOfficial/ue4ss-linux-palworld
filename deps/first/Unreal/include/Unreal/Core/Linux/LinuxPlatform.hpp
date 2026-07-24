// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#if defined(__clang__)
    #include "Clang/ClangPlatform.hpp"
#endif

#include "GenericPlatform/GenericPlatform.hpp"

// MSVC type compatibility for generated headers
typedef long long __int64;

/**
* Linux specific types
**/
struct FLinuxPlatformTypes : public FGenericPlatformTypes
{
    typedef size_t          SIZE_T;
    typedef ptrdiff_t       SSIZE_T;
    typedef char16_t        WIDECHAR;
    typedef char16_t        CHAR16;
    typedef WIDECHAR        TCHAR;
};

typedef FLinuxPlatformTypes FPlatformTypes;

// On Linux, WIDECHAR is char16_t which is the same as UCS2CHAR (CHAR16).
// This is intentional for UE4SS compatibility where CharType is char16_t.
#define PLATFORM_UCS2CHAR_IS_UTF16CHAR 1

// Base defines, must define these for the platform, there are no defaults
#define PLATFORM_DESKTOP                    1
#define PLATFORM_64BITS                     1

// Base defines, defaults are commented out
#define PLATFORM_LITTLE_ENDIAN              1
#define PLATFORM_SUPPORTS_UNALIGNED_LOADS   1

#define PLATFORM_SUPPORTS_PRAGMA_PACK       0
#define PLATFORM_CPU_ARM_FAMILY             0
#define PLATFORM_CPU_X86_FAMILY             1
#define PLATFORM_ENABLE_VECTORINTRINSICS    1

#define PLATFORM_USE_LS_SPEC_FOR_WIDECHAR   0
#define PLATFORM_TCHAR_IS_4_BYTES           0
#define PLATFORM_WCHAR_IS_4_BYTES           1
#define PLATFORM_TCHAR_IS_CHAR16            1
#define PLATFORM_HAS_BSD_TIME               1
#define PLATFORM_USE_PTHREADS               1
#define PLATFORM_USES_UNFAIR_LOCKS          0
#define PLATFORM_MAX_FILEPATH_LENGTH_DEPRECATED 4096
#define PLATFORM_HAS_BSD_IPV6_SOCKETS       1
#define PLATFORM_HAS_BSD_SOCKET_FEATURE_WINSOCKETS 0
#define PLATFORM_USES_MICROSOFT_LIBC_FUNCTIONS 0
#define PLATFORM_IS_ANSI_MALLOC_THREADSAFE  1
#define PLATFORM_SUPPORTS_ASYMMETRIC_FENCES 0

#define PLATFORM_SUPPORTS_TBB               0
#define PLATFORM_SUPPORTS_MIMALLOC          0
#define PLATFORM_SUPPORTS_NAMED_PIPES       1
#define PLATFORM_COMPILER_HAS_TCHAR_WMAIN   0
#define PLATFORM_SUPPORTS_EARLY_MOVIE_PLAYBACK (!WITH_EDITOR)
#define PLATFORM_USE_GENERIC_STRING_IMPLEMENTATION 0
#define PLATFORM_SUPPORTS_VARIABLE_RATE_SHADING 0
#define PLATFORM_SUPPORTS_MESH_SHADERS      0
#define PLATFORM_SUPPORTS_WORKGRAPH_SHADERS 0
#define PLATFORM_SUPPORTS_BINDLESS_RENDERING 0
#define PLATFORM_USES__ALIGNED_MALLOC       0

#define PLATFORM_SUPPORTS_STACK_SYMBOLS     1

#define PLATFORM_GLOBAL_LOG_CATEGORY        LogLinux

#define PLATFORM_SUPPORTS_BORDERLESS_WINDOW 1

#if defined(__clang__)
    #define PLATFORM_RETURN_ADDRESS_FOR_CALLSTACKTRACING PLATFORM_RETURN_ADDRESS
    #define PLATFORM_USE_CALLSTACK_ADDRESS_POINTER 0
#else
    #define PLATFORM_RETURN_ADDRESS_FOR_CALLSTACKTRACING 0
    #define PLATFORM_USE_CALLSTACK_ADDRESS_POINTER 0
#endif

#define LINUX_USE_FEATURE_APPLICATIONMISC_CLASS 1
#define LINUX_USE_FEATURE_PLATFORMMISC_CLASS     1

#define PLATFORM_BREAK() __builtin_trap()
#define PLATFORM_BREAK_IS_EXPRESSION 0

#define PLATFORM_HAS_128BIT_ATOMICS (PLATFORM_64BITS && defined(__x86_64__))

#ifdef CDECL
#undef CDECL
#endif

#define VARARGS     __attribute__((cdecl))
#define CDECL       __attribute__((cdecl))
#define STDCALL     
#define FORCEINLINE inline __attribute__((always_inline))
#define FORCENOINLINE __attribute__((noinline))

#ifndef FUNCTION_NON_NULL_RETURN_START
    #define FUNCTION_NON_NULL_RETURN_START [[gnu::returns_nonnull]]
#endif

#define DECLARE_UINT64(x) x

#ifndef PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
    #define PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
#endif
#ifndef PRAGMA_ENABLE_OPTIMIZATION_ACTUAL
    #define PRAGMA_ENABLE_OPTIMIZATION_ACTUAL
#endif

#ifndef PLATFORM_EMPTY_BASES
    #define PLATFORM_EMPTY_BASES
#endif

#define PLATFORM_CODE_SECTION(Name)

#if !defined(__clang__)
    #define TYPENAME_OUTSIDE_TEMPLATE typename
#endif

#define ABSTRACT abstract

#define LINE_TERMINATOR TEXT("\n")
#define LINE_TERMINATOR_ANSI "\n"

#if defined(__clang__) || defined(__GNUC__)
    #define GCC_PACK(n) __attribute__((packed,aligned(n)))
    #define GCC_ALIGN(n) __attribute__((aligned(n)))
    #define MS_ALIGN(n) __attribute__((aligned(n)))
#endif

#ifndef MSVC_PRAGMA
    #define MSVC_PRAGMA(Pragma)
#endif

#define DLLEXPORT __attribute__((visibility("default")))
#define DLLIMPORT __attribute__((visibility("default")))

#if PLATFORM_COMPILER_CLANG
    #include "Clang/ClangPlatformCodeAnalysis.hpp"
#endif

#ifndef PLATFORM_RETURN_ADDRESS
    #if defined(__clang__) || defined(__GNUC__)
        #define PLATFORM_RETURN_ADDRESS() __builtin_return_address(0)
        #define PLATFORM_RETURN_ADDRESS_POINTER() __builtin_frame_address(0)
    #endif
#endif

#ifndef UE_LIFETIMEBOUND
    #define UE_LIFETIMEBOUND
#endif

#ifndef UE_NODEBUG
    #define UE_NODEBUG
#endif

#ifndef UE_ALLOCATION_FUNCTION
    #define UE_ALLOCATION_FUNCTION_0() 
    #define UE_ALLOCATION_FUNCTION_1(SIZE) 
    #define UE_ALLOCATION_FUNCTION_2(SIZE, ALIGN) 
    #define UE_ALLOCATION_FUNCTION_X(x, SIZE, ALIGN, FUNC, ...) FUNC
    #define UE_ALLOCATION_FUNCTION(...) UE_ALLOCATION_FUNCTION_X(,##__VA_ARGS__, UE_ALLOCATION_FUNCTION_2(__VA_ARGS__), UE_ALLOCATION_FUNCTION_1(__VA_ARGS__), UE_ALLOCATION_FUNCTION_0(__VA_ARGS__))
#endif

#ifndef PLATFORM_COMPILER_SUPPORTS_BUILTIN_BITCAST
    #define PLATFORM_COMPILER_SUPPORTS_BUILTIN_BITCAST 1
#endif

#ifndef CALLSITE_FORCEINLINE
    #define CALLSITE_FORCEINLINE inline __attribute__((always_inline))
#endif

#ifndef UE_NO_PROFILE_ATTRIBUTE
    #define UE_NO_PROFILE_ATTRIBUTE
#endif
