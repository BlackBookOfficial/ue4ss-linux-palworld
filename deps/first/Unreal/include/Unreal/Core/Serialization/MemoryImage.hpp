// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/Core/Containers/ContainerAllocationPolicies.hpp>

namespace RC::Unreal
{
    /**
     * Base allocator class for memory image containers
     * This is a simplified version that provides the basic interface needed for TMemoryImageAllocator
     */
    class RC_UE_API FMemoryImageAllocatorBase
    {
    public:
        FMemoryImageAllocatorBase() = default;
        FMemoryImageAllocatorBase(const FMemoryImageAllocatorBase&) = delete;
        FMemoryImageAllocatorBase& operator=(const FMemoryImageAllocatorBase&) = delete;

        /**
         * Moves the state of another allocator into this one.
         * Assumes that the allocator is currently empty.
         */
        void MoveToEmpty(FMemoryImageAllocatorBase& Other);

        /** Destructor */
        ~FMemoryImageAllocatorBase();

        // FContainerAllocatorInterface
        inline FScriptContainerElement* GetAllocation() const
        {
            return Data;
        }

        inline SIZE_T GetAllocatedSize(int32 CurrentMax, SIZE_T NumBytesPerElement) const
        {
            return CurrentMax * NumBytesPerElement;
        }

        inline bool HasAllocation() const
        {
            return Data != nullptr;
        }

        void ResizeAllocation(int32 PreviousNumElements, int32 NumElements, SIZE_T NumBytesPerElement, uint32 Alignment);

    private:
        FScriptContainerElement* Data = nullptr;
    };

    /**
     * Memory image allocator for containers that can be frozen/unfrozen
     * This allocator is compatible with TArray, TMap, TSet and can be used for memory-mapped data structures
     *
     * Template parameter Alignment specifies the alignment requirement for allocations
     */
    template<uint32 Alignment = DEFAULT_ALIGNMENT>
    class TMemoryImageAllocator
    {
    public:
        using SizeType = int32;

        enum { NeedsElementType = false };
        enum { RequireRangeCheck = true };
        enum { SupportsFreezeMemoryImage = true };

        class ForAnyElementType : public FMemoryImageAllocatorBase
        {
        public:
            /** Default constructor */
            ForAnyElementType() = default;

            inline SizeType GetInitialCapacity() const
            {
                return 0;
            }

            inline int32 CalculateSlackReserve(int32 NewMax, int32 NumBytesPerElement) const
            {
                return DefaultCalculateSlackReserve(NewMax, NumBytesPerElement, true, Alignment);
            }

            inline int32 CalculateSlackReserve(int32 NewMax, int32 NumBytesPerElement, uint32 AlignmentOfElement) const
            {
                return DefaultCalculateSlackReserve(NewMax, NumBytesPerElement, true, AlignmentOfElement);
            }

            inline int32 CalculateSlackShrink(int32 NewMax, int32 CurrentMax, int32 NumBytesPerElement) const
            {
                return DefaultCalculateSlackShrink(NewMax, CurrentMax, NumBytesPerElement, true, Alignment);
            }

            inline int32 CalculateSlackShrink(int32 NewMax, int32 CurrentMax, int32 NumBytesPerElement, uint32 AlignmentOfElement) const
            {
                return DefaultCalculateSlackShrink(NewMax, CurrentMax, NumBytesPerElement, true, AlignmentOfElement);
            }

            inline int32 CalculateSlackGrow(int32 NewMax, int32 CurrentMax, int32 NumBytesPerElement) const
            {
                return DefaultCalculateSlackGrow(NewMax, CurrentMax, NumBytesPerElement, true, Alignment);
            }

            inline int32 CalculateSlackGrow(int32 NewMax, int32 CurrentMax, int32 NumBytesPerElement, uint32 AlignmentOfElement) const
            {
                return DefaultCalculateSlackGrow(NewMax, CurrentMax, NumBytesPerElement, true, AlignmentOfElement);
            }

            inline void ResizeAllocation(int32 CurrentNum, int32 NewMax, SIZE_T NumBytesPerElement)
            {
                FMemoryImageAllocatorBase::ResizeAllocation(CurrentNum, NewMax, NumBytesPerElement, Alignment);
            }

            inline void ResizeAllocation(int32 CurrentNum, int32 NewMax, SIZE_T NumBytesPerElement, uint32 AlignmentOfElement)
            {
                FMemoryImageAllocatorBase::ResizeAllocation(CurrentNum, NewMax, NumBytesPerElement, AlignmentOfElement);
            }
        };

        template<typename ElementType>
        class ForElementType : public ForAnyElementType
        {
        public:
            ForElementType() = default;
            inline ElementType* GetAllocation() const
            {
                return (ElementType*)ForAnyElementType::GetAllocation();
            }
        };
    };

    /**
     * Allocator traits for TMemoryImageAllocator
     */
    template <uint32 Alignment>
    struct TAllocatorTraits<TMemoryImageAllocator<Alignment>> : TAllocatorTraitsBase<TMemoryImageAllocator<Alignment>>
    {
        enum { IsZeroConstruct = true };
        enum { SupportsFreezeMemoryImage = true };
        enum { SupportsElementAlignment = true };
    };

    /**
     * Default memory image allocator with default alignment
     */
    using FMemoryImageAllocator = TMemoryImageAllocator<>;

    /**
     * Memory image allocator for sparse arrays
     */
    using FMemoryImageSparseArrayAllocator = TSparseArrayAllocator<FMemoryImageAllocator, FMemoryImageAllocator>;

    /**
     * Memory image allocator for sets
     */
    using FMemoryImageSetAllocator = TSetAllocator<FMemoryImageSparseArrayAllocator, FMemoryImageAllocator>;

    /**
     * TArray using memory image allocator
     */
    template<typename T>
    using TMemoryImageArray = TArray<T, FMemoryImageAllocator>;

    /**
     * TSet using memory image allocator
     */
    template<typename ElementType, typename KeyFuncs = DefaultKeyFuncs<ElementType>>
    using TMemoryImageSet = TSet<ElementType, KeyFuncs, FMemoryImageSetAllocator>;

    /**
     * TMap using memory image allocator
     */
    template <typename KeyType, typename ValueType, typename KeyFuncs = TDefaultMapHashableKeyFuncs<KeyType, ValueType, false>>
    using TMemoryImageMap = TMap<KeyType, ValueType, FMemoryImageSetAllocator, KeyFuncs>;

} // namespace RC::Unreal
