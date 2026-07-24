// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/GenericPlatform/GenericPlatformAtomics.hpp"

namespace RC::Unreal
{
    /**
     * Linux implementation of the Atomics OS functions
     */
    struct FLinuxPlatformAtomics
        : public FGenericPlatformAtomics
    {
        static FORCEINLINE int8 InterlockedIncrement(volatile int8* Value)
        {
            return __sync_add_and_fetch(Value, 1);
        }

        static FORCEINLINE int16 InterlockedIncrement(volatile int16* Value)
        {
            return __sync_add_and_fetch(Value, 1);
        }

        static FORCEINLINE int32 InterlockedIncrement(volatile int32* Value)
        {
            return __sync_add_and_fetch(Value, 1);
        }

        static FORCEINLINE int64 InterlockedIncrement(volatile int64* Value)
        {
            return __sync_add_and_fetch(Value, 1);
        }

        static FORCEINLINE int8 InterlockedDecrement(volatile int8* Value)
        {
            return __sync_sub_and_fetch(Value, 1);
        }

        static FORCEINLINE int16 InterlockedDecrement(volatile int16* Value)
        {
            return __sync_sub_and_fetch(Value, 1);
        }

        static FORCEINLINE int32 InterlockedDecrement(volatile int32* Value)
        {
            return __sync_sub_and_fetch(Value, 1);
        }

        static FORCEINLINE int64 InterlockedDecrement(volatile int64* Value)
        {
            return __sync_sub_and_fetch(Value, 1);
        }

        static FORCEINLINE int8 InterlockedAdd(volatile int8* Value, int8 Amount)
        {
            return __sync_fetch_and_add(Value, Amount);
        }

        static FORCEINLINE int16 InterlockedAdd(volatile int16* Value, int16 Amount)
        {
            return __sync_fetch_and_add(Value, Amount);
        }

        static FORCEINLINE int32 InterlockedAdd(volatile int32* Value, int32 Amount)
        {
            return __sync_fetch_and_add(Value, Amount);
        }

        static FORCEINLINE int64 InterlockedAdd(volatile int64* Value, int64 Amount)
        {
            return __sync_fetch_and_add(Value, Amount);
        }

        static FORCEINLINE int8 InterlockedExchange(volatile int8* Value, int8 Exchange)
        {
            return __sync_lock_test_and_set(Value, Exchange);
        }

        static FORCEINLINE int16 InterlockedExchange(volatile int16* Value, int16 Exchange)
        {
            return __sync_lock_test_and_set(Value, Exchange);
        }

        static FORCEINLINE int32 InterlockedExchange(volatile int32* Value, int32 Exchange)
        {
            return __sync_lock_test_and_set(Value, Exchange);
        }

        static FORCEINLINE int64 InterlockedExchange(volatile int64* Value, int64 Exchange)
        {
            return __sync_lock_test_and_set(Value, Exchange);
        }

        static FORCEINLINE void* InterlockedExchangePtr(void* volatile* Dest, void* Exchange)
        {
            return __sync_lock_test_and_set(Dest, Exchange);
        }

        static FORCEINLINE int8 InterlockedCompareExchange(volatile int8* Dest, int8 Exchange, int8 Comparand)
        {
            return __sync_val_compare_and_swap(Dest, Comparand, Exchange);
        }

        static FORCEINLINE int16 InterlockedCompareExchange(volatile int16* Dest, int16 Exchange, int16 Comparand)
        {
            return __sync_val_compare_and_swap(Dest, Comparand, Exchange);
        }

        static FORCEINLINE int32 InterlockedCompareExchange(volatile int32* Dest, int32 Exchange, int32 Comparand)
        {
            return __sync_val_compare_and_swap(Dest, Comparand, Exchange);
        }

        static FORCEINLINE int64 InterlockedCompareExchange(volatile int64* Dest, int64 Exchange, int64 Comparand)
        {
            return __sync_val_compare_and_swap(Dest, Comparand, Exchange);
        }

        static FORCEINLINE int8 InterlockedAnd(volatile int8* Value, const int8 AndValue)
        {
            return __sync_fetch_and_and(Value, AndValue);
        }

        static FORCEINLINE int16 InterlockedAnd(volatile int16* Value, const int16 AndValue)
        {
            return __sync_fetch_and_and(Value, AndValue);
        }

        static FORCEINLINE int32 InterlockedAnd(volatile int32* Value, const int32 AndValue)
        {
            return __sync_fetch_and_and(Value, AndValue);
        }

        static FORCEINLINE int64 InterlockedAnd(volatile int64* Value, const int64 AndValue)
        {
            return __sync_fetch_and_and(Value, AndValue);
        }

        static FORCEINLINE int8 InterlockedOr(volatile int8* Value, const int8 OrValue)
        {
            return __sync_fetch_and_or(Value, OrValue);
        }

        static FORCEINLINE int16 InterlockedOr(volatile int16* Value, const int16 OrValue)
        {
            return __sync_fetch_and_or(Value, OrValue);
        }

        static FORCEINLINE int32 InterlockedOr(volatile int32* Value, const int32 OrValue)
        {
            return __sync_fetch_and_or(Value, OrValue);
        }

        static FORCEINLINE int64 InterlockedOr(volatile int64* Value, const int64 OrValue)
        {
            return __sync_fetch_and_or(Value, OrValue);
        }

        static FORCEINLINE int8 InterlockedXor(volatile int8* Value, const int8 XorValue)
        {
            return __sync_fetch_and_xor(Value, XorValue);
        }

        static FORCEINLINE int16 InterlockedXor(volatile int16* Value, const int16 XorValue)
        {
            return __sync_fetch_and_xor(Value, XorValue);
        }

        static FORCEINLINE int32 InterlockedXor(volatile int32* Value, const int32 XorValue)
        {
            return __sync_fetch_and_xor(Value, XorValue);
        }

        static FORCEINLINE int64 InterlockedXor(volatile int64* Value, const int64 XorValue)
        {
            return __sync_fetch_and_xor(Value, XorValue);
        }

        static FORCEINLINE int8 AtomicRead(volatile const int8* Src)
        {
            return __sync_val_compare_and_swap(const_cast<int8*>(Src), 0, 0);
        }

        static FORCEINLINE int16 AtomicRead(volatile const int16* Src)
        {
            return __sync_val_compare_and_swap(const_cast<int16*>(Src), 0, 0);
        }

        static FORCEINLINE int32 AtomicRead(volatile const int32* Src)
        {
            return __sync_val_compare_and_swap(const_cast<int32*>(Src), 0, 0);
        }

        static FORCEINLINE int64 AtomicRead(volatile const int64* Src)
        {
            return __sync_val_compare_and_swap(const_cast<int64*>(Src), 0, 0);
        }

        static FORCEINLINE int8 AtomicRead_Relaxed(volatile const int8* Src) { return *Src; }
        static FORCEINLINE int16 AtomicRead_Relaxed(volatile const int16* Src) { return *Src; }
        static FORCEINLINE int32 AtomicRead_Relaxed(volatile const int32* Src) { return *Src; }
        static FORCEINLINE int64 AtomicRead_Relaxed(volatile const int64* Src) { return *Src; }

        static FORCEINLINE void AtomicStore(volatile int8* Src, int8 Val) { __sync_lock_test_and_set(Src, Val); }
        static FORCEINLINE void AtomicStore(volatile int16* Src, int16 Val) { __sync_lock_test_and_set(Src, Val); }
        static FORCEINLINE void AtomicStore(volatile int32* Src, int32 Val) { __sync_lock_test_and_set(Src, Val); }
        static FORCEINLINE void AtomicStore(volatile int64* Src, int64 Val) { __sync_lock_test_and_set(Src, Val); }

        static FORCEINLINE void AtomicStore_Relaxed(volatile int8* Src, int8 Val) { *Src = Val; }
        static FORCEINLINE void AtomicStore_Relaxed(volatile int16* Src, int16 Val) { *Src = Val; }
        static FORCEINLINE void AtomicStore_Relaxed(volatile int32* Src, int32 Val) { *Src = Val; }
        static FORCEINLINE void AtomicStore_Relaxed(volatile int64* Src, int64 Val) { *Src = Val; }

        static FORCEINLINE void* InterlockedCompareExchangePointer(void* volatile* Dest, void* Exchange, void* Comparand)
        {
            return __sync_val_compare_and_swap(Dest, Comparand, Exchange);
        }

        static FORCEINLINE bool CanUseCompareExchange128()
        {
            return false;
        }
    };

    typedef FLinuxPlatformAtomics FPlatformAtomics;
}
