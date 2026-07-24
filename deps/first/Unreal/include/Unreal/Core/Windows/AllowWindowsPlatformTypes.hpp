// Copyright Epic Games, Inc. All Rights Reserved.

// #TODO: redirect to platform-agnostic version for the time being. Eventually this will become an error
#include "HAL/Platform.hpp"
#if !PLATFORM_WINDOWS
    #include "Microsoft/AllowMicrosoftPlatformTypes.hpp"
#else


#include "Windows/WindowsHWrapper.hpp"

#ifndef WINDOWS_PLATFORM_TYPES_GUARD
    #define WINDOWS_PLATFORM_TYPES_GUARD
#else
    #error Nesting AllowWindowsPlatformTypes.hpp is not allowed!
#endif

#pragma warning( push )
#pragma warning( disable : 4459 )

#define INT ::INT
#define UINT ::UINT
#define DWORD ::DWORD
#define FLOAT ::FLOAT

#define TRUE 1
#define FALSE 0

#endif //PLATFORM_*
