#pragma once

#include <functional>
#include <stdexcept>
#include <type_traits>
#include <unordered_set>
#include <tuple>
#include <ranges>

#include <Constructs/Generator.hpp>
#include <DynamicOutput/Output.hpp>
#include <Helpers/Format.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/Core/Templates/ChooseClass.hpp>
#include <Unreal/Core/Containers/ContainersFwd.hpp>
#include <Unreal/Core/Containers/ContainerAllocationPolicies.hpp>
#include <Unreal/Core/Containers/ContainerElementTypeCompatibility.hpp>
#include <Unreal/FMemory.hpp>
#include <Unreal/UnrealFlags.hpp>
#include <Unreal/TypeChecker.hpp>
#include <Unreal/Core/Templates/MemoryOps.hpp>
#include <Unreal/Core/Templates/UnrealTemplate.hpp>
#include <Unreal/Core/Containers/AllowShrinking.hpp>
#include <Unreal/Core/Templates/EnableIf.hpp>
#include <Unreal/Core/Templates/IsAbstract.hpp>
#include <Unreal/Core/Templates/IsConstructible.hpp>
#include <Unreal/Core/Templates/IsSigned.hpp>
#include <Unreal/Core/Templates/MakeUnsigned.hpp>
#include <Unreal/Core/Misc/AssertionMacros.hpp>

#include <Unreal/Core/Templates/Invoke.hpp>
#include <Unreal/Core/Templates/LosesQualifiersFromTo.hpp>
#include <Unreal/Core/Templates/Sorting.hpp>
// UE4SS CHANGE -> START
#include <Unreal/Core/Algo/StableSort.hpp>

// UE4SS CHANGE -> END

namespace RC::Unreal
{
    /**
     * Generic iterator which can operate on types that expose the following:
     * - A type called ElementType representing the contained type.
     * - A method SizeType Num() const that returns the number of items in the container.
     * - A method bool IsValidIndex(SizeType index) which returns whether a given index is valid in the container.
     * - A method T& operator\[\](SizeType index) which returns a reference to a contained object by index.
     * - A method void RemoveAt(SizeType index) which removes the element at index
     */
    template< typename ContainerType, typename ElementType, typename SizeType>
    class TIndexedContainerIterator
    {
    public:
        TIndexedContainerIterator(ContainerType& InContainer, SizeType StartIndex = 0)
            : Container(InContainer)
            , Index    (StartIndex)
        {
        }

        /** Advances iterator to the next element in the container. */
        TIndexedContainerIterator& operator++()
        {
            ++Index;
            return *this;
        }
        TIndexedContainerIterator operator++(int)
        {
            TIndexedContainerIterator Tmp(*this);
            ++Index;
            return Tmp;
        }

        /** Moves iterator to the previous element in the container. */
        TIndexedContainerIterator& operator--()
        {
            --Index;
            return *this;
        }
        TIndexedContainerIterator operator--(int)
        {
            TIndexedContainerIterator Tmp(*this);
            --Index;
            return Tmp;
        }

        /** iterator arithmetic support */
        TIndexedContainerIterator& operator+=(SizeType Offset)
        {
            Index += Offset;
            return *this;
        }

        TIndexedContainerIterator operator+(SizeType Offset) const
        {
            TIndexedContainerIterator Tmp(*this);
            return Tmp += Offset;
        }

        TIndexedContainerIterator& operator-=(SizeType Offset)
        {
            return *this += -Offset;
        }

        TIndexedContainerIterator operator-(SizeType Offset) const
        {
            TIndexedContainerIterator Tmp(*this);
            return Tmp -= Offset;
        }

        ElementType& operator* () const
        {
            return Container[ Index ];
        }

        ElementType* operator->() const
        {
            return &Container[ Index ];
        }

        /** conversion to "bool" returning true if the iterator has not reached the last element. */
        FORCEINLINE explicit operator bool() const
        {
            return Container.IsValidIndex(Index);
        }

        /** Returns an index to the current element. */
        SizeType GetIndex() const
        {
            return Index;
        }

        /** Resets the iterator to the first element. */
        void Reset()
        {
            Index = 0;
        }

        /** Sets iterator to the last element. */
        void SetToEnd()
        {
            Index = Container.Num();
        }
        
        /** Removes current element in array. This invalidates the current iterator value and it must be incremented */
        void RemoveCurrent()
        {
            Container.RemoveAt(Index);
            Index--;
        }

        FORCEINLINE friend bool operator==(const TIndexedContainerIterator& Lhs, const TIndexedContainerIterator& Rhs) { return &Lhs.Container == &Rhs.Container && Lhs.Index == Rhs.Index; }
        FORCEINLINE friend bool operator!=(const TIndexedContainerIterator& Lhs, const TIndexedContainerIterator& Rhs) { return &Lhs.Container != &Rhs.Container || Lhs.Index != Rhs.Index; }

    private:

        ContainerType& Container;
        SizeType      Index;
    };

    /** operator + */
    template <typename ContainerType, typename ElementType, typename SizeType>
    FORCEINLINE TIndexedContainerIterator<ContainerType, ElementType, SizeType> operator+(SizeType Offset, TIndexedContainerIterator<ContainerType, ElementType, SizeType> RHS)
    {
        return RHS + Offset;
    }



    /**
     * Pointer-like iterator type for ranged-for loops which checks that the
     * container hasn't been resized during iteration.
     */
    template <typename ElementType, typename SizeType>
    struct TCheckedPointerIterator
    {
        // This iterator type only supports the minimal functionality needed to support
        // C++ ranged-for syntax.  For example, it does not provide post-increment ++ nor ==.
        //
        // We do add an operator-- to help FString implementation

        explicit TCheckedPointerIterator(const SizeType& InNum, ElementType* InPtr)
            : Ptr       (InPtr)
            , CurrentNum(InNum)
            , InitialNum(InNum)
        {
        }

        FORCEINLINE ElementType& operator*() const
        {
            return *Ptr;
        }

        FORCEINLINE TCheckedPointerIterator& operator++()
        {
            ++Ptr;
            return *this;
        }

        FORCEINLINE TCheckedPointerIterator& operator--()
        {
            --Ptr;
            return *this;
        }

    private:
        ElementType*    Ptr;
        const SizeType& CurrentNum;
        SizeType        InitialNum;

        FORCEINLINE friend bool operator!=(const TCheckedPointerIterator& Lhs, const TCheckedPointerIterator& Rhs)
        {
            // We only need to do the check in this operator, because no other operator will be
            // called until after this one returns.
            //
            // Also, we should only need to check one side of this comparison - if the other iterator isn't
            // even from the same array then the compiler has generated bad code.
            /*if (Lhs.CurrentNum != Lhs.InitialNum) // Commenting out this check as it is not an exception in UE and happens quite often.
            {
                Output::send<LogLevel::Warning>(STR("Array has changed during ranged-for iteration!\n"));
            }*/
            return Lhs.Ptr != Rhs.Ptr;
        }
    };


    template <typename ElementType, typename IteratorType>
    struct TDereferencingIterator
    {
        explicit TDereferencingIterator(IteratorType InIter)
            : Iter(InIter)
        {
        }

        FORCEINLINE ElementType& operator*() const
        {
            return *(ElementType*)*Iter;
        }

        FORCEINLINE TDereferencingIterator& operator++()
        {
            ++Iter;
            return *this;
        }

    private:
        IteratorType Iter;

        FORCEINLINE friend bool operator!=(const TDereferencingIterator& Lhs, const TDereferencingIterator& Rhs)
        {
            return Lhs.Iter != Rhs.Iter;
        }
    };

    namespace UE::Core::Private
    {
        // Simply forwards to an unqualified GetData(), but can be called from within a container or view
        // where GetData() is already a member and so hides any others.
        template <typename T>
        [[nodiscard]] FORCEINLINE decltype(auto) GetDataHelper(T&& Arg)
        {
            return GetData(Forward<T>(Arg));
        }

        template <typename FromArrayType, typename ToArrayType>
        UE_NODEBUG [[nodiscard]] constexpr bool CanMoveTArrayPointersBetweenArrayTypes()
        {
            using FromAllocatorType          = typename FromArrayType::AllocatorType;
            using ToAllocatorType            = typename ToArrayType::AllocatorType;
            using FromElementType            = typename FromArrayType::ElementType;
            using ToElementType              = typename ToArrayType::ElementType;
            using UnqualifiedFromElementType = std::remove_cv_t<FromElementType>;
            using UnqualifiedToElementType   = std::remove_cv_t<ToElementType>;

            // Allocators must be equal or move-compatible...
            if constexpr (std::is_same_v<FromAllocatorType, ToAllocatorType> || TCanMoveBetweenAllocators<FromAllocatorType, ToAllocatorType>::Value)
            {
                return
                    !TLosesQualifiersFromTo_V<FromElementType, ToElementType> &&
                    (
                        std::is_same_v         <const ToElementType, const FromElementType> ||               // The element type of the container must be the same, or...
                        TIsBitwiseConstructible<UnqualifiedToElementType, UnqualifiedFromElementType>::Value // ... the element type of the source container must be bitwise constructible from the element type in the destination container
                    );
            }
            else
            {
                return false;
            }
        }

        // Assume elements are compatible with themselves - avoids problems with generated copy
        // constructors of arrays of forwarded types, e.g.:
        //
        // struct FThing;
        //
        // struct FOuter
        // {
        //     TArray<FThing> Arr; // this will cause errors without this workaround
        // };
        template <typename DestType, typename SourceType>
        constexpr bool TArrayElementsAreCompatible_V = std::disjunction_v<std::is_same<DestType, std::decay_t<SourceType>>, std::is_constructible<DestType, SourceType>>;

        template <typename ElementType, typename AllocatorType>
        UE_NODEBUG static char (&ResolveIsTArrayPtr(const volatile TArray<ElementType, AllocatorType>*))[2];
        UE_NODEBUG static char(&ResolveIsTArrayPtr(...))[1];

        template <typename T>
        constexpr bool TIsTArrayOrDerivedFromTArray_V = sizeof(ResolveIsTArrayPtr((T*)nullptr)) == 2;

        [[noreturn]] CORE_API void OnInvalidArrayNum(unsigned long long NewNum);

        // A hacky way to get the SizeType, since it's defined in the
        // (outer) allocator type, not the (inner) allocator instance type
        template <typename AllocatorInstanceType>
        using TAllocatorSizeType_T = decltype(std::declval<AllocatorInstanceType&>().GetInitialCapacity());

        // Flags are passed as a uint32 to minimize PDB impact of these generated symbols.
        //
        // 1 == TAllocatorTraits<>::SupportsElementAlignment
        // 2 == TAllocatorTraits<>::SupportsSlackTracking
        //
        // When C++20 is guaranteed, concept checks can be used instead.
        template <typename AllocatorType>
        UE_NODEBUG [[nodiscard]] constexpr uint32 GetAllocatorFlags()
        {
            uint32 Result = 0;
            if constexpr (TAllocatorTraits<AllocatorType>::SupportsElementAlignment)
            {
                Result |= 1;
            }
            if constexpr (TAllocatorTraits<AllocatorType>::SupportsSlackTracking)
            {
                Result |= 2;
            }
            return Result;
        }

        
        // Called only when we KNOW we are going to do a realloc increasing by 1.
        // In this case, we know that max == num and can simplify things in a very 
        // hot location in the code.
        // This returns the old ArrayMax in order to save a register clobber/reload.
        template <uint32 Flags, typename AllocatorInstanceType>
        FORCEINLINE TAllocatorSizeType_T<AllocatorInstanceType> ReallocGrow1_DoAlloc_Impl(
            uint32                                       ElementSize,
            uint32                                       ElementAlignment,
            AllocatorInstanceType&                       AllocatorInstance,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayMax
        )
        {        
            using SizeType  = TAllocatorSizeType_T<AllocatorInstanceType>;
            using USizeType = std::make_unsigned_t<SizeType>;

            const USizeType UOldMax = (USizeType)ArrayMax;
            const USizeType UNewNum = UOldMax + 1U;
            const SizeType  OldMax  = (SizeType)UOldMax;
            const SizeType  NewNum  = (SizeType)UNewNum;
            
            // This should only happen when we've underflowed or overflowed SizeType
            if (NewNum < OldMax)
            {
                OnInvalidArrayNum((unsigned long long)UNewNum);
            }

            SizeType NewMax;
            if constexpr (!!(Flags & 1)) // TAllocatorTraits<AllocatorType>::SupportsElementAlignment
            {
                NewMax = AllocatorInstance.CalculateSlackGrow(NewNum, OldMax, ElementSize, ElementAlignment);
                AllocatorInstance.ResizeAllocation(UOldMax, NewMax, ElementSize, ElementAlignment);
            }
            else
            {
                NewMax = AllocatorInstance.CalculateSlackGrow(NewNum, OldMax, ElementSize);
                AllocatorInstance.ResizeAllocation(UOldMax, NewMax, ElementSize);
            }
            ArrayMax = NewMax;
            #if UE_ENABLE_ARRAY_SLACK_TRACKING
            if constexpr (!!(Flags & 2)) // TAllocatorTraits<AllocatorType>::SupportsSlackTracking
            {
                AllocatorInstance.SlackTrackerLogNum(NewNum);
            }
            #endif

            return OldMax;
        }

