// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/HAL/PlatformAtomics.hpp"
#include "Unreal/Core/HAL/PlatformCrt.hpp"
#include "Unreal/Core/Templates/Atomic.hpp"

namespace RC::Unreal
{
    class UWorld;
    template <typename T> class TAtomic;

    #ifndef UPDATE_MALLOC_STATS
    #define UPDATE_MALLOC_STATS 1
    #endif

    enum
    {
        // Default allocator alignment. If the default is specified, the allocator applies to engine rules.
        // Blocks >= 16 bytes will be 16-byte-aligned, Blocks < 16 will be 8-byte aligned. If the allocator does
        // not support allocation alignment, the alignment will be ignored.
        DEFAULT_ALIGNMENT = 0,

        // Minimum allocator alignment
        MIN_ALIGNMENT = 8,
    };


    /** The global memory allocator. */
    CORE_API extern class FMalloc** GMalloc;

    /** Holds generic memory stats, internally implemented as a map. */
    struct FGenericMemoryStats;


    /**
     * Inherit from FUseSystemMallocForNew if you want your objects to be placed in memory
     * alloced by the system malloc routines, bypassing GMalloc. This is e.g. used by FMalloc
     * itself.
     */
    class FUseSystemMallocForNew
    {
    public:
        /**
         * Overloaded new operator using the system allocator.
         *
         * @param    Size    Amount of memory to allocate (in bytes)
         * @return            A pointer to a block of memory with size Size or nullptr
         */
        CORE_API void* operator new(size_t Size);

        /**
         * Overloaded delete operator using the system allocator
         *
         * @param    Ptr        Pointer to delete
         */
        CORE_API void operator delete(void* Ptr);

        /**
         * Overloaded array new operator using the system allocator.
         *
         * @param    Size    Amount of memory to allocate (in bytes)
         * @return            A pointer to a block of memory with size Size or nullptr
         */
        void* operator new[](size_t Size);

        /**
         * Overloaded array delete operator using the system allocator
         *
         * @param    Ptr        Pointer to delete
         */
        void operator delete[](void* Ptr);
    };
}