// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/Windows/WindowsPlatformCompilerSetup.hpp"
#include "Unreal/Core/Windows/MinimalWindowsApi.hpp"

// Macro for releasing COM objects
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

namespace RC::Unreal
{
  // Current instance
  extern "C" CORE_API Windows::HINSTANCE hInstance;
}

// SIMD intrinsics
THIRD_PARTY_INCLUDES_START
#include <intrin.h>

#include <stdint.h>
#include "Unreal/Core/HAL/HideTCHAR.hpp"
#include <tchar.h>
#include "Unreal/Core/HAL/AllowTCHAR.hpp"

// When compiling under Windows, these headers cause us particular problems.  We need to make sure they're included before we pull in our 
// 'DoNotUseOldUE4Type' namespace.  This is because these headers will redeclare various numeric typedefs, but under the Clang and Visual
// Studio compilers it is not allowed to define a typedef with a global scope operator in it (such as ::INT). So we'll get these headers
// included early on to avoid compiler errors with that.
#if defined(__clang__) || (defined(_MSC_VER) && (_MSC_VER >= 1900))
#include <intsafe.h>
#include <strsafe.h>
#endif

THIRD_PARTY_INCLUDES_END
