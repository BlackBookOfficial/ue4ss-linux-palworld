// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal/Core/HAL/UnrealMemory.hpp"
#include "Unreal/Core/Containers/Array.hpp"
#include "Unreal/Core/HAL/ThreadSafeCounter.hpp"

#include <functional>

/*-----------------------------------------------------------------------------
    Memory functions.
-----------------------------------------------------------------------------*/

#include "UnrealInitializer.hpp"

// Allocator recovery wrapper (defined in main_linux.cpp)
extern "C" bool ue4ss_with_alloc_recovery(const std::function<void()>& func);

namespace RC::Unreal
{
  void* FMemory::MallocExternal(SIZE_T Count, uint32 Alignment)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::MallocExternal' before the FMalloc instance was found"};
    }
    return (*GMalloc)->Malloc(Count, Alignment);
  }

  void* FMemory::ReallocExternal(void* Original, SIZE_T Count, uint32 Alignment)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::ReallocExternal' before the FMalloc instance was found"};
    }
    return (*GMalloc)->Realloc(Original, Count, Alignment);
  }

  void FMemory::FreeExternal(void* Original)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::FreeExternal' before the FMalloc instance was found"};
    }
    if (Original)
    {
      (*GMalloc)->Free(Original);
    }
  }

  SIZE_T FMemory::GetAllocSizeExternal(void* Original)
  { 
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::GetAllocSizeExternal' before the FMalloc instance was found"};
    }
    SIZE_T Size = 0;
    return (*GMalloc)->GetAllocationSize(Original, Size) ? Size : 0;
  }

  SIZE_T FMemory::QuantizeSizeExternal(SIZE_T Count, uint32 Alignment)
  { 
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::QuantizeSizeExternal' before the FMalloc instance was found"};
    }
    return (*GMalloc)->QuantizeSize(Count, Alignment);
  }    


  void FMemory::Trim(bool bTrimThreadCaches)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::Trim' before the FMalloc instance was found"};
    }
    (*GMalloc)->Trim(bTrimThreadCaches);
  }

  void FMemory::SetupTLSCachesOnCurrentThread()
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::SetupTLSCachesOnCurrentThread' before the FMalloc instance was found"};
    }
    (*GMalloc)->SetupTLSCachesOnCurrentThread();
  }
      
  void FMemory::ClearAndDisableTLSCachesOnCurrentThread()
  {
    if (GMalloc && *GMalloc)
    {
      (*GMalloc)->ClearAndDisableTLSCachesOnCurrentThread();
    }
  }

  void* FUseSystemMallocForNew::operator new(size_t Size)
  {
    return FMemory::SystemMalloc(Size);
  }

  void FUseSystemMallocForNew::operator delete(void* Ptr)
  {
    FMemory::SystemFree(Ptr);
  }

  void* FUseSystemMallocForNew::operator new[](size_t Size)
  {
    return FMemory::SystemMalloc(Size);
  }

  void FUseSystemMallocForNew::operator delete[](void* Ptr)
  {
    FMemory::SystemFree(Ptr);
  }

  void* FMemory::Malloc(SIZE_T Count, uint32 Alignment)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::Malloc' before the FMalloc instance was found"};
    }

#ifdef __linux__
    // On Linux, UE4SS runs on a detached background thread. The engine's
    // FMallocBinned2 uses pthread_getspecific for per-thread allocation
    // caches. On the game thread, the TLS cache is initialized during
    // engine boot. On UE4SS's background thread, the TLS cache may not
    // be set up, causing the allocator to crash when accessing thread-local
    // pool structures.
    //
    // Additionally, the GMalloc heuristic may find a false-positive
    // allocator (multiple FMalloc* pointers exist in BSS, only one is
    // the engine's GMalloc). Calling Malloc/Realloc/Free on a wrong
    // allocator can crash.
    //
    // UE4SS's internal containers (TMap, TSparseArray, TArray) are
    // self-contained and don't interact with the engine's garbage
    // collector. Using the system allocator is safe and avoids both issues.
    return SystemMalloc(Count);
#else
    return (*GMalloc)->Malloc(Count, Alignment);
#endif
  }

  void FMemory::Free(void* Original)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized) { return; }

#ifdef __linux__
    // See FMemory::Malloc for rationale.
    SystemFree(Original);
#else
    (*GMalloc)->Free(Original);
#endif
  }

  SIZE_T FMemory::GetAllocSize(void* Original)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::GetAllocSize' before the FMalloc instance was found"};
    }

    SIZE_T Size = 0;
    const SIZE_T Result = (*GMalloc)->GetAllocationSize(Original, Size) ? Size : 0;
    return Result;
  }

  void* FMemory::Realloc(void* Original, SIZE_T Count, uint32 Alignment)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      throw std::runtime_error{"Tried to call 'FMemory::Realloc' before the FMalloc instance was found"};
    }

#ifdef __linux__
    // See FMemory::Malloc for rationale.
    if (!Original) return SystemMalloc(Count);
    if (Count == 0) { SystemFree(Original); return nullptr; }
    return ::realloc(Original, Count);
#else
    return (*GMalloc)->Realloc(Original, Count, Alignment);
#endif
  }

  SIZE_T FMemory::QuantizeSize(SIZE_T Count, uint32 Alignment)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      return Count;
    }

#ifdef __linux__
    // See FMemory::Malloc for rationale. QuantizeSize is advisory — return
    // the unmodified count when using the system allocator.
    return Count;
#else
    return (*GMalloc)->QuantizeSize(Count, Alignment);
#endif
  }
  
}