        // Version for small sizes/alignments. This allows the parameter setup to be a single instruction
        // note the uint16 limitation allows for a single instruction setup on arm.
        template <uint32 Flags, typename AllocatorInstanceType>
        FORCENOINLINE TAllocatorSizeType_T<AllocatorInstanceType> ReallocGrow1_DoAlloc_Tiny(
            uint16                                       ElementSizeAndAlignment,
            AllocatorInstanceType&                       AllocatorInstance,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayMax
        )
        {
            return ReallocGrow1_DoAlloc_Impl<Flags, AllocatorInstanceType>(ElementSizeAndAlignment & 0xff, ElementSizeAndAlignment >> 8, AllocatorInstance, ArrayMax);        
        }

        template <uint32 Flags, typename AllocatorInstanceType>
        FORCENOINLINE TAllocatorSizeType_T<AllocatorInstanceType> ReallocGrow1_DoAlloc(
            uint32                                       ElementSize,
            uint32                                       ElementAlignment,
            AllocatorInstanceType&                       AllocatorInstance,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayMax
        )
        {
            return ReallocGrow1_DoAlloc_Impl<Flags, AllocatorInstanceType>(ElementSize, ElementAlignment, AllocatorInstance, ArrayMax);        
        }

        // This should be used for repeated growing operations when reallocations are to be amortized over multiple inserts.
        template <uint32 Flags, typename AllocatorInstanceType>
        FORCENOINLINE TAllocatorSizeType_T<AllocatorInstanceType> ReallocGrow(
            uint32                                       ElementSize,
            uint32                                       ElementAlignment,
            TAllocatorSizeType_T<AllocatorInstanceType>  Count,
            AllocatorInstanceType&                       AllocatorInstance,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayNum,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayMax
        )
        {
            using SizeType  = TAllocatorSizeType_T<AllocatorInstanceType>;
            using USizeType = std::make_unsigned_t<SizeType>;

            const USizeType UCount  = (USizeType)Count;
            const USizeType UOldNum = (USizeType)ArrayNum;
            const USizeType UOldMax = (USizeType)ArrayMax;
            const USizeType UNewNum = UOldNum + UCount;
            const SizeType  OldNum  = (SizeType)UOldNum;
            const SizeType  OldMax  = (SizeType)UOldMax;
            const SizeType  NewNum  = (SizeType)UNewNum;

            checkSlow((OldNum >= 0) & (OldMax >= OldNum) & (Count >= 0)); // & for one branch

            ArrayNum = NewNum;

    #if DO_GUARD_SLOW
            if (UNewNum > UOldMax)
    #else
            // SECURITY - This check will guard against negative counts too, in case the checkSlow above is compiled out.
            // However, it results in slightly worse code generation.
            if (UCount > UOldMax - UOldNum)
    #endif
            {
                // This should only happen when we've underflowed or overflowed SizeType
                if (NewNum < OldNum)
                {
                    OnInvalidArrayNum((unsigned long long)UNewNum);
                }
                SizeType NewMax;
                if constexpr (!!(Flags & 1)) // TAllocatorTraits<AllocatorType>::SupportsElementAlignment
                {
                    NewMax = AllocatorInstance.CalculateSlackGrow(NewNum, OldMax, ElementSize, ElementAlignment);
                    AllocatorInstance.ResizeAllocation(UOldNum, NewMax, ElementSize, ElementAlignment);
                }
                else
                {
                    NewMax = AllocatorInstance.CalculateSlackGrow(NewNum, OldMax, ElementSize);
                    AllocatorInstance.ResizeAllocation(UOldNum, NewMax, ElementSize);
                }
                ArrayMax = NewMax;
    #if UE_ENABLE_ARRAY_SLACK_TRACKING
                if constexpr (!!(Flags & 2)) // TAllocatorTraits<AllocatorType>::SupportsSlackTracking
                {
                    AllocatorInstance.SlackTrackerLogNum(NewNum);
                }
    #endif
            }

            return OldNum;
        }

        // This should be used for repeated shrinking operations when reallocations are to be amortized over multiple removals.
        template <uint32 Flags, typename AllocatorInstanceType>
        FORCENOINLINE void ReallocShrink(
            uint32                                       ElementSize,
            uint32                                       ElementAlignment,
            AllocatorInstanceType&                       AllocatorInstance,
            TAllocatorSizeType_T<AllocatorInstanceType>  ArrayNum,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayMax
        )
        {
            using SizeType  = TAllocatorSizeType_T<AllocatorInstanceType>;

            SizeType OldArrayMax = ArrayMax;

            if constexpr (!!(Flags & 1)) // TAllocatorTraits<AllocatorType>::SupportsElementAlignment
            {
                SizeType NewArrayMax = AllocatorInstance.CalculateSlackShrink(ArrayNum, OldArrayMax, ElementSize, ElementAlignment);
                if (NewArrayMax != OldArrayMax)
                {
                    ArrayMax = NewArrayMax;
                    AllocatorInstance.ResizeAllocation(ArrayNum, NewArrayMax, ElementSize, ElementAlignment);
                }
            }
            else
            {
                SizeType NewArrayMax = AllocatorInstance.CalculateSlackShrink(ArrayNum, OldArrayMax, ElementSize);
                if (NewArrayMax != OldArrayMax)
                {
                    ArrayMax = NewArrayMax;
                    AllocatorInstance.ResizeAllocation(ArrayNum, NewArrayMax, ElementSize);
                }
            }
        }

        // This should be used for setting an allocation to a specific size.
        // Precondition: NewMax >= ArrayNum.
        template <uint32 Flags, typename AllocatorInstanceType>
        FORCENOINLINE void ReallocTo(
            uint32                                       ElementSize,
            uint32                                       ElementAlignment,
            TAllocatorSizeType_T<AllocatorInstanceType>  NewMax,
            AllocatorInstanceType&                       AllocatorInstance,
            TAllocatorSizeType_T<AllocatorInstanceType>  ArrayNum,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayMax
        )
        {
            if constexpr (!!(Flags & 1)) // TAllocatorTraits<AllocatorType>::SupportsElementAlignment
            {
                if (NewMax)
                {
                    NewMax = AllocatorInstance.CalculateSlackReserve(NewMax, ElementSize, ElementAlignment);
                }
                if (NewMax != ArrayMax)
                {
                    ArrayMax = NewMax;
                    AllocatorInstance.ResizeAllocation(ArrayNum, NewMax, ElementSize, ElementAlignment);
                }
            }
            else
            {
                if (NewMax)
                {
                    NewMax = AllocatorInstance.CalculateSlackReserve(NewMax, ElementSize);
                }
                if (NewMax != ArrayMax)
                {
                    ArrayMax = NewMax;
                    AllocatorInstance.ResizeAllocation(ArrayNum, NewMax, ElementSize);
                }
            }
        }

        template <uint32 Flags, typename AllocatorInstanceType>
        FORCENOINLINE void ReallocForCopy(
            uint32                                       ElementSize,
            uint32                                       ElementAlignment,
            TAllocatorSizeType_T<AllocatorInstanceType>  NewMax,
            TAllocatorSizeType_T<AllocatorInstanceType>  PrevMax,
            AllocatorInstanceType&                       AllocatorInstance,
            TAllocatorSizeType_T<AllocatorInstanceType>  ArrayNum,
            TAllocatorSizeType_T<AllocatorInstanceType>& ArrayMax
        )
        {
            if constexpr (!!(Flags & 1)) // TAllocatorTraits<AllocatorType>::SupportsElementAlignment
            {
                if (NewMax)
                {
                    NewMax = AllocatorInstance.CalculateSlackReserve(NewMax, ElementSize, ElementAlignment);
                }
                if (NewMax > PrevMax)
                {
                    AllocatorInstance.ResizeAllocation(0, NewMax, ElementSize, ElementAlignment);
                }
                else
                {
                    NewMax = PrevMax;
                }
            }
            else
            {
                if (NewMax)
                {
                    NewMax = AllocatorInstance.CalculateSlackReserve(NewMax, ElementSize);
                }
                if (NewMax > PrevMax)
                {
                    AllocatorInstance.ResizeAllocation(0, NewMax, ElementSize);
                }
                else
                {
                    NewMax = PrevMax;
                }
            }
            ArrayMax = NewMax;
        }

    }

    namespace UE4Array_Private
    {
        template <typename FromArrayType, typename ToArrayType>
        constexpr bool CanMoveTArrayPointersBetweenArrayTypes()
        {
            typedef typename FromArrayType::AllocatorType FromAllocatorType;
            typedef typename ToArrayType::AllocatorType ToAllocatorType;
            typedef typename FromArrayType::ElementType   FromElementType;
            typedef typename ToArrayType::ElementType   ToElementType;

            // Allocators must be equal or move-compatible...
            if constexpr (std::is_same_v<FromAllocatorType, ToAllocatorType> || TCanMoveBetweenAllocators<FromAllocatorType, ToAllocatorType>::Value)
            {
                return
                    std::is_same_v         <ToElementType, FromElementType> ||      // The element type of the container must be the same, or...
                    TIsBitwiseConstructible<ToElementType, FromElementType>::Value; // ... the element type of the source container must be bitwise constructible from the element type in the destination container
            }
            else
            {
                return false;
            }
        }

        // Assume elements are compatible with themselves - avoids problems with generated copy
        // constuctors of arrays of forwarded types, e.g.:
        //
        // struct FThing;
        //
        // struct FOuter
        // {
        //     TArray<FThing> Arr; // this will cause errors without this workaround
        // };
        //
        // This should be changed to use std::disjunction and std::is_constructible, and the usage
        // changed to use ::value instead of ::Value, when std::disjunction (C++17) is available everywhere.
        template <typename DestType, typename SourceType>
        using TArrayElementsAreCompatible = TOrValue<std::is_same<DestType, std::decay_t<DestType>>::value, TIsConstructible<DestType, SourceType>>;
    }

    // Redo or remove this, need to think about it
    // maybe a concept for structs which have a dynamic array size?
    template<typename ElementType>
    constexpr bool ArraySizeIsImplicit = !(std::is_same_v<ElementType, struct FAssetData> ||
                                           std::is_same_v<ElementType, struct FVector> ||
                                           std::is_same_v<ElementType, struct FQuat> ||
                                           std::is_same_v<ElementType, class FFieldVariant> ||
                                           std::is_same_v<ElementType, class FText>);

    template<typename ElementType, bool Const = false>
    struct TRangeBasedIterator
    {
        using iterator_category = std::contiguous_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = ElementType;
        using pointer = std::conditional_t<Const, ElementType const*, ElementType*>;
        using reference = std::conditional_t<Const, ElementType const&, ElementType&>;

        using data_ptr = std::conditional_t<Const, void const*, void*>;
        using data_char_ptr = std::conditional_t<Const, uint8 const*, uint8*>;

        TRangeBasedIterator() = default;
        explicit TRangeBasedIterator(data_ptr DataPtr) : DataPtr(DataPtr) {
        }

        reference operator*() const { return *static_cast<pointer>(DataPtr); }
        pointer operator->() { return static_cast<pointer>(DataPtr); }

        TRangeBasedIterator& operator++()
        {
            DataPtr = static_cast<data_ptr>(static_cast<data_char_ptr>(DataPtr) + GetTypeSize());
            return *this;
        }

        TRangeBasedIterator operator++(int)
        {
            TRangeBasedIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr bool operator==(const TRangeBasedIterator& Other) const
        {
            return DataPtr == Other.DataPtr;
        }

        constexpr bool operator!=(const TRangeBasedIterator& Other) const
        {
            return !(*this == Other);
        }

    private:
        /** 
         * Helper function returning the size of the inner type.
         *
         * @returns Size in bytes of array type.
         */
        FORCEINLINE uint32 GetTypeSize() const
        {
            if constexpr (!ArraySizeIsImplicit<ElementType>)
            {
                // Structs where the size is unknown to the compiler
                // This happens when a struct has had layout changes and now has different sizes in different engine versions
                return ElementType::StaticSize();
            }
            else
            {
                // Structs where the size is known to the compiler
                return sizeof(ElementType);
            }
        }

    private:
        data_ptr DataPtr;
    };

    // todo: Copy TArray from unreal source and annotate every UE4SS specific change with comments
    /*
     * Problems with TArray:
     *
     * The TArray destructor doesn't call element destructors.
     *
     * You can't create a new TArray in the games memory.
     */
    /**
     * Templated dynamic array
     *
     * A dynamically sized array of typed elements.  Makes the assumption that your elements are relocate-able; 
     * i.e. that they can be transparently moved to new memory without a copy constructor.  The main implication 
     * is that pointers to elements in the TArray may be invalidated by adding or removing other elements to the array. 
     * Removal of elements is O(N) and invalidates the indices of subsequent elements.
     *
     * Caution: as noted below some methods are not safe for element types that require constructors.
     *
     **/
    template<typename InElementType, typename InAllocator>
    class TArray
    {
    public:
        static constexpr InternalType internal_type = InternalType::Array;
        using SizeType = typename InAllocator::SizeType;
        using ElementType = InElementType;
        using Allocator = InAllocator;
        using AllocatorType = InAllocator;

