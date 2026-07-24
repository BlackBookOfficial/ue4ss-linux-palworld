// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal/Core/HAL/UnrealMemory.hpp"
#include "Unreal/Core/Containers/Array.hpp"
#include "Unreal/Core/HAL/ThreadSafeCounter.hpp"

/*-----------------------------------------------------------------------------
    Memory functions.
-----------------------------------------------------------------------------*/

#include "UnrealInitializer.hpp"

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

    return (*GMalloc)->Malloc(Count, Alignment);
  }

  void FMemory::Free(void* Original)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized) { return; }

    (*GMalloc)->Free(Original);
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

    return (*GMalloc)->Realloc(Original, Count, Alignment);
  }

  SIZE_T FMemory::QuantizeSize(SIZE_T Count, uint32 Alignment)
  {
    if (!GMalloc || !*GMalloc || !UnrealInitializer::StaticStorage::bVersionedContainerIsInitialized)
    {
      return Count;
    }

    return (*GMalloc)->QuantizeSize(Count, Alignment);
  }
  
}

