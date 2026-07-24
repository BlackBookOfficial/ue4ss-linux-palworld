// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/HAL/PlatformMemory.hpp"
#include "Unreal/Core/GenericPlatform/GenericPlatformMemory.hpp"

namespace RC::Unreal
{
    struct FPlatformMemoryStats : public FGenericPlatformMemoryStats
    {
        FPlatformMemoryStats() : FGenericPlatformMemoryStats() {}
    };

    struct FLinuxPlatformMemory
        : public FGenericPlatformMemory
    {
        enum EMemoryCounterRegion
        {
            MCR_Invalid,
            MCR_Physical,
            MCR_GPU,
            MCR_GPUSystem,
            MCR_TexturePool,
            MCR_StreamingPool,
            MCR_UsedStreamingPool,
            MCR_GPUDefragPool,
            MCR_SamplePlatformSpecifcMemoryRegion,
            MCR_PhysicalLLM,
            MCR_MAX
        };

        static CORE_API FPlatformMemoryStats GetStats();
        static CORE_API const FPlatformMemoryConstants& GetConstants();
        static CORE_API bool PageProtect(void* const Ptr, const SIZE_T Size, const bool bCanRead, const bool bCanWrite);
        static CORE_API void* BinnedAllocFromOS(SIZE_T Size);
        static CORE_API void BinnedFreeToOS(void* Ptr, SIZE_T Size);

        class FPlatformVirtualMemoryBlock : public FBasicVirtualMemoryBlock
        {
        public:
            FPlatformVirtualMemoryBlock() = default;
            FPlatformVirtualMemoryBlock(void *InPtr, uint32 InVMSizeDivVirtualSizeAlignment)
                : FBasicVirtualMemoryBlock(InPtr, InVMSizeDivVirtualSizeAlignment) {}
            FPlatformVirtualMemoryBlock(const FPlatformVirtualMemoryBlock& Other) = default;
            FPlatformVirtualMemoryBlock& operator=(const FPlatformVirtualMemoryBlock& Other) = default;

            void Commit(size_t InOffset, size_t InSize);
            void Decommit(size_t InOffset, size_t InSize);
            void FreeVirtual();

            FORCEINLINE void CommitByPtr(void *InPtr, size_t InSize) { Commit(size_t(((uint8*)InPtr) - ((uint8*)Ptr)), InSize); }
            FORCEINLINE void DecommitByPtr(void *InPtr, size_t InSize) { Decommit(size_t(((uint8*)InPtr) - ((uint8*)Ptr)), InSize); }
            FORCEINLINE void Commit() { Commit(0, GetActualSize()); }
            FORCEINLINE void Decommit() { Decommit(0, GetActualSize()); }
            FORCEINLINE size_t GetActualSize() const { return VMSizeDivVirtualSizeAlignment * GetVirtualSizeAlignment(); }

            static FPlatformVirtualMemoryBlock AllocateVirtual(size_t Size, size_t InAlignment = FPlatformVirtualMemoryBlock::GetVirtualSizeAlignment());
            static size_t GetCommitAlignment();
            static size_t GetVirtualSizeAlignment();
        };
    };

    typedef FLinuxPlatformMemory FPlatformMemory;
}