    private:
        using USizeType = typename TMakeUnsigned<SizeType>::Type;

    public:
        typedef typename TChooseClass<
                Allocator::NeedsElementType,
                typename Allocator::template ForElementType<ElementType>,
                typename Allocator::ForAnyElementType
        >::Result ElementAllocatorType;

        static_assert(TIsSigned<SizeType>::Value, "TArray only supports signed index types");

        /**
         * Constructor, initializes element number counters.
         */
        FORCEINLINE TArray()
            : ArrayNum(0)
            , ArrayMax(AllocatorInstance.GetInitialCapacity())
        {}

    protected:
        ElementAllocatorType AllocatorInstance{};
        SizeType ArrayNum{};
        SizeType ArrayMax{};

    public:
        // Custom constructor for when we already have a TArray in memory, and we'd just like to take it over
        //TArray(ArrayInnerType* data_ptr, SizeType current_size, SizeType capacity) : data(data_ptr), ArrayNum(current_size),
        //                                                                           ArrayMax(capacity) {}

        TArray([[maybe_unused]]InElementType* data_ptr, SizeType current_size, SizeType capacity) : ArrayNum(current_size), ArrayMax(capacity)
        {
            // This is currently used in FString to allow construction of strings
            AllocatorInstance.Data = std::bit_cast<FScriptContainerElement*>(data_ptr);
        }

        /**
         * Constructor from a raw array of elements.
         *
         * @param Ptr   A pointer to an array of elements to copy.
         * @param Count The number of elements to copy from Ptr.
         * @see Append
         */
        FORCEINLINE TArray(const ElementType* Ptr, SizeType Count)
        {
            if (Count < 0)
            {
                // Cast to USizeType first to prevent sign extension on negative sizes, producing unusually large values.
                UE::Core::Private::OnInvalidArrayNum((unsigned long long)(USizeType)Count);
            }
            
            check(Ptr != nullptr || Count == 0);

            CopyToEmpty(Ptr, Count, 0, 0);
        }
        
        template <typename OtherElementType, typename OtherSizeType>
        explicit TArray(const TArrayView<OtherElementType, OtherSizeType>& Other);

        /**
         * Initializer list constructor
         */
        TArray(std::initializer_list<InElementType> InitList)
        {
            // This is not strictly legal, as std::initializer_list's iterators are not guaranteed to be pointers, but
            // this appears to be the case on all of our implementations.  Also, if it's not true on a new implementation,
            // it will fail to compile rather than behave badly.
            CopyToEmpty(InitList.begin(), (SizeType)InitList.size(), 0, 0);
        }

        /**
         * Copy constructor with changed allocator. Use the common routine to perform the copy.
         *
         * @param Other The source array to copy.
         */
        template <
            typename OtherElementType,
            typename OtherAllocator,
            std::enable_if_t<UE4Array_Private::TArrayElementsAreCompatible<ElementType, const OtherElementType&>::Value>* = nullptr
        >
        FORCEINLINE explicit TArray(const TArray<OtherElementType, OtherAllocator>& Other)
        {
            CopyToEmpty(Other.GetData(), Other.Num(), 0, 0);
        }

        /**
         * Copy constructor. Use the common routine to perform the copy.
         *
         * @param Other The source array to copy.
         */
        FORCEINLINE TArray(const TArray& Other)
        {
            CopyToEmpty(Other.GetData(), Other.Num(), 0, 0);
        }

        /**
         * Copy constructor. Use the common routine to perform the copy.
         *
         * @param Other The source array to copy.
         * @param ExtraSlack Tells how much extra memory should be preallocated
         *                   at the end of the array in the number of elements.
         */
        FORCEINLINE TArray(const TArray& Other, SizeType ExtraSlack)
        {
            CopyToEmpty(Other.GetData(), Other.Num(), 0, ExtraSlack);
        }

        /**
         * Initializer list assignment operator. First deletes all currently contained elements
         * and then copies from initializer list.
         *
         * @param InitList The initializer_list to copy from.
         */
        TArray& operator=(std::initializer_list<InElementType> InitList)
        {
            DestructItems(GetData(), ArrayNum);
            // This is not strictly legal, as std::initializer_list's iterators are not guaranteed to be pointers, but
            // this appears to be the case on all of our implementations.  Also, if it's not true on a new implementation,
            // it will fail to compile rather than behave badly.
            CopyToEmpty(InitList.begin(), (SizeType)InitList.size(), ArrayMax, 0);
            return *this;
        }

        /**
         * Assignment operator. First deletes all currently contained elements
         * and then copies from other array.
         *
         * Allocator changing version.
         *
         * @param Other The source array to assign from.
         */
        template<typename OtherAllocator>
        TArray& operator=(const TArray<ElementType, OtherAllocator>& Other)
        {
            DestructItems(GetData(), ArrayNum);
            CopyToEmpty(Other.GetData(), Other.Num(), ArrayMax, 0);
            return *this;
        }

        /**
         * Assignment operator. First deletes all currently contained elements
         * and then copies from other array.
         *
         * @param Other The source array to assign from.
         */
        TArray& operator=(const TArray& Other)
        {
            if (this != &Other)
            {
                DestructItems(GetData(), ArrayNum);
                CopyToEmpty(Other.GetData(), Other.Num(), ArrayMax, 0);
            }
            return *this;
        }
        
        template <typename OtherElementType, typename OtherSizeType>
        TArray& operator=(const TArrayView<OtherElementType, OtherSizeType>& Other);

    private:

        FORCEINLINE void SlackTrackerNumChanged()
        {
#if UE_ENABLE_ARRAY_SLACK_TRACKING
            if constexpr (TAllocatorTraits<InAllocatorType>::SupportsSlackTracking)
            {
                AllocatorInstance.SlackTrackerLogNum(ArrayNum);
            }
#endif
        }
        
        /**
         * Moves or copies array. Depends on the array type traits.
         *
         * @param ToArray Array to move into.
         * @param FromArray Array to move from.
         * @param PrevMax The previous allocated size.
         */
        template <typename FromArrayType, typename ToArrayType>
        static FORCEINLINE void MoveOrCopy(ToArrayType& ToArray, FromArrayType& FromArray, SizeType PrevMax)
        {
            if constexpr (UE4Array_Private::CanMoveTArrayPointersBetweenArrayTypes<FromArrayType, ToArrayType>())
            {
                // Move

                static_assert(std::is_same_v<TArray, ToArrayType>, "MoveOrCopy is expected to be called with the current array type as the destination");

                using FromAllocatorType = typename FromArrayType::AllocatorType;
                using ToAllocatorType   = typename ToArrayType::AllocatorType;

                if constexpr (TCanMoveBetweenAllocators<FromAllocatorType, ToAllocatorType>::Value)
                {
                    ToArray.AllocatorInstance.template MoveToEmptyFromOtherAllocator<FromAllocatorType>(FromArray.AllocatorInstance);
                }
                else
                {
                    ToArray.AllocatorInstance.MoveToEmpty(FromArray.AllocatorInstance);
                }

                ToArray  .ArrayNum = (SizeType)FromArray.ArrayNum;
                ToArray  .ArrayMax = (SizeType)FromArray.ArrayMax;

                // Ensure the destination container could hold the source range (when the allocator size types shrink)
                if constexpr (sizeof(USizeType) < sizeof(typename FromArrayType::USizeType))
                {
                    if (ToArray.ArrayNum != FromArray.ArrayNum || ToArray.ArrayMax != FromArray.ArrayMax)
                    {
                        // Cast to USizeType first to prevent sign extension on negative sizes, producing unusually large values.
                        // UE::Core::Private::OnInvalidArrayNum((unsigned long long)(USizeType)ToArray.ArrayNum);
                    }
                }

                FromArray.ArrayNum = 0;
                FromArray.ArrayMax = FromArray.AllocatorInstance.GetInitialCapacity();
            }
            else
            {
                // Copy

                ToArray.CopyToEmpty(FromArray.GetData(), FromArray.Num(), PrevMax);
            }
        }

        /**
         * Moves or copies array. Depends on the array type traits.
         *
         * @param ToArray Array to move into.
         * @param FromArray Array to move from.
         * @param PrevMax The previous allocated size.
         * @param ExtraSlack Tells how much extra memory should be preallocated
         *                   at the end of the array in the number of elements.
         */
        template <typename FromArrayType, typename ToArrayType>
        static FORCEINLINE void MoveOrCopyWithSlack(ToArrayType& ToArray, FromArrayType& FromArray, SizeType PrevMax, SizeType ExtraSlack)
        {
            if constexpr (UE4Array_Private::CanMoveTArrayPointersBetweenArrayTypes<FromArrayType, ToArrayType>())
            {
                // Move

                MoveOrCopy(ToArray, FromArray, PrevMax);

                USizeType LocalArrayNum = (USizeType)ToArray.ArrayNum;
                USizeType NewMax        = (USizeType)LocalArrayNum + (USizeType)ExtraSlack;

                // This should only happen when we've underflowed or overflowed SizeType
                if ((SizeType)NewMax < LocalArrayNum)
                {
                    // UE::Core::Private::OnInvalidArrayNum((unsigned long long)ExtraSlack);
                }

                ToArray.Reserve(NewMax);
            }
            else
            {
                // Copy

                ToArray.CopyToEmptyWithSlack(FromArray.GetData(), FromArray.Num(), PrevMax, ExtraSlack);
            }
        }

    public:
        /**
         * Move constructor.
         *
         * @param Other Array to move from.
         */
        FORCEINLINE TArray(TArray&& Other)
        {
            MoveOrCopy(*this, Other, 0);
        }

        /**
         * Move constructor.
         *
         * @param Other Array to move from.
         */
        template <
            typename OtherElementType,
            typename OtherAllocator,
            std::enable_if_t<UE4Array_Private::TArrayElementsAreCompatible<ElementType, OtherElementType&&>::Value>* = nullptr
        >
        FORCEINLINE explicit TArray(TArray<OtherElementType, OtherAllocator>&& Other)
        {
            MoveOrCopy(*this, Other, 0);
        }

        /**
         * Move constructor.
         *
         * @param Other Array to move from.
         * @param ExtraSlack Tells how much extra memory should be preallocated
         *                   at the end of the array in the number of elements.
         */
        template <
            typename OtherElementType,
            std::enable_if_t<UE4Array_Private::TArrayElementsAreCompatible<ElementType, OtherElementType&&>::Value>* = nullptr
        >
        TArray(TArray<OtherElementType, Allocator>&& Other, SizeType ExtraSlack)
        {
            // We don't implement move semantics for general OtherAllocators, as there's no way
            // to tell if they're compatible with the current one.  Probably going to be a pretty
            // rare requirement anyway.

            MoveOrCopyWithSlack(*this, Other, 0, ExtraSlack);
        }

        /**
         * Move assignment operator.
         *
         * @param Other Array to assign and move from.
         */
        TArray& operator=(TArray&& Other)
        {
            if (this != &Other)
            {
                DestructItems(GetData(), ArrayNum);
                MoveOrCopy(*this, Other, ArrayMax);
            }
            return *this;
        }

        /** Destructor. */
        ~TArray()
        {
            DestructItems(GetData(), ArrayNum);
            ArrayNum = 0;
        }
        
        /**
         * Helper function for returning a typed pointer to the first array entry.
         *
         * @returns Pointer to first array entry or nullptr if ArrayMax == 0.
         */
        FORCEINLINE ElementType* GetData()
        {
            return (ElementType*)AllocatorInstance.GetAllocation();
        }

        /**
         * Helper function for returning a typed pointer to the first array entry.
         *
         * @returns Pointer to first array entry or nullptr if ArrayMax == 0.
         */
        FORCEINLINE const ElementType* GetData() const
        {
            return (const ElementType*)AllocatorInstance.GetAllocation();
        }

        /** 
         * Helper function returning the size of the inner type.
         *
         * @returns Size in bytes of array type.
         */
        FORCEINLINE uint32 GetTypeSize() const
        {
            if constexpr (!ArraySizeIsImplicit<ElementType>)
            {
                // Structs where the size is unknown to the compiler
                // This happens when a struct has had layout changes and now has different sizes in different engine versions
                return ElementType::StaticSize();
            }
            else
            {
                // Structs where the size is known to the compiler
                return sizeof(ElementType);
            }
        }

        /** 
         * Helper function to return the amount of memory allocated by this
         * container.
         * Only returns the size of allocations made directly by the container, not the elements themselves.
         *
         * @returns Number of bytes allocated by this container.
         */
        FORCEINLINE SIZE_T GetAllocatedSize(void) const
        {
                return AllocatorInstance.GetAllocatedSize(ArrayMax, GetTypeSize());
        }

