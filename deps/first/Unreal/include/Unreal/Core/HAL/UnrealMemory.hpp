// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Common.hpp"
#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/GenericPlatform/GenericPlatformMemory.hpp"
#include "Unreal/Core/HAL/MemoryBase.hpp"
#include "Unreal/Core/HAL/PlatformMemory.hpp"
#include "Unreal/Core/Templates/IsPointer.hpp"

#ifndef UE_USE_VERYLARGEPAGEALLOCATOR
#define UE_USE_VERYLARGEPAGEALLOCATOR 0
#endif

#ifndef UE_ALLOW_OSMEMORYLOCKFREE
#define UE_ALLOW_OSMEMORYLOCKFREE 0
#endif


// Sizes.

#if STATS
#define MALLOC_GT_HOOKS 1
#else
#define MALLOC_GT_HOOKS 0
#endif

namespace RC::Unreal
{
  /*-----------------------------------------------------------------------------
          FMemory.
  -----------------------------------------------------------------------------*/

  struct FMemory
  {
    /** Some allocators can be given hints to treat allocations differently depending on how the memory is used, it's lifetime etc. */
    enum AllocationHints
    {
      None = -1,
      Default,
      Temporary,
      SmallPool,

      Max
  };


    /** @name Memory functions (wrapper for FPlatformMemory) */

    static FORCEINLINE void* Memmove( void* Dest, const void* Src, SIZE_T Count )
    {
      return FPlatformMemory::Memmove( Dest, Src, Count );
    }

    static FORCEINLINE int32 Memcmp( const void* Buf1, const void* Buf2, SIZE_T Count )
    {
      return FPlatformMemory::Memcmp( Buf1, Buf2, Count );
    }

    static FORCEINLINE void* Memset(void* Dest, uint8 Char, SIZE_T Count)
    {
      return FPlatformMemory::Memset( Dest, Char, Count );
    }

    template< class T > 
    static FORCEINLINE void Memset( T& Src, uint8 ValueToSet )
    {
      static_assert( !TIsPointer<T>::Value, "For pointers use the three parameters function");
      Memset( &Src, ValueToSet, sizeof( T ) );
    }

    static FORCEINLINE void* Memzero(void* Dest, SIZE_T Count)
    {
      return FPlatformMemory::Memzero( Dest, Count );
    }

    /** Returns true if memory is zeroes, false otherwise. */
    static FORCEINLINE bool MemIsZero(const void* Ptr, SIZE_T Count)
    {
      // first pass implementation
      uint8* Start = (uint8*)Ptr;
      uint8* End = Start + Count;
      while (Start < End)
      {
        if ((*Start++) != 0)
        {
          return false;
        }
      }

      return true;
    }

    template< class T > 
    static FORCEINLINE void Memzero( T& Src )
    {
      static_assert( !TIsPointer<T>::Value, "For pointers use the two parameters function");
      Memzero( &Src, sizeof( T ) );
    }

    static FORCEINLINE void* Memcpy(void* Dest, const void* Src, SIZE_T Count)
    {
      return FPlatformMemory::Memcpy(Dest,Src,Count);
    }

    template< class T > 
    static FORCEINLINE void Memcpy( T& Dest, const T& Src )
    {
      static_assert( !TIsPointer<T>::Value, "For pointers use the three parameters function");
      Memcpy( &Dest, &Src, sizeof( T ) );
    }

    static FORCEINLINE void* BigBlockMemcpy(void* Dest, const void* Src, SIZE_T Count)
    {
      return FPlatformMemory::BigBlockMemcpy(Dest,Src,Count);
    }

    static FORCEINLINE void* StreamingMemcpy(void* Dest, const void* Src, SIZE_T Count)
    {
      return FPlatformMemory::StreamingMemcpy(Dest,Src,Count);
    }

    static FORCEINLINE void* ParallelMemcpy(void* Dest, const void* Src, SIZE_T Count, EMemcpyCachePolicy Policy = EMemcpyCachePolicy::StoreCached)
    {
      return FPlatformMemory::ParallelMemcpy(Dest, Src, Count, Policy);
    }

    static FORCEINLINE void Memswap( void* Ptr1, void* Ptr2, SIZE_T Size )
    {
      FPlatformMemory::Memswap(Ptr1,Ptr2,Size);
    }

    //
    // C style memory allocation stubs that fall back to C runtime
    //
    static FORCEINLINE void* SystemMalloc(SIZE_T Size)
    {
      /* TODO: Trace! */
      return ::malloc(Size);
    }

    static FORCEINLINE void SystemFree(void* Ptr)
    {
      /* TODO: Trace! */
      ::free(Ptr);
    }

    //
    // C style memory allocation stubs.
    //

    static CORE_API void* Malloc(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);
    static CORE_API void* Realloc(void* Original, SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);
    static CORE_API void Free(void* Original);
    static CORE_API SIZE_T GetAllocSize(void* Original);

    static FORCEINLINE_DEBUGGABLE void* MallocZeroed(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT)
    {
      void* Memory = Malloc(Count, Alignment);
      Memzero(Memory, Count);
      return Memory;
    }

    /**
    * For some allocators this will return the actual size that should be requested to eliminate
    * internal fragmentation. The return value will always be >= Count. This can be used to grow
    * and shrink containers to optimal sizes.
    * This call is always fast and threadsafe with no locking.
    */
    static CORE_API SIZE_T QuantizeSize(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);

    /**
    * Releases as much memory as possible. Must be called from the main thread.
    */
    static CORE_API void Trim(bool bTrimThreadCaches = true);

    /**
    * Set up TLS caches on the current thread. These are the threads that we can trim.
    */
    static CORE_API void SetupTLSCachesOnCurrentThread();

    /**
    * Clears the TLS caches on the current thread and disables any future caching.
    */
    static CORE_API void ClearAndDisableTLSCachesOnCurrentThread();
  
  private:
    // These versions are called either at startup or in the event of a crash
    static CORE_API void* MallocExternal(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);
    static CORE_API void* ReallocExternal(void* Original, SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);
    static CORE_API void FreeExternal(void* Original);
    static CORE_API SIZE_T GetAllocSizeExternal(void* Original);
    static CORE_API SIZE_T QuantizeSizeExternal(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT);
  };
}

#define INLINE_FMEMORY_OPERATION (0) // untested, but should work. Inlines FMemory::Malloc, etc

#if INLINE_FMEMORY_OPERATION
    #if PLATFORM_USES_FIXED_GMalloc_CLASS
        #error "PLATFORM_USES_FIXED_GMalloc_CLASS and INLINE_FMEMORY_OPERATION are not compatible. PLATFORM_USES_FIXED_GMalloc_CLASS is inlined below."
    #endif

    #define FMEMORY_INLINE_FUNCTION_DECORATOR FORCEINLINE
// IWYU pragma: begin_export
    #include "FMemory.inl" // HEADER_UNIT_IGNORE - Causes circular includes
// IWYU pragma: end_export
#endif

#if PLATFORM_USES_FIXED_GMalloc_CLASS && !FORCE_ANSI_ALLOCATOR && USE_MALLOC_BINNED2
    #include "HAL/MallocBinned2.h" // HEADER_UNIT_IGNORE - Causes circular includes
#endif
