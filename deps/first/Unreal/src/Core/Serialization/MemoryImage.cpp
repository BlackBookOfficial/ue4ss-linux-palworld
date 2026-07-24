// Copyright Epic Games, Inc. All Rights Reserved.

#include <Unreal/Core/Serialization/MemoryImage.hpp>
#include <Unreal/FMemory.hpp>

namespace RC::Unreal
{
    void FMemoryImageAllocatorBase::MoveToEmpty(FMemoryImageAllocatorBase& Other)
    {
        // Move allocation from Other to this
        if (Data != Other.Data)
        {
            Data = Other.Data;
            Other.Data = nullptr;
        }
    }

    FMemoryImageAllocatorBase::~FMemoryImageAllocatorBase()
    {
        if (Data)
        {
            FMemory::Free(Data);
            Data = nullptr;
        }
    }

    void FMemoryImageAllocatorBase::ResizeAllocation(int32 PreviousNumElements, int32 NumElements, SIZE_T NumBytesPerElement, uint32 Alignment)
    {
        // If we're shrinking to zero, free the allocation
        if (NumElements == 0)
        {
            if (Data)
            {
                FMemory::Free(Data);
                Data = nullptr;
            }
            return;
        }

        // Calculate new size
        const SIZE_T NewSize = NumElements * NumBytesPerElement;

        if (Data == nullptr)
        {
            // First allocation
            Data = (FScriptContainerElement*)FMemory::Malloc(NewSize, Alignment);
        }
        else
        {
            // Reallocation
            Data = (FScriptContainerElement*)FMemory::Realloc(Data, NewSize, Alignment);
        }
    }

} // namespace RC::Unreal