        /**
         * Returns the amount of slack in this array in elements.
         *
         * @see Num, Shrink
         */
        FORCEINLINE SizeType GetSlack() const
        {
            return ArrayMax - ArrayNum;
        }

        /**
         * Checks array invariants: if array size is greater than zero and less
         * than maximum.
         */
        FORCEINLINE void CheckInvariants() const
        {
            if (!((ArrayNum >= 0) & (ArrayMax >= ArrayNum))) // & for one branch
            {
                throw std::runtime_error{"Array failed invariants check, ArrayNum exceeds ArrayMax."};
            }
        }

        /**
         * Checks if index is in array range.
         *
         * @param Index Index to check.
         */
        FORCEINLINE void RangeCheck(SizeType Index) const
        {
            CheckInvariants();

            // Template property, branch will be optimized out
            if (Allocator::RequireRangeCheck)
            {
                if (!((Index >= 0) & (Index < ArrayNum)))
                {
                    throw std::runtime_error{fmt::format("Array index out of bounds: {} from an array of size {}", Index, ArrayNum)};
                }
            }
        }
        
        /**
         * Checks if a range of indices are in the array range.
         *
         * @param Index Index of the start of the range to check.
         * @param Count Number of elements in the range.
         */
            FORCEINLINE void RangeCheck(SizeType Index, SizeType Count) const
            {
                CheckInvariants();

                // Template property, branch will be optimized out
                if constexpr (AllocatorType::RequireRangeCheck)
                {
                    checkf((Count >= 0) & (Index >= 0) & (Index + Count <= ArrayNum), TEXT("Array range out of bounds: index %lld and length %lld into an array of size %lld"), (long long)Index, (long long)Count, (long long)ArrayNum); // & for one branch
                }
            }

        /**
         * Tests if index is valid, i.e. greater than or equal to zero, and less than the number of elements in the array.
         *
         * @param Index Index to test.
         * @returns True if index is valid. False otherwise.
         */
        FORCEINLINE bool IsValidIndex(SizeType Index) const
        {
            return Index >= 0 && Index < ArrayNum;
        }

        /**
         * Returns number of elements in array.
         *
         * @returns Number of elements in array.
         * @see GetSlack
         */
        FORCEINLINE SizeType Num() const
        {
            return ArrayNum;
        }

        /**
         * Returns maximum number of elements in array.
         *
         * @returns Maximum number of elements in array.
         * @see GetSlack
         */
        FORCEINLINE SizeType Max() const
        {
            return ArrayMax;
        }

        /**
         * Array bracket operator. Returns reference to element at give index.
         *
         * @returns Reference to indexed element.
         */
        FORCEINLINE ElementType& operator[](SizeType Index)
        {
            RangeCheck(Index);
            return GetData()[Index];
        }

        /**
         * Array bracket operator. Returns reference to element at give index.
         *
         * Const version of the above.
         *
         * @returns Reference to indexed element.
         */
        FORCEINLINE const ElementType& operator[](SizeType Index) const
        {
            RangeCheck(Index);
            return GetData()[Index];
        }

        /**
         * Pops element from the array.
         *
         * @param bAllowShrinking If this call allows shrinking of the array during element remove.
         * @returns Popped element.
         */
        template<typename ET=InElementType>
        FORCEINLINE typename TEnableIf<!TIsAbstract<ET>::Value, ElementType>::Type Pop(bool bAllowShrinking = true)
        {
            RangeCheck(0);
            ElementType Result = MoveTempIfPossible(GetData()[ArrayNum - 1]);
            RemoveAt(ArrayNum - 1, 1, bAllowShrinking);
            return Result;
        }

        /**
         * Pushes element into the array.
         *
         * @param Item Item to push.
         */
        FORCEINLINE void Push(ElementType&& Item)
        {
            Add(MoveTempIfPossible(Item));
        }

        /**
         * Pushes element into the array.
         *
         * Const ref version of the above.
         *
         * @param Item Item to push.
         * @see Pop, Top
         */
        FORCEINLINE void Push(const ElementType& Item)
        {
            Add(Item);
        }

        /**
         * Returns the top element, i.e. the last one.
         *
         * @returns Reference to the top element.
         * @see Pop, Push
         */
        FORCEINLINE ElementType& Top()
        {
            return Last();
        }

        /**
         * Returns the top element, i.e. the last one.
         *
         * Const version of the above.
         *
         * @returns Reference to the top element.
         * @see Pop, Push
         */
        FORCEINLINE const ElementType& Top() const
        {
            return Last();
        }

        /**
         * Returns n-th last element from the array.
         *
         * @param IndexFromTheEnd (Optional) Index from the end of array (default = 0).
         * @returns Reference to n-th last element from the array.
         */
        FORCEINLINE ElementType& Last(SizeType IndexFromTheEnd = 0)
        {
            RangeCheck(ArrayNum - IndexFromTheEnd - 1);
            return GetData()[ArrayNum - IndexFromTheEnd - 1];
        }

        /**
         * Returns n-th last element from the array.
         *
         * Const version of the above.
         *
         * @param IndexFromTheEnd (Optional) Index from the end of array (default = 0).
         * @returns Reference to n-th last element from the array.
         */
        FORCEINLINE const ElementType& Last(SizeType IndexFromTheEnd = 0) const
        {
            RangeCheck(ArrayNum - IndexFromTheEnd - 1);
            return GetData()[ArrayNum - IndexFromTheEnd - 1];
        }

        /**
         * Shrinks the array's used memory to smallest possible to store elements currently in it.
         *
         * @see Slack
         */
        FORCEINLINE void Shrink()
        {
            CheckInvariants();
            if (ArrayMax != ArrayNum)
            {
                ResizeTo(ArrayNum);
            }
        }

        /**
         * Finds element within the array.
         *
         * @param Item Item to look for.
         * @param Index Will contain the found index.
         * @returns True if found. False otherwise.
         * @see FindLast, FindLastByPredicate
         */
        FORCEINLINE bool Find(const ElementType& Item, SizeType& Index) const
        {
            Index = this->Find(Item);
            return Index != INDEX_NONE;
        }

        /**
         * Finds element within the array.
         *
         * @param Item Item to look for.
         * @returns Index of the found element. INDEX_NONE otherwise.
         * @see FindLast, FindLastByPredicate
         */
        SizeType Find(const ElementType& Item) const
        {
            const ElementType* RESTRICT Start = GetData();
            for (const ElementType* RESTRICT Data = Start, *RESTRICT DataEnd = Data + ArrayNum; Data != DataEnd; ++Data)
            {
                if (*Data == Item)
                {
                    return static_cast<SizeType>(Data - Start);
                }
            }
            return INDEX_NONE;
        }

        /**
         * Finds element within the array starting from the end.
         *
         * @param Item Item to look for.
         * @param Index Output parameter. Found index.
         * @returns True if found. False otherwise.
         * @see Find, FindLastByPredicate
         */
        FORCEINLINE bool FindLast(const ElementType& Item, SizeType& Index) const
        {
            Index = this->FindLast(Item);
            return Index != INDEX_NONE;
        }

        /**
         * Finds element within the array starting from the end.
         *
         * @param Item Item to look for.
         * @returns Index of the found element. INDEX_NONE otherwise.
         */
        SizeType FindLast(const ElementType& Item) const
        {
            for (const ElementType* RESTRICT Start = GetData(), *RESTRICT Data = Start + ArrayNum; Data != Start; )
            {
                --Data;
                if (*Data == Item)
                {
                    return static_cast<SizeType>(Data - Start);
                }
            }
            return INDEX_NONE;
        }

        /**
         * Searches an initial subrange of the array for the last occurrence of an element which matches the specified predicate.
         *
         * @param Pred Predicate taking array element and returns true if element matches search criteria, false otherwise.
         * @param Count The number of elements from the front of the array through which to search.
         * @returns Index of the found element. INDEX_NONE otherwise.
         */
        template <typename Predicate>
        SizeType FindLastByPredicate(Predicate Pred, SizeType Count) const
        {
            if (!(Count >= 0 && Count <= this->Num())) { Output::send<LogLevel::Warning>(STR("Cannot find index.  Count is either less than 0 or greater than the size of the array.\n")); return; };
            for (const ElementType* RESTRICT Start = GetData(), *RESTRICT Data = Start + Count; Data != Start; )
            {
                --Data;
                if (Pred(*Data))
                {
                    return static_cast<SizeType>(Data - Start);
                }
            }
            return INDEX_NONE;
        }

        /**
         * Searches the array for the last occurrence of an element which matches the specified predicate.
         *
         * @param Pred Predicate taking array element and returns true if element matches search criteria, false otherwise.
         * @returns Index of the found element. INDEX_NONE otherwise.
         */
        template <typename Predicate>
        FORCEINLINE SizeType FindLastByPredicate(Predicate Pred) const
        {
            return FindLastByPredicate(Pred, ArrayNum);
        }

        /**
         * Finds an item by key (assuming the ElementType overloads operator== for
         * the comparison).
         *
         * @param Key The key to search by.
         * @returns Index to the first matching element, or INDEX_NONE if none is found.
         */
        template <typename KeyType>
        SizeType IndexOfByKey(const KeyType& Key) const
        {
            const ElementType* RESTRICT Start = GetData();
            for (const ElementType* RESTRICT Data = Start, *RESTRICT DataEnd = Start + ArrayNum; Data != DataEnd; ++Data)
            {
                if (*Data == Key)
                {
                    return static_cast<SizeType>(Data - Start);
                }
            }
            return INDEX_NONE;
        }

        /**
         * Finds an item by predicate.
         *
         * @param Pred The predicate to match.
         * @returns Index to the first matching element, or INDEX_NONE if none is found.
         */
        template <typename Predicate>
        SizeType IndexOfByPredicate(Predicate Pred) const
        {
            const ElementType* RESTRICT Start = GetData();
            for (const ElementType* RESTRICT Data = Start, *RESTRICT DataEnd = Start + ArrayNum; Data != DataEnd; ++Data)
            {
                if (Pred(*Data))
                {
                    return static_cast<SizeType>(Data - Start);
                }
            }
            return INDEX_NONE;
        }

        /**
         * Finds an item by key (assuming the ElementType overloads operator== for
         * the comparison).
         *
         * @param Key The key to search by.
         * @returns Pointer to the first matching element, or nullptr if none is found.
         * @see Find
         */
        template <typename KeyType>
        FORCEINLINE const ElementType* FindByKey(const KeyType& Key) const
        {
            return const_cast<TArray*>(this)->FindByKey(Key);
        }

        /**
         * Finds an item by key (assuming the ElementType overloads operator== for
         * the comparison). Time Complexity: O(n), starts iteration from the beginning so better performance if Key is in the front
         *
         * @param Key The key to search by.
         * @returns Pointer to the first matching element, or nullptr if none is found.
         * @see Find
         */
        template <typename KeyType>
        ElementType* FindByKey(const KeyType& Key)
        {
            for (ElementType* RESTRICT Data = GetData(), *RESTRICT DataEnd = Data + ArrayNum; Data != DataEnd; ++Data)
            {
                if (*Data == Key)
                {
                    return Data;
                }
            }

            return nullptr;
        }

        /**
         * Finds an element which matches a predicate functor.
         *
         * @param Pred The functor to apply to each element.
         * @returns Pointer to the first element for which the predicate returns true, or nullptr if none is found.
         * @see FilterByPredicate, ContainsByPredicate
         */
        template <typename Predicate>
        FORCEINLINE const ElementType* FindByPredicate(Predicate Pred) const
        {
            return const_cast<TArray*>(this)->FindByPredicate(Pred);
        }

        /**
         * Finds an element which matches a predicate functor.
         *
         * @param Pred The functor to apply to each element. true, or nullptr if none is found.
         * @see FilterByPredicate, ContainsByPredicate
         */
        template <typename Predicate>
        ElementType* FindByPredicate(Predicate Pred)
        {
            for (ElementType* RESTRICT Data = GetData(), *RESTRICT DataEnd = Data + ArrayNum; Data != DataEnd; ++Data)
            {
                if (Pred(*Data))
                {
                    return Data;
                }
            }

            return nullptr;
        }

        /**
         * Filters the elements in the array based on a predicate functor.
         *
         * @param Pred The functor to apply to each element.
         * @returns TArray with the same type as this object which contains
         *          the subset of elements for which the functor returns true.
         * @see FindByPredicate, ContainsByPredicate
         */
        template <typename Predicate>
        TArray<ElementType> FilterByPredicate(Predicate Pred) const
        {
            TArray<ElementType> FilterResults;
            for (const ElementType* RESTRICT Data = GetData(), *RESTRICT DataEnd = Data + ArrayNum; Data != DataEnd; ++Data)
            {
                if (Pred(*Data))
                {
                    FilterResults.Add(*Data);
                }
            }
            return FilterResults;
        }

