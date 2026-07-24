// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#if !PLATFORM_WINDOWS
    #error this code should only be included on Windows
#endif

#if PLATFORM_CPU_X86_FAMILY
    #include <intrin.h>
    #include <smmintrin.h>
#endif

#include "Unreal/Core/Microsoft/MicrosoftPlatformMath.hpp"
namespace RC::Unreal
{
  typedef FMicrosoftPlatformMathBase FWindowsPlatformMath;
  typedef FWindowsPlatformMath FPlatformMath;
}
