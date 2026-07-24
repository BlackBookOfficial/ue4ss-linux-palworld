// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/HAL/Platform.hpp"
#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/Traits/IsContiguousContainer.hpp"

/// @cond DOXYGEN_WARNINGS
namespace RC::Unreal
{
    template<int IndexSize> class TSizedDefaultAllocator;
    using FDefaultAllocator = TSizedDefaultAllocator<32>;
    using FDefaultAllocator64 = TSizedDefaultAllocator<64>;
    class FDefaultSetAllocator;

    class FString;

    template<> struct TIsContiguousContainer<FString> { static constexpr bool Value = true; };

    template<typename T, typename Allocator = FDefaultAllocator> class TArray;
    template<typename T> using TArray64 = TArray<T, FDefaultAllocator64>;
    template<typename T, typename SizeType = int32> class TArrayView;
    template<typename T> using TArrayView64 = TArrayView<T, int64>;
    template<typename T, typename SizeType = int32> using TConstArrayView = TArrayView<const T, SizeType>;
    template<typename T> using TConstArrayView64 = TConstArrayView<T, int64>;
    template<typename T> class TTransArray;
    template<typename InKeyType, typename InValueType, bool bInAllowDuplicateKeys> struct TDefaultMapHashableKeyFuncs;
    template<typename InKeyType, typename InValueType, typename SetAllocator = FDefaultSetAllocator, typename KeyFuncs = TDefaultMapHashableKeyFuncs<InKeyType, InValueType, false> > class TMap;
    template<typename KeyType, typename ValueType, typename SetAllocator = FDefaultSetAllocator, typename KeyFuncs = TDefaultMapHashableKeyFuncs<KeyType, ValueType, true > > class TMultiMap;
    template <typename T = void > struct TLess;
    template <typename> struct TTypeTraits;
    template<typename InKeyType, typename InValueType, typename ArrayAllocator = FDefaultAllocator, typename SortPredicate = TLess<typename TTypeTraits<InKeyType>::ConstPointerType> > class TSortedMap;
    template<typename ElementType,bool bInAllowDuplicateKeys = false> struct DefaultKeyFuncs;
    template<typename InElementType, typename KeyFuncs = DefaultKeyFuncs<InElementType>, typename Allocator = FDefaultSetAllocator> class TSet;
    template<typename InElementType, typename InSizeType = int32> class TStridedView;
    template<typename T, typename SizeType = int32> using TConstStridedView = TStridedView<const T, SizeType>;

    // Legacy container used by FUObjectArray in UE versions < 4.11
    template<typename ElementType, int32 MaxTotalElements, int32 ElementsPerChunk> class TStaticIndirectArrayThreadSafeRead;

    // Lock-free list used by FUObjectArray::ObjAvailableList in UE < 4.27
    template<class T> class TLockFreePointerListLIFO;
    template<class T> using TLockFreePointerList = TLockFreePointerListLIFO<T>;
}
/// @endcond