        /**
         * Checks if this array contains the element.
         *
         * @returns    True if found. False otherwise.
         * @see ContainsByPredicate, FilterByPredicate, FindByPredicate
         */
        template <typename ComparisonType>
        bool Contains(const ComparisonType& Item) const
        {
            for (const ElementType* RESTRICT Data = GetData(), *RESTRICT DataEnd = Data + ArrayNum; Data != DataEnd; ++Data)
            {
                if (*Data == Item)
                {
                    return true;
                }
            }
            return false;
        }

        /**
         * Checks if this array contains element for which the predicate is true.
         *
         * @param Predicate to use
         * @returns    True if found. False otherwise.
         * @see Contains, Find
         */
        template <typename Predicate>
        FORCEINLINE bool ContainsByPredicate(Predicate Pred) const
        {
            return FindByPredicate(Pred) != nullptr;
        }

        /**
         * Equality operator.
         *
         * @param OtherArray Array to compare.
         * @returns True if this array is the same as OtherArray. False otherwise.
         */
        bool operator==(const TArray& OtherArray) const
        {
            SizeType Count = Num();

            return Count == OtherArray.Num() && CompareItems(GetData(), OtherArray.GetData(), Count);
        }

        /**
         * Inequality operator.
         *
         * @param OtherArray Array to compare.
         * @returns True if this array is NOT the same as OtherArray. False otherwise.
         */
        FORCEINLINE bool operator!=(const TArray& OtherArray) const
        {
            return !(*this == OtherArray);
        }

        // We do not include serialization logic from UE, which would normally go here.

        /**
         * Adds a given number of uninitialized elements into the array.
         *
         * Caution, AddUninitialized() will create elements without calling
         * the constructor and this is not appropriate for element types that
         * require a constructor to function properly.
         *
         * @param Count Number of elements to add.
         * @returns Number of elements in array before addition.
         */
        FORCEINLINE SizeType AddUninitialized(SizeType Count = 1)
        {
            CheckInvariants();
            const SizeType OldNum = ArrayNum;
            if (Count < 0)
            {
                Output::send<LogLevel::Warning>(STR("Number of elements to add must be greater than 0.\n"));
                return OldNum;
            }
            
            if ((ArrayNum += Count) > ArrayMax)
            {
                ResizeGrow(OldNum);
            }
            return OldNum;
        }

    private:
        template <typename OtherSizeType>
        void InsertUninitializedImpl(SizeType Index, OtherSizeType Count)
        {
            CheckInvariants();
            if (!((Count >= 0) & (Index >= 0) & (Index <= ArrayNum)))
            {
                Output::send<LogLevel::Error>(STR("Unable to add unitialized elements to array.  Count or index are less than 0 or index is lower than total array number.\n"));
                return;
            }

            SizeType NewNum = Count;
            if (!((OtherSizeType)NewNum == Count))
            {
                Output::send<LogLevel::Error>(STR("Invalid number of elements to add to this array type: {}"), (unsigned long long)NewNum);
                return;
            }

            const SizeType OldNum = ArrayNum;
            if ((ArrayNum += Count) > ArrayMax)
            {
                ResizeGrow(OldNum);
            }
            ElementType* Data = GetData() + Index;
            RelocateConstructItems<ElementType>(Data + Count, Data, OldNum - Index);
        }

    public:
        /**
         * Inserts a given number of uninitialized elements into the array at given
         * location.
         *
         * Caution, InsertUninitialized() will create elements without calling the
         * constructor and this is not appropriate for element types that require
         * a constructor to function properly.
         *
         * @param Index Tells where to insert the new elements.
         * @param Count Number of elements to add.
         * @see Insert, InsertZeroed, InsertDefaulted
         */
        FORCEINLINE void InsertUninitialized(SizeType Index, SizeType Count = 1)
        {
            InsertUninitializedImpl(Index, Count);
        }

        /**
         * Inserts a given number of zeroed elements into the array at given
         * location.
         *
         * Caution, InsertZeroed() will create elements without calling the
         * constructor and this is not appropriate for element types that require
         * a constructor to function properly.
         *
         * @param Index Tells where to insert the new elements.
         * @param Count Number of elements to add.
         * @see Insert, InsertUninitialized, InsertDefaulted
         */
        void InsertZeroed(SizeType Index, SizeType Count = 1)
        {
            InsertUninitializedImpl(Index, Count);
            FMemory::Memzero(GetData() + Index, Count * GetTypeSize());
        }

        /**
         * Inserts a zeroed element into the array at given location.
         *
         * Caution, InsertZeroed_GetRef() will create an element without calling the
         * constructor and this is not appropriate for element types that require
         * a constructor to function properly.
         *
         * @param Index Tells where to insert the new element.
         * @return A reference to the newly-inserted element.
         * @see Insert_GetRef, InsertDefaulted_GetRef
         */
        ElementType& InsertZeroed_GetRef(SizeType Index)
        {
            InsertUninitializedImpl(Index, 1);
            ElementType* Ptr = GetData() + Index;
            FMemory::Memzero(Ptr, GetTypeSize());
            return *Ptr;
        }

        /**
         * Inserts a given number of default-constructed elements into the array at a given
         * location.
         *
         * @param Index Tells where to insert the new elements.
         * @param Count Number of elements to add.
         * @see Insert, InsertUninitialized, InsertZeroed
         */
        void InsertDefaulted(SizeType Index, SizeType Count = 1)
        {
            InsertUninitializedImpl(Index, Count);
            DefaultConstructItems<ElementType>(GetData() + Index, Count);
        }

        /**
         * Inserts a default-constructed element into the array at a given
         * location.
         *
         * @param Index Tells where to insert the new element.
         * @return A reference to the newly-inserted element.
         * @see Insert_GetRef, InsertZeroed_GetRef
         */
        ElementType& InsertDefaulted_GetRef(SizeType Index)
        {
            InsertUninitializedImpl(Index, 1);
            ElementType* Ptr = GetData() + Index;
            DefaultConstructItems<ElementType>(Ptr, 1);
            return *Ptr;
        }

        /**
         * Inserts given elements into the array at given location.
         *
         * @param Items Array of elements to insert.
         * @param InIndex Tells where to insert the new elements.
         * @returns Location at which the item was inserted.
         */
        SizeType Insert(std::initializer_list<ElementType> InitList, const SizeType InIndex)
        {
            SizeType NumNewElements = (SizeType)InitList.size();

            InsertUninitializedImpl(InIndex, NumNewElements);
            ConstructItems<ElementType>(GetData() + InIndex, InitList.begin(), NumNewElements);

            return InIndex;
        }

        /**
         * Inserts given elements into the array at given location.
         *
         * @param Items Array of elements to insert.
         * @param InIndex Tells where to insert the new elements.
         * @returns Location at which the item was inserted.
         */
        template <typename OtherAllocator>
        SizeType Insert(const TArray<ElementType, OtherAllocator>& Items, const SizeType InIndex)
        {
            check((const void*)this != (const void*)&Items);

            auto NumNewElements = Items.Num();

            InsertUninitializedImpl(InIndex, NumNewElements);
            ConstructItems<ElementType>(GetData() + InIndex, Items.GetData(), NumNewElements);

            return InIndex;
        }

        /**
         * Inserts given elements into the array at given location.
         *
         * @param Items Array of elements to insert.
         * @param InIndex Tells where to insert the new elements.
         * @returns Location at which the item was inserted.
         */
        template <typename OtherAllocator>
        SizeType Insert(TArray<ElementType, OtherAllocator>&& Items, const SizeType InIndex)
        {
            check((const void*)this != (const void*)&Items);

            auto NumNewElements = Items.Num();

            InsertUninitializedImpl(InIndex, NumNewElements);
            RelocateConstructItems<ElementType>(GetData() + InIndex, Items.GetData(), NumNewElements);
            Items.ArrayNum = 0;

            return InIndex;
        }

        /**
         * Inserts a raw array of elements at a particular index in the TArray.
         *
         * @param Ptr A pointer to an array of elements to add.
         * @param Count The number of elements to insert from Ptr.
         * @param Index The index to insert the elements at.
         * @return The index of the first element inserted.
         * @see Add, Remove
         */
        SizeType Insert(const ElementType* Ptr, SizeType Count, SizeType Index)
        {
            check(Ptr != nullptr);

            InsertUninitializedImpl(Index, Count);
            ConstructItems<ElementType>(GetData() + Index, Ptr, Count);

            return Index;
        }

        /**
         * Checks that the specified address is not part of an element within the
         * container. Used for implementations to check that reference arguments
         * aren't going to be invalidated by possible reallocation.
         *
         * @param Addr The address to check.
         * @see Add, Remove
         */
        FORCEINLINE void CheckAddress(const ElementType* Addr) const
        {
            if (!(Addr < GetData() || Addr >= (GetData() + ArrayMax)))
            {
                Output::send<LogLevel::Error>(fmt::format(STR("Attempting to use a container element ({}) which already comes from the container being modified ({}, ArrayMax: {}, ArrayNum: {}, TypeSize: {})!"), static_cast<const void*>(Addr), static_cast<const void*>(GetData()), ArrayMax, ArrayNum, GetTypeSize()));
            }
        }

        /**
         * Inserts a given element into the array at given location. Move semantics
         * version.
         *
         * @param Item The element to insert.
         * @param Index Tells where to insert the new elements.
         * @returns Location at which the insert was done.
         * @see Add, Remove
         */
        SizeType Insert(ElementType&& Item, SizeType Index)
        {
            CheckAddress(&Item);

            // construct a copy in place at Index (this new operator will insert at 
            // Index, then construct that memory with Item)
            InsertUninitializedImpl(Index, 1);
            new(GetData() + Index) ElementType(MoveTempIfPossible(Item));
            return Index;
        }

        /**
         * Inserts a given element into the array at given location.
         *
         * @param Item The element to insert.
         * @param Index Tells where to insert the new elements.
         * @returns Location at which the insert was done.
         * @see Add, Remove
         */
        SizeType Insert(const ElementType& Item, SizeType Index)
        {
            CheckAddress(&Item);

            // construct a copy in place at Index (this new operator will insert at 
            // Index, then construct that memory with Item)
            InsertUninitializedImpl(Index, 1);
            new(GetData() + Index) ElementType(Item);
            return Index;
        }

        /**
         * Inserts a given element into the array at given location. Move semantics
         * version.
         *
         * @param Item The element to insert.
         * @param Index Tells where to insert the new element.
         * @return A reference to the newly-inserted element.
         * @see Add, Remove
         */
        ElementType& Insert_GetRef(ElementType&& Item, SizeType Index)
        {
            CheckAddress(&Item);

            // construct a copy in place at Index (this new operator will insert at 
            // Index, then construct that memory with Item)
            InsertUninitializedImpl(Index, 1);
            ElementType* Ptr = GetData() + Index;
            new(Ptr) ElementType(MoveTempIfPossible(Item));
            return *Ptr;
        }

        /**
         * Inserts a given element into the array at given location.
         *
         * @param Item The element to insert.
         * @param Index Tells where to insert the new element.
         * @return A reference to the newly-inserted element.
         * @see Add, Remove
         */
        ElementType& Insert_GetRef(const ElementType& Item, SizeType Index)
        {
            CheckAddress(&Item);

            // construct a copy in place at Index (this new operator will insert at 
            // Index, then construct that memory with Item)
            InsertUninitializedImpl(Index, 1);
            ElementType* Ptr = GetData() + Index;
            new(Ptr) ElementType(Item);
            return *Ptr;
        }

    private:
    void RemoveAtImpl(SizeType Index)
    {
        ElementType* Dest = GetData() + Index;

        DestructItem(Dest);

        // Skip relocation in the common case that there is nothing to move.
        SizeType NumToMove = (ArrayNum - Index) - 1;
        if (NumToMove)
        {
            RelocateConstructItems<ElementType>((void*)Dest, Dest + 1, NumToMove);
        }
        --ArrayNum;

        SlackTrackerNumChanged();
    }

