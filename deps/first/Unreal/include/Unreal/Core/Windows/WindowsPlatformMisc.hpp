// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/HAL/PlatformMemory.hpp"
#include "Unreal/Core/GenericPlatform/GenericPlatformMisc.hpp"

#define UE_DEBUG_BREAK_IMPL() PLATFORM_BREAK()

namespace RC::Unreal
{
  class GenericApplication;
  struct FGuid;
  class IPlatformChunkInstall;

  /**
  * Windows implementation of the misc OS functions
  **/
  struct FWindowsPlatformMisc
          : public FGenericPlatformMisc
  {
    

    FORCEINLINE static void MemoryBarrier() 
    {
  #if PLATFORM_CPU_X86_FAMILY
      _mm_sfence();
  #elif PLATFORM_CPU_ARM_FAMILY
      __dmb(_ARM64_BARRIER_SY);
  #endif
    }
    
  };


  #if WINDOWS_USE_FEATURE_PLATFORMMISC_CLASS
  typedef FWindowsPlatformMisc FPlatformMisc;
  #endif
}