    void RemoveAtImpl(SizeType Index, SizeType Count)
    {
        ElementType* Dest = GetData() + Index;

        DestructItems(Dest, Count);

        // Skip relocation in the common case that there is nothing to move.
        SizeType NumToMove = (ArrayNum - Index) - Count;
        if (NumToMove)
        {
            RelocateConstructItems<ElementType>((void*)Dest, Dest + Count, NumToMove);
        }
        ArrayNum -= Count;

        SlackTrackerNumChanged();
    }

public:
    /**
     * Removes an element (or elements) at given location, then shrinks
     * the array.
     *
     * @param Index Location in array of the element to remove.
     * @param AllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is yes.
     */
    void RemoveAt(SizeType Index, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
    {
        RangeCheck(Index);
        RemoveAtImpl(Index);
        if (AllowShrinking == EAllowShrinking::Yes)
        {
            UE::Core::Private::ReallocShrink<UE::Core::Private::GetAllocatorFlags<AllocatorType>()>(
                sizeof(ElementType),
                alignof(ElementType),
                AllocatorInstance,
                ArrayNum,
                ArrayMax
            );
        }
    }

    /**
     * Removes an element (or elements) at given location, optionally shrinking
     * the array.
     *
     * @param Index Location in array of the element to remove.
     * @param Count (Optional) Number of elements to remove. Default is 1.
     * @param AllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is yes.
     */
    template <
        typename CountType
        UE_REQUIRES(std::is_integral_v<CountType>)
    >
    FORCEINLINE void RemoveAt(SizeType Index, CountType Count, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
    {
        static_assert(!std::is_same_v<CountType, bool>, "TArray::RemoveAt: unexpected bool passed as the Count argument");
        RangeCheck(Index, Count);
        if (Count)
        {
            RemoveAtImpl(Index, (SizeType)Count);
            if (AllowShrinking == EAllowShrinking::Yes)
            {
                UE::Core::Private::ReallocShrink<UE::Core::Private::GetAllocatorFlags<AllocatorType>()>(
                    sizeof(ElementType),
                    alignof(ElementType),
                    AllocatorInstance,
                    ArrayNum,
                    ArrayMax
                );
            }
        }
    }
    template <typename CountType>
    UE_ALLOWSHRINKING_BOOL_DEPRECATED("RemoveAt")
    FORCEINLINE void RemoveAt(SizeType Index, CountType Count, bool bAllowShrinking)
    {
        RemoveAt(Index, Count, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
    }

private:
    void RemoveAtSwapImpl(SizeType Index)
    {
        ElementType* Data = GetData();
        ElementType* Dest = Data + Index;

        DestructItem(Dest);

        // Replace the elements in the hole created by the removal with elements from the end of the array, so the range of indices used by the array is contiguous.
        const SizeType NumElementsAfterHole = (ArrayNum - Index) - 1;
        const SizeType NumElementsToMoveIntoHole = FPlatformMath::Min(1, NumElementsAfterHole);
        if (NumElementsToMoveIntoHole)
        {
            RelocateConstructItems<ElementType>((void*)Dest, Data + (ArrayNum - NumElementsToMoveIntoHole), NumElementsToMoveIntoHole);
        }
        --ArrayNum;

        SlackTrackerNumChanged();
    }

    void RemoveAtSwapImpl(SizeType Index, SizeType Count)
    {
        ElementType* Data = GetData();
        ElementType* Dest = Data + Index;

        DestructItems(Dest, Count);

        // Replace the elements in the hole created by the removal with elements from the end of the array, so the range of indices used by the array is contiguous.
        const SizeType NumElementsAfterHole = (ArrayNum - Index) - Count;
        const SizeType NumElementsToMoveIntoHole = FPlatformMath::Min(Count, NumElementsAfterHole);
        if (NumElementsToMoveIntoHole)
        {
            RelocateConstructItems<ElementType>((void*)Dest, Data + (ArrayNum - NumElementsToMoveIntoHole), NumElementsToMoveIntoHole);
        }
        ArrayNum -= Count;

        SlackTrackerNumChanged();
    }

public:
    /**
     * Removes an element (or elements) at given location, then shrinks
     * the array.
     *
     * This version is much more efficient than RemoveAt (O(Count) instead of
     * O(ArrayNum)), but does not preserve the order.
     *
     * @param Index Location in array of the element to remove.
     * @param AllowShrinking (Optional) Tells if this call can shrink array if
     *                        suitable after remove. Default is yes.
     */
    FORCEINLINE void RemoveAtSwap(SizeType Index, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
    {
        RangeCheck(Index);
        RemoveAtSwapImpl(Index);
        if (AllowShrinking == EAllowShrinking::Yes)
        {
            UE::Core::Private::ReallocShrink<UE::Core::Private::GetAllocatorFlags<AllocatorType>()>(
                sizeof(ElementType),
                alignof(ElementType),
                AllocatorInstance,
                ArrayNum,
                ArrayMax
            );
        }
    }

    /**
     * Removes an element (or elements) at given location, optionally shrinking
     * the array.
     *
     * This version is much more efficient than RemoveAt (O(Count) instead of
     * O(ArrayNum)), but does not preserve the order.
     *
     * @param Index Location in array of the element to remove.
     * @param Count (Optional) Number of elements to remove. Default is 1.
     * @param AllowShrinking (Optional) Tells if this call can shrink array if
     *                        suitable after remove. Default is yes.
     */
    template <
        typename CountType
        UE_REQUIRES(std::is_integral_v<CountType>)
    >
    FORCEINLINE void RemoveAtSwap(SizeType Index, CountType Count, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
    {
        static_assert(!std::is_same_v<CountType, bool>, "TArray::RemoveAtSwap: unexpected bool passed as the Count argument");
        RangeCheck(Index, Count);
        if (Count)
        {
            RemoveAtSwapImpl(Index, Count);
            if (AllowShrinking == EAllowShrinking::Yes)
            {
                UE::Core::Private::ReallocShrink<UE::Core::Private::GetAllocatorFlags<AllocatorType>()>(
                    sizeof(ElementType),
                    alignof(ElementType),
                    AllocatorInstance,
                    ArrayNum,
                    ArrayMax
                );
            }
        }
    }
    template <typename CountType>
    UE_ALLOWSHRINKING_BOOL_DEPRECATED("RemoveAtSwap")
    UE_NODEBUG FORCEINLINE void RemoveAtSwap(SizeType Index, CountType Count, bool bAllowShrinking)
    {
        RemoveAtSwap(Index, Count, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
    }

        /**
         * Same as empty, but doesn't change memory allocations, unless the new size is larger than
         * the current array. It calls the destructors on held items if needed and then zeros the ArrayNum.
         *
         * @param NewSize The expected usage size after calling this function.
         */
        void Reset(SizeType NewSize = 0)
        {
            // If we have space to hold the excepted size, then don't reallocate
            if (NewSize <= ArrayMax)
            {
                DestructItems(GetData(), ArrayNum);
                ArrayNum = 0;
            }
            else
            {
                Empty(NewSize);
            }
        }

        /**
         * Empties the array. It calls the destructors on held items if needed.
         *
         * @param Slack (Optional) The expected usage size after empty operation. Default is 0.
         */
        void Empty(SizeType Slack = 0)
        {
            DestructItems(GetData(), ArrayNum);

            checkSlow(Slack >= 0);
            ArrayNum = 0;

            if (ArrayMax != Slack)
            {
                ResizeTo(Slack);
            }
        }

        /**
         * Resizes array to given number of elements.
         *
         * @param NewNum New size of the array.
         * @param AllowShrinking Tell if this function can shrink the memory in-use if suitable.
         */
        void SetNum(SizeType NewNum, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
        {
            if (NewNum > Num())
            {
                const SizeType Diff = NewNum - ArrayNum;
                const SizeType Index = AddUninitialized(Diff);
                DefaultConstructItems<ElementType>((void*)((uint8*)AllocatorInstance.GetAllocation() + Index * sizeof(ElementType)), Diff);
            }
            else if (NewNum < 0)
            {
                // Cast to USizeType first to prevent sign extension on negative sizes, producing unusually large values.
                UE::Core::Private::OnInvalidArrayNum((unsigned long long)(USizeType)NewNum);
            }
            else if (NewNum < Num())
            {
                RemoveAt(NewNum, Num() - NewNum, AllowShrinking);
            }
        }
        UE_ALLOWSHRINKING_BOOL_DEPRECATED("SetNum")
        UE_NODEBUG FORCEINLINE void SetNum(SizeType NewNum, bool bAllowShrinking)
        {
            SetNum(NewNum, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
        }

        /**
         * Resizes array to given number of elements, optionally shrinking it.
         * New elements will be zeroed.
         *
         * @param NewNum New size of the array.
         * @param AllowShrinking Tell if this function can shrink the memory in-use if suitable.
         */
        void SetNumZeroed(SizeType NewNum, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
        {
            if (NewNum > Num())
            {
                AddZeroed(NewNum - Num());
            }
            else if (NewNum < 0)
            {
                // Cast to USizeType first to prevent sign extension on negative sizes, producing unusually large values.
                UE::Core::Private::OnInvalidArrayNum((unsigned long long)(USizeType)NewNum);
            }
            else if (NewNum < Num())
            {
                RemoveAt(NewNum, Num() - NewNum, AllowShrinking);
            }
        }
        UE_ALLOWSHRINKING_BOOL_DEPRECATED("SetNumZeroed")
        UE_NODEBUG FORCEINLINE void SetNumZeroed(SizeType NewNum, bool bAllowShrinking)
        {
            SetNumZeroed(NewNum, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
        }

        /**
         * Resizes array to given number of elements. New elements will be uninitialized.
         *
         * @param NewNum New size of the array.
         * @param AllowShrinking Tell if this function can shrink the memory in-use if suitable.
         */
        void SetNumUninitialized(SizeType NewNum, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
        {
            if (NewNum > Num())
            {
                AddUninitialized(NewNum - Num());
            }
            else if (NewNum < 0)
            {
                // Cast to USizeType first to prevent sign extension on negative sizes, producing unusually large values.
                UE::Core::Private::OnInvalidArrayNum((unsigned long long)(USizeType)NewNum);
            }
            else if (NewNum < Num())
            {
                RemoveAt(NewNum, Num() - NewNum, AllowShrinking);
            }
        }
        UE_ALLOWSHRINKING_BOOL_DEPRECATED("SetNumUninitialized")
        UE_NODEBUG FORCEINLINE void SetNumUninitialized(SizeType NewNum, bool bAllowShrinking)
        {
            SetNumUninitialized(NewNum, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
        }

        /**
         * Does nothing except setting the new number of elements in the array. Does not destruct items, does not de-allocate memory.
         * @param NewNum New number of elements in the array, must be <= the current number of elements in the array.
         */
        void SetNumUnsafeInternal(SizeType NewNum)
        {
            checkSlow(NewNum <= Num() && NewNum >= 0);
            ArrayNum = NewNum;

            SlackTrackerNumChanged();
        }

        /**
         * Appends the specified array to this array.
         *
         * Allocator changing version.
         *
         * @param Source The array to append.
         * @see Add, Insert
         */
        template <typename OtherElementType, typename OtherAllocator>
        void Append(const TArray<OtherElementType, OtherAllocator>& Source)
        {
            if (!((void*)this != (void*)&Source)) { Output::send<LogLevel::Error>(STR("Unable to append an array it itself.\n")); return; }

            SizeType SourceCount = Source.Num();

            // Do nothing if the source is empty.
            if (!SourceCount)
            {
                return;
            }

            // Allocate memory for the new elements.
            Reserve(ArrayNum + SourceCount);
            ConstructItems<ElementType>(GetData() + ArrayNum, Source.GetData(), SourceCount);

            ArrayNum += SourceCount;
        }

        /**
         * Appends the specified array to this array.
         *
         * @param Source The array to append.
         * @see Add, Insert
         */
        template <typename OtherElementType, typename OtherAllocator>
        void Append(TArray<OtherElementType, OtherAllocator>&& Source)
        {
            if (!((void*)this != (void*)&Source)) { Output::send<LogLevel::Error>(STR("Unable to append an array it itself.\n")); return; }

            SizeType SourceCount = Source.Num();

            // Do nothing if the source is empty.
            if (!SourceCount)
            {
                return;
            }

            // Allocate memory for the new elements.
            Reserve(ArrayNum + SourceCount);
            RelocateConstructItems<ElementType>(GetData() + ArrayNum, Source.GetData(), SourceCount);
            Source.ArrayNum = 0;

            ArrayNum += SourceCount;
        }

        /**
         * Adds a raw array of elements to the end of the TArray.
         *
         * @param Ptr   A pointer to an array of elements to add.
         * @param Count The number of elements to insert from Ptr.
         * @see Add, Insert
         */
        void Append(const ElementType* Ptr, SizeType Count)
        {
            check(Ptr != nullptr || Count == 0);

            SizeType Pos = AddUninitialized(Count);
            ConstructItems<ElementType>(GetData() + Pos, Ptr, Count);
        }

        /**
         * Adds an initializer list of elements to the end of the TArray.
         *
         * @param InitList The initializer list of elements to add.
         * @see Add, Insert
         */
        FORCEINLINE void Append(std::initializer_list<ElementType> InitList)
        {
            SizeType Count = (SizeType)InitList.size();

            SizeType Pos = AddUninitialized(Count);
            ConstructItems<ElementType>(GetData() + Pos, InitList.begin(), Count);
        }

        /**
         * Appends the specified array to this array.
         * Cannot append to self.
         *
         * Move semantics version.
         *
         * @param Other The array to append.
         */
        TArray& operator+=(TArray&& Other)
        {
            Append(MoveTemp(Other));
            return *this;
        }

        /**
         * Appends the specified array to this array.
         * Cannot append to self.
         *
         * @param Other The array to append.
         */
        TArray& operator+=(const TArray& Other)
        {
            Append(Other);
            return *this;
        }

        /**
         * Appends the specified initializer list to this array.
         *
         * @param InitList The initializer list to append.
         */
        TArray& operator+=(std::initializer_list<ElementType> InitList)
        {
            Append(InitList);
            return *this;
        }

        /**
         * Constructs a new item at the end of the array, possibly reallocating the whole array to fit.
         *
         * @param Args    The arguments to forward to the constructor of the new item.
         * @return        Index to the new item
         */
        template <typename... ArgsType>
        FORCEINLINE SizeType Emplace(ArgsType&&... Args)
        {
            const SizeType Index = AddUninitialized(1);
            new(GetData() + Index) ElementType(Forward<ArgsType>(Args)...);
            return Index;
        }

        /**
         * Constructs a new item at the end of the array, possibly reallocating the whole array to fit.
         *
         * @param Args    The arguments to forward to the constructor of the new item.
         * @return A reference to the newly-inserted element.
         */
        template <typename... ArgsType>
        FORCEINLINE ElementType& Emplace_GetRef(ArgsType&&... Args)
        {
            const SizeType Index = AddUninitialized(1);
            ElementType* Ptr = GetData() + Index;
            new(Ptr) ElementType(Forward<ArgsType>(Args)...);
            return *Ptr;
        }

        /**
         * Constructs a new item at a specified index, possibly reallocating the whole array to fit.
         *
         * @param Index    The index to add the item at.
         * @param Args    The arguments to forward to the constructor of the new item.
         */
        template <typename... ArgsType>
        FORCEINLINE void EmplaceAt(SizeType Index, ArgsType&&... Args)
        {
            InsertUninitializedImpl(Index, 1);
            new(GetData() + Index) ElementType(Forward<ArgsType>(Args)...);
        }

        /**
         * Constructs a new item at a specified index, possibly reallocating the whole array to fit.
         *
         * @param Index    The index to add the item at.
         * @param Args    The arguments to forward to the constructor of the new item.
         * @return A reference to the newly-inserted element.
         */
        template <typename... ArgsType>
        FORCEINLINE ElementType& EmplaceAt_GetRef(SizeType Index, ArgsType&&... Args)
        {
            InsertUninitializedImpl(Index, 1);
            ElementType* Ptr = GetData() + Index;
            new(Ptr) ElementType(Forward<ArgsType>(Args)...);
            return *Ptr;
        }

        /**
         * Adds a new item to the end of the array, possibly reallocating the whole array to fit.
         *
         * Move semantics version.
         *
         * @param Item The item to add
         * @return Index to the new item
         * @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
         */
        FORCEINLINE SizeType Add(ElementType&& Item)
        {
            CheckAddress(&Item);
            return Emplace(MoveTempIfPossible(Item));
        }

        /**
         * Adds a new item to the end of the array, possibly reallocating the whole array to fit.
         *
         * @param Item The item to add
         * @return Index to the new item
         * @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
         */
        FORCEINLINE SizeType Add(const ElementType& Item)
        {
            CheckAddress(&Item);
            return Emplace(Item);
        }

        /**
         * Adds a new item to the end of the array, possibly reallocating the whole array to fit.
         *
         * Move semantics version.
         *
         * @param Item The item to add
         * @return A reference to the newly-inserted element.
         * @see AddDefaulted_GetRef, AddUnique_GetRef, AddZeroed_GetRef, Insert_GetRef
         */
        FORCEINLINE ElementType& Add_GetRef(ElementType&& Item)
        {
            CheckAddress(&Item);
            return Emplace_GetRef(MoveTempIfPossible(Item));
        }

        /**
         * Adds a new item to the end of the array, possibly reallocating the whole array to fit.
         *
         * @param Item The item to add
         * @return A reference to the newly-inserted element.
         * @see AddDefaulted_GetRef, AddUnique_GetRef, AddZeroed_GetRef, Insert_GetRef
         */
        FORCEINLINE ElementType& Add_GetRef(const ElementType& Item)
        {
            CheckAddress(&Item);
            return Emplace_GetRef(Item);
        }

        /**
         * Adds new items to the end of the array, possibly reallocating the whole
         * array to fit. The new items will be zeroed.
         *
         * Caution, AddZeroed() will create elements without calling the
         * constructor and this is not appropriate for element types that require
         * a constructor to function properly.
         *
         * @param  Count  The number of new items to add.
         * @return Index to the first of the new items.
         * @see Add, AddDefaulted, AddUnique, Append, Insert
         */
        SizeType AddZeroed(SizeType Count = 1)
        {
            const SizeType Index = AddUninitialized(Count);
            FMemory::Memzero((uint8*)AllocatorInstance.GetAllocation() + Index*GetTypeSize(), Count*GetTypeSize());
            return Index;
        }

        /**
         * Adds a new item to the end of the array, possibly reallocating the whole
         * array to fit. The new item will be zeroed.
         *
         * Caution, AddZeroed_GetRef() will create elements without calling the
         * constructor and this is not appropriate for element types that require
         * a constructor to function properly.
         *
         * @return A reference to the newly-inserted element.
         * @see Add_GetRef, AddDefaulted_GetRef, AddUnique_GetRef, Insert_GetRef
         */
        ElementType& AddZeroed_GetRef()
        {
            const SizeType Index = AddUninitialized(1);
            ElementType* Ptr = GetData() + Index;
            FMemory::Memzero(Ptr, GetTypeSize());
            return *Ptr;
        }

        /**
         * Adds new items to the end of the array, possibly reallocating the whole
         * array to fit. The new items will be default-constructed.
         *
         * @param  Count  The number of new items to add.
         * @return Index to the first of the new items.
         * @see Add, AddZeroed, AddUnique, Append, Insert
         */
        SizeType AddDefaulted(SizeType Count = 1)
        {
            const SizeType Index = AddUninitialized(Count);
            DefaultConstructItems<ElementType>((uint8*)AllocatorInstance.GetAllocation() + Index * GetTypeSize(), Count);
            return Index;
        }

        /**
         * Add a new item to the end of the array, possibly reallocating the whole
         * array to fit. The new item will be default-constructed.
         *
         * @return A reference to the newly-inserted element.
         * @see Add_GetRef, AddZeroed_GetRef, AddUnique_GetRef, Insert_GetRef
         */
        ElementType& AddDefaulted_GetRef()
        {
            const SizeType Index = AddUninitialized(1);
            ElementType* Ptr = GetData() + Index;
            DefaultConstructItems<ElementType>(Ptr, 1);
            return *Ptr;
        }

    private:
        /**
         * Adds unique element to array if it doesn't exist.
         *
         * @param Args Item to add.
         * @returns Index of the element in the array.
         */
        template <typename ArgsType>
        SizeType AddUniqueImpl(ArgsType&& Args)
        {
            SizeType Index;
            if (Find(Args, Index))
            {
                return Index;
            }

            return Add(Forward<ArgsType>(Args));
        }

    public:
        /**
         * Adds unique element to array if it doesn't exist.
         *
         * Move semantics version.
         *
         * @param Args Item to add.
         * @returns Index of the element in the array.
         * @see Add, AddDefaulted, AddZeroed, Append, Insert
         */
        FORCEINLINE SizeType AddUnique(ElementType&& Item) { return AddUniqueImpl(MoveTempIfPossible(Item)); }

        /**
         * Adds unique element to array if it doesn't exist.
         *
         * @param Args Item to add.
         * @returns Index of the element in the array.
         * @see Add, AddDefaulted, AddZeroed, Append, Insert
         */
        FORCEINLINE SizeType AddUnique(const ElementType& Item) { return AddUniqueImpl(Item); }

        /**
         * Reserves memory such that the array can contain at least Number elements.
         *
         * @param Number The number of elements that the array should be able to contain after allocation.
         * @see Shrink
         */
        FORCEINLINE void Reserve(SizeType Number)
        {
            if (!(Number >= 0)) { Output::send<LogLevel::Error>(STR("Number of array elements cannot be 0.\n")); }
            if (Number > ArrayMax)
            {
                ResizeTo(Number);
            }
        }

        /**
         * Sets the size of the array, filling it with the given element.
         *
         * @param Element The element to fill array with.
         * @param Number The number of elements that the array should be able to contain after allocation.
         */
        void Init(const ElementType& Element, SizeType Number)
        {
            Empty(Number);
            for (SizeType Index = 0; Index < Number; ++Index)
            {
                Add(Element);
            }
        }

        /**
         * Removes the first occurrence of the specified item in the array,
         * maintaining order but not indices.
         *
         * @param Item The item to remove.
         * @returns The number of items removed. For RemoveSingleItem, this is always either 0 or 1.
         * @see Add, Insert, Remove, RemoveAll, RemoveAllSwap
         */
        SizeType RemoveSingle(const ElementType& Item)
        {
            SizeType Index = Find(Item);
            if (Index == INDEX_NONE)
            {
                return 0;
            }

            auto* RemovePtr = GetData() + Index;

            // Destruct items that match the specified Item.
            DestructItems(RemovePtr, 1);
            const SizeType NextIndex = Index + 1;
            RelocateConstructItems<ElementType>(RemovePtr, RemovePtr + 1, ArrayNum - (Index + 1));

            // Update the array count
            --ArrayNum;

            // Removed one item
            return 1;
        }

        /**
         * Removes as many instances of Item as there are in the array, maintaining
         * order but not indices.
         *
         * @param Item Item to remove from array.
         * @returns Number of removed elements.
         * @see Add, Insert, RemoveAll, RemoveAllSwap, RemoveSingle, RemoveSwap
         */
        SizeType Remove(const ElementType& Item)
        {
            CheckAddress(&Item);

            // Element is non-const to preserve compatibility with existing code with a non-const operator==() member function
            return RemoveAll([&Item](ElementType& Element) { return Element == Item; });
        }

        /**
         * Remove all instances that match the predicate, maintaining order but not indices
         * Optimized to work with runs of matches/non-matches
         *
         * @param Predicate Predicate class instance
         * @returns Number of removed elements.
         * @see Add, Insert, RemoveAllSwap, RemoveSingle, RemoveSwap
         */
        template <class PREDICATE_CLASS>
        SizeType RemoveAll(const PREDICATE_CLASS& Predicate)
        {
            const SizeType OriginalNum = ArrayNum;
            if (!OriginalNum)
            {
                return 0; // nothing to do, loop assumes one item so need to deal with this edge case here
            }

            SizeType WriteIndex = 0;
            SizeType ReadIndex = 0;
            bool NotMatch = !Predicate(GetData()[ReadIndex]); // use a ! to guarantee it can't be anything other than zero or one
            do
            {
                SizeType RunStartIndex = ReadIndex++;
                while (ReadIndex < OriginalNum && NotMatch == !Predicate(GetData()[ReadIndex]))
                {
                    ReadIndex++;
                }
                SizeType RunLength = ReadIndex - RunStartIndex;
                checkSlow(RunLength > 0);
                if (NotMatch)
                {
                    // this was a non-matching run, we need to move it
                    if (WriteIndex != RunStartIndex)
                    {
                        FMemory::Memmove(&GetData()[WriteIndex], &GetData()[RunStartIndex], GetTypeSize()* RunLength);
                    }
                    WriteIndex += RunLength;
                }
                else
                {
                    // this was a matching run, delete it
                    DestructItems(GetData() + RunStartIndex, RunLength);
                }
                NotMatch = !NotMatch;
            } while (ReadIndex < OriginalNum);

            ArrayNum = WriteIndex;
            return OriginalNum - ArrayNum;
        }

        /**
         * Remove all instances that match the predicate
         *
         * @param Predicate Predicate class instance
         * @param AllowShrinking Tell if this function can shrink the memory in-use if suitable.
         * @see Remove, RemoveSingle, RemoveSingleSwap, RemoveSwap
         */
        template <class PREDICATE_CLASS>
        SizeType RemoveAllSwap(const PREDICATE_CLASS& Predicate, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
        {
            bool bRemoved = false;
            const SizeType OriginalNum = ArrayNum;
            for (SizeType ItemIndex = 0; ItemIndex < Num();)
            {
                if (Invoke(Predicate, (*this)[ItemIndex]))
                {
                    bRemoved = true;
                    RemoveAtSwap(ItemIndex, EAllowShrinking::No);
                }
                else
                {
                    ++ItemIndex;
                }
            }

            if (bRemoved && AllowShrinking == EAllowShrinking::Yes)
            {
                UE::Core::Private::ReallocShrink<UE::Core::Private::GetAllocatorFlags<AllocatorType>()>(
                    sizeof(ElementType),
                    alignof(ElementType),
                    AllocatorInstance,
                    ArrayNum,
                    ArrayMax
                );
            }

            return OriginalNum - ArrayNum;
        }
        template <class PREDICATE_CLASS>
        UE_ALLOWSHRINKING_BOOL_DEPRECATED("RemoveAllSwap")
        UE_NODEBUG FORCEINLINE SizeType RemoveAllSwap(const PREDICATE_CLASS& Predicate, bool bAllowShrinking)
        {
            return RemoveAllSwap(Predicate, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
        }

        /**
         * Removes the first occurrence of the specified item in the array. This version is much more efficient
         * O(Count) instead of O(ArrayNum), but does not preserve the order
         *
         * @param Item The item to remove
         * @param AllowShrinking Tell if this function can shrink the memory in-use if suitable.
         *
         * @returns The number of items removed. For RemoveSingleItem, this is always either 0 or 1.
         * @see Add, Insert, Remove, RemoveAll, RemoveAllSwap, RemoveSwap
         */
        SizeType RemoveSingleSwap(const ElementType& Item, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
        {
            SizeType Index = Find(Item);
            if (Index == INDEX_NONE)
            {
                return 0;
            }

            RemoveAtSwap(Index, 1, AllowShrinking);

            // Removed one item
            return 1;
        }
        UE_ALLOWSHRINKING_BOOL_DEPRECATED("RemoveSingleSwap")
        UE_NODEBUG FORCEINLINE SizeType RemoveSingleSwap(const ElementType& Item, bool bAllowShrinking)
        {
            return RemoveSingleSwap(Item, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
        }

        /**
         * Removes all instances of a given item from the array.
         *
         * This version is much more efficient, because it uses RemoveAtSwap
         * internally which is O(Count) instead of RemoveAt which is O(ArrayNum),
         * but does not preserve the order.
         *
         * @param Item The item to remove
         * @param AllowShrinking Tell if this function can shrink the memory in-use if suitable.
         *
         * @returns Number of elements removed.
         * @see Add, Insert, Remove, RemoveAll, RemoveAllSwap
         */
        SizeType RemoveSwap(const ElementType& Item, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
        {
            CheckAddress(&Item);

            const SizeType OriginalNum = ArrayNum;
            bool bRemoved = false;
            for (SizeType Index = 0; Index < ArrayNum; Index++)
            {
                if ((*this)[Index] == Item)
                {
                    bRemoved = true;
                    RemoveAtSwap(Index--, EAllowShrinking::No);
                }
            }

            if (bRemoved && AllowShrinking == EAllowShrinking::Yes)
            {
                UE::Core::Private::ReallocShrink<UE::Core::Private::GetAllocatorFlags<AllocatorType>()>(
                    sizeof(ElementType),
                    alignof(ElementType),
                    AllocatorInstance,
                    ArrayNum,
                    ArrayMax
                );
            }

            return OriginalNum - ArrayNum;
        }
        UE_ALLOWSHRINKING_BOOL_DEPRECATED("RemoveSwap")
        UE_NODEBUG FORCEINLINE SizeType RemoveSwap(const ElementType& Item, bool bAllowShrinking)
        {
            return RemoveSwap(Item, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
        }

        /**
         * Element-wise array memory swap.
         *
         * @param FirstIndexToSwap Position of the first element to swap.
         * @param SecondIndexToSwap Position of the second element to swap.
         */
        FORCEINLINE void SwapMemory(SizeType FirstIndexToSwap, SizeType SecondIndexToSwap)
        {
            FMemory::Memswap(
                (uint8*)AllocatorInstance.GetAllocation() + (GetTypeSize()*FirstIndexToSwap),
                (uint8*)AllocatorInstance.GetAllocation() + (GetTypeSize()*SecondIndexToSwap),
                GetTypeSize()
                );
        }

        /**
         * Element-wise array element swap.
         *
         * This version is doing more sanity checks than SwapMemory.
         *
         * @param FirstIndexToSwap Position of the first element to swap.
         * @param SecondIndexToSwap Position of the second element to swap.
         */
        FORCEINLINE void Swap(SizeType FirstIndexToSwap, SizeType SecondIndexToSwap)
        {
            check((FirstIndexToSwap >= 0) && (SecondIndexToSwap >= 0));
            check((ArrayNum > FirstIndexToSwap) && (ArrayNum > SecondIndexToSwap));
            if (FirstIndexToSwap != SecondIndexToSwap)
            {
                SwapMemory(FirstIndexToSwap, SecondIndexToSwap);
            }
        }

        // TODO: Fix this finditem by class
        
        /**
         * Searches for the first entry of the specified type, will only work with
         * TArray<UObject*>. Optionally return the item's index, and can specify
         * the start index.
         *
         * @param Item (Optional output) If it's not null, then it will point to
         *             the found element. Untouched if element hasn't been found.
         * @param ItemIndex (Optional output) If it's not null, then it will be set
         *             to the position of found element in the array. Untouched if
         *             element hasn't been found.
         * @param StartIndex (Optional) Index in array at which the function should
         *             start to look for element.
         * @returns True if element was found. False otherwise.
         */
        /*template<typename SearchType>
        bool FindItemByClass(SearchType **Item = nullptr, SizeType *ItemIndex = nullptr, SizeType StartIndex = 0) const
        {
            UClass* SearchClass = SearchType::StaticClass();
            for (SizeType Idx = StartIndex; Idx < ArrayNum; Idx++)
            {
                if ((*this)[Idx] != nullptr && (*this)[Idx]->IsA(SearchClass))
                {
                    if (Item != nullptr)
                    {
                        *Item = (SearchType*)((*this)[Idx]);
                    }
                    if (ItemIndex != nullptr)
                    {
                        *ItemIndex = Idx;
                    }
                    return true;
                }
            }
            return false;
        }*/

        // Iterators
        typedef TIndexedContainerIterator<      TArray,       ElementType, SizeType> TIterator;
        typedef TIndexedContainerIterator<const TArray, const ElementType, SizeType> TConstIterator;

        /**
         * Creates an iterator for the contents of this array
         *
         * @returns The iterator.
         */
        TIterator CreateIterator()
        {
            return TIterator(*this);
        }

        /**
         * Creates a const iterator for the contents of this array
         *
         * @returns The const iterator.
         */
        TConstIterator CreateConstIterator() const
        {
            return TConstIterator(*this);
        }


        typedef       TRangeBasedIterator<ElementType, false> RangedForIteratorType;
        typedef const TRangeBasedIterator<ElementType, true> RangedForConstIteratorType;


    public:
        /**
         * DO NOT USE DIRECTLY
         * STL-like iterators to enable range-based for loop support.
         */
        FORCEINLINE RangedForIteratorType      begin()       { return RangedForIteratorType(GetData()); }
        FORCEINLINE RangedForIteratorType      end()
        {
            auto* ptr = reinterpret_cast<ElementType*>(reinterpret_cast<uint8*>(GetData()) + Num() * GetTypeSize());
            return RangedForIteratorType(ptr);
        }

        FORCEINLINE RangedForConstIteratorType begin() const { return RangedForConstIteratorType(GetData()); }
        FORCEINLINE RangedForConstIteratorType end() const   
        {
            auto* ptr = reinterpret_cast<const ElementType*>(reinterpret_cast<const uint8*>(GetData()) + Num() * GetTypeSize());
            return RangedForConstIteratorType(ptr);
        }

    public:
        /**
         * Sorts the array assuming < operator is defined for the item type.
         *
         * @note: If your array contains raw pointers, they will be automatically dereferenced during sorting.
         *        Therefore, your array will be sorted by the values being pointed to, rather than the pointers' values.
         *        If this is not desirable, please use Algo::Sort(MyArray) instead.
         *        The auto-dereferencing behavior does not occur with smart pointers.
         */
        // TODO: Implement Sorting
        /*void Sort()
        {
            ::Sort(GetData(), Num());
        }*/

        /**
         * Sorts the array using user define predicate class.
         *
         * @param Predicate Predicate class instance.
         *
         * @note: If your array contains raw pointers, they will be automatically dereferenced during sorting.
         *        Therefore, your predicate will be passed references rather than pointers.
         *        If this is not desirable, please use Algo::Sort(MyArray, Predicate) instead.
         *        The auto-dereferencing behavior does not occur with smart pointers.
         */
        // TODO: Implement Sorting
        /*template <class PREDICATE_CLASS>
        void Sort(const PREDICATE_CLASS& Predicate)
        {
            ::Sort(GetData(), Num(), Predicate);
        }*/

        /**
         * Stable sorts the array assuming < operator is defined for the item type.
         *
         * Stable sort is slower than non-stable algorithm.
         *
         * @note: If your array contains raw pointers, they will be automatically dereferenced during sorting.
         *        Therefore, your array will be sorted by the values being pointed to, rather than the pointers' values.
         *        The auto-dereferencing behavior does not occur with smart pointers.
         */
        /*void StableSort()
        {
            ::StableSort(GetData(), Num());
        }*/

        /**
         * Stable sorts the array using user defined predicate class.
         *
         * Stable sort is slower than non-stable algorithm.
         *
         * @param Predicate Predicate class instance
         *
         * @note: If your array contains raw pointers, they will be automatically dereferenced during sorting.
         *        Therefore, your predicate will be passed references rather than pointers.
         *        The auto-dereferencing behavior does not occur with smart pointers.
         */
        /*template <class PREDICATE_CLASS>
        void StableSort(const PREDICATE_CLASS& Predicate)
        {
            ::StableSort(GetData(), Num(), Predicate);
        }*/
        

        auto SetDataPtr(InElementType* NewDataPtr) -> void
        {
            if constexpr (IsTInlineAllocator<InAllocator>)
            {
                throw std::runtime_error{"TArray::SetDataPtr cannot be used with TInlineAllocator"};
            }
            else
            {
                AllocatorInstance.Data = std::bit_cast<FScriptContainerElement*>(NewDataPtr);
            }
        }

        auto SetMax(SizeType NewArrayMax) -> void
        {
            ArrayMax = NewArrayMax;
        }

        // Temporary function
        // Transfers ownership of another data ptr to this instance of TArray
        // The 'other' TArray becomes zeroed
        auto CopyFast(TArray<InElementType, Allocator>& other) -> void
        {
            if constexpr (IsTInlineAllocator<InAllocator>)
            {
                throw std::runtime_error{"TArray::copy_fast cannot be used with TInlineAllocator"};
            }

            AllocatorInstance.MoveToEmpty(other.AllocatorInstance);
            ArrayNum = other.ArrayNum;
            ArrayMax = other.ArrayMax;

            // Hack to prevent deallocation when 'other' goes out of scope
            other.AllocatorInstance.Data = nullptr;
            other.ArrayNum = 0;
            other.ArrayMax = 0;
        }

        FORCENOINLINE void ResizeGrow(SizeType OldNum)
        {
            ArrayMax = AllocatorInstance.CalculateSlackGrow(ArrayNum, ArrayMax, GetTypeSize());
            AllocatorInstance.ResizeAllocation(OldNum, ArrayMax, GetTypeSize());
        }
        FORCENOINLINE void ResizeShrink()
        {
            const SizeType NewArrayMax = AllocatorInstance.CalculateSlackShrink(ArrayNum, ArrayMax, GetTypeSize());
            if (NewArrayMax != ArrayMax)
            {
                ArrayMax = NewArrayMax;
                if (!(ArrayMax >= ArrayNum)) { return; }
                AllocatorInstance.ResizeAllocation(ArrayNum, ArrayMax, GetTypeSize());
            }
        }
        FORCENOINLINE void ResizeTo(SizeType NewMax)
        {
            if (NewMax)
            {
                NewMax = AllocatorInstance.CalculateSlackReserve(NewMax, GetTypeSize());
            }
            if (NewMax != ArrayMax)
            {
                ArrayMax = NewMax;
                AllocatorInstance.ResizeAllocation(ArrayNum, ArrayMax, GetTypeSize());
            }
        }
        FORCENOINLINE void ResizeForCopy(SizeType NewMax, SizeType PrevMax)
        {
            if (NewMax)
            {
                NewMax = AllocatorInstance.CalculateSlackReserve(NewMax, GetTypeSize());
            }
            if (NewMax > PrevMax)
            {
                AllocatorInstance.ResizeAllocation(0, NewMax, GetTypeSize());
                ArrayMax = NewMax;
            }
            else
            {
                ArrayMax = PrevMax;
            }
        }

        /**
         * Copies data from one array into this array. Uses the fast path if the
         * data in question does not need a constructor.
         *
         * @param Source The source array to copy
         * @param PrevMax The previous allocated size
         * @param ExtraSlack Additional amount of memory to allocate at
         *                   the end of the buffer. Counted in elements. Zero by
         *                   default.
         */
        template <typename OtherElementType, typename OtherSizeType>
        void CopyToEmpty(const OtherElementType* OtherData, OtherSizeType OtherNum, SizeType PrevMax, SizeType ExtraSlack)
        {
            SizeType NewNum = (SizeType)OtherNum;
            if (!((OtherSizeType)NewNum == OtherNum)) { Output::send<LogLevel::Error>(STR("Invalid number of elements to add to this array type: {}"), (unsigned long long)NewNum); return; };
            
            ArrayNum = NewNum;
            if (OtherNum || ExtraSlack || PrevMax)
            {
                ResizeForCopy(NewNum + ExtraSlack, PrevMax);
                ConstructItems<ElementType>(GetData(), OtherData, OtherNum);
            }
            else
            {
                ArrayMax = AllocatorInstance.GetInitialCapacity();
            }
        }
    };
}
