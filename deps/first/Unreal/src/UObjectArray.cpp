#include <Unreal/UObjectArray.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/UKismetSystemLibrary.hpp>

namespace RC::Unreal
{
#include <MemberVariableLayout_SrcWrapper_FUObjectItem.hpp>
#include <MemberVariableLayout_SrcWrapper_TUObjectArray.hpp>
#include <MemberVariableLayout_SrcWrapper_FUObjectArray.hpp>

    static int32_t GetFlagsFromFlagsAndRefCount(int64_t FlagsAndRefCount)
    {
        return static_cast<int32_t>(FlagsAndRefCount >> 32);
    }

    static int32_t GetRefCountFromFlagsAndRefCount(int64_t FlagsAndRefCount)
    {
        return static_cast<int32_t>(FlagsAndRefCount & 0xFFFFFFFF);
    }

    bool FUObjectItem::IsUnreachable() const
    {
        return !!(GetFlagsInternal() & static_cast<int32_t>(EInternalObjectFlags::Unreachable)) || !GetUObject();
    }

    bool FUObjectItem::IsPendingKill() const
    {
        return !!(GetFlagsInternal() & static_cast<int32_t>(EInternalObjectFlags::PendingKill));
    }

    void FUObjectItem::SetRootSet()
    {
        SetFlagsInternal(EInternalObjectFlags::RootSet);
    }

    void FUObjectItem::UnsetRootSet()
    {
        UnsetFlagsInternal(EInternalObjectFlags::RootSet);
    }

    bool FUObjectItem::IsRootSet()
    {
        return !!(GetFlagsInternal() & static_cast<int32_t>(EInternalObjectFlags::RootSet));
    }

    void FUObjectItem::SetGCKeep()
    {
        SetFlagsInternal(EInternalObjectFlags::GarbageCollectionKeepFlags);
    }

    void FUObjectItem::UnsetGCKeep()
    {
        UnsetFlagsInternal(EInternalObjectFlags::GarbageCollectionKeepFlags);
    }

    bool FUObjectItem::IsGCKeepSet()
    {
        return !!(GetFlagsInternal() & static_cast<int32_t>(EInternalObjectFlags::GarbageCollectionKeepFlags));
    }

    UObject* FUObjectItem::GetUObject() const
    {
        // Missing: Flag stuff for 5.7+
#if UE_ENABLE_FUOBJECT_ITEM_PACKING
        static_assert("GetUObject for 5.7+ with UE_ENABLE_FUOBJECT_ITEM_PACKING == 1 is unimplemented");
#else
        return std::bit_cast<UObject*>(GetObject());
#endif
    }

    bool FUObjectItem::HasAnyFlags(EInternalObjectFlags InFlags) const
    {
        return !!(GetFlagsInternal() & int32(InFlags));
    }

    int32_t FUObjectItem::GetFlagsInternal()
    {
        if (Version::IsAtLeast(5, 7))
        {
            return GetFlagsFromFlagsAndRefCount(GetFlagsAndRefCount());
        }
        else if (Version::IsAtLeast(4, 13))
        {
            return GetFlags();
        }
        else
        {
            return GetClusterAndFlags() & static_cast<int32>(EInternalObjectFlags::AllFlags);
        }
    }

    int32_t FUObjectItem::GetFlagsInternal() const
    {
        if (Version::IsAtLeast(5, 7))
        {
            return GetFlagsFromFlagsAndRefCount(GetFlagsAndRefCount());
        }
        else if (Version::IsAtLeast(4, 13))
        {
            return GetFlags();
        }
        else
        {
            return GetClusterAndFlags() & static_cast<int32>(EInternalObjectFlags::AllFlags);
        }
    }

    void FUObjectItem::SetFlagsInternal(EInternalObjectFlags InFlags)
    {
        if (Version::IsAtLeast(5, 7))
        {
            auto Flags = GetFlagsFromFlagsAndRefCount(GetFlagsAndRefCount());
            Flags |= static_cast<int32_t>(InFlags);
            GetFlagsAndRefCount() = static_cast<int64_t>(Flags) << 32 | GetRefCountFromFlagsAndRefCount(GetFlagsAndRefCount());
        }
        else if (Version::IsAtLeast(4, 13))
        {
            GetFlags() |= static_cast<int32_t>(InFlags);
        }
        else
        {
            GetClusterAndFlags() |= static_cast<int32_t>(InFlags);
        }
    }

    void FUObjectItem::UnsetFlagsInternal(EInternalObjectFlags InFlags)
    {
        if (Version::IsAtLeast(5, 7))
        {
            auto Flags = GetFlagsFromFlagsAndRefCount(GetFlagsAndRefCount());
            Flags &= ~static_cast<int32_t>(InFlags);
            GetFlagsAndRefCount() = static_cast<int64_t>(Flags) << 32 | GetRefCountFromFlagsAndRefCount(GetFlagsAndRefCount());
        }
        else if (Version::IsAtLeast(4, 13))
        {
            GetFlags() &= ~static_cast<int32_t>(InFlags);
        }
        else
        {
            GetClusterAndFlags() &= ~static_cast<int32_t>(InFlags);
        }
    }

    int32_t FUObjectItem::GetRefCountInternal()
    {
        if (Version::IsAtLeast(5, 7))
        {
            return GetRefCountFromFlagsAndRefCount(GetFlagsAndRefCount());
        }
        else
        {
            return GetRefCount();
        }
    }

    int32_t FUObjectItem::GetRefCountInternal() const
    {
        if (Version::IsAtLeast(5, 7))
        {
            return GetRefCountFromFlagsAndRefCount(GetFlagsAndRefCount());
        }
        else
        {
            return GetRefCount();
        }
    }

    bool FUObjectItem::IsValid(bool bEvenIfPendingKill) const
    {
        return bEvenIfPendingKill ? !IsUnreachable() : !(IsUnreachable() || IsPendingKill());
    }

    FUObjectItem* TUObjectArray::GetObjectPtr(int32_t Index) const
    {
        static const auto ItemSize = FUObjectItem::UEP_TotalSize();
#ifdef __linux__
        // Palworld Linux: FChunkedFixedUObjectArray layout.
        // GUObjectArray+0x10 = ObjObjects sub-struct.
        //   ObjObjects+0x00 (abs +0x10) = FUObjectItem** Objects (chunk array)
        //   ObjObjects+0x14 (abs +0x24) = int32 NumElements
        //   ObjObjects+0x18 (abs +0x28) = int32 MaxChunks
        //   ObjObjects+0x1c (abs +0x2c) = int32 NumChunks
        // Each chunk is a contiguous array of FUObjectItem (24 bytes each).
        // Chunk size = 65536 bytes / ItemSize = 65536/24 = 2730 items.
        // Wait — verified: each chunk holds up to 65536 items (not limited by 65536 bytes).
        // The engine allocates chunks large enough for 65536 FUObjectItems.
        // Items per chunk = 65536.
        // ItemSize is 24 (0x18) for Palworld.
        const int32_t ItemsPerChunk = 65536;
        const int32_t ChunkIndex = Index / ItemsPerChunk;
        const int32_t WithinChunk = Index % ItemsPerChunk;
        // ObjObjects base = GUObjectArray + 0x10 (the TUObjectArray sub-struct)
        auto* obj_objects = Helper::Casting::ptr_cast<uint8_t*>(const_cast<FUObjectArray*>(GUObjectArray), 0x10);
        // Objects (chunk array ptr) at ObjObjects+0x00
        FUObjectItem** chunks = *reinterpret_cast<FUObjectItem***>(obj_objects);
        if (!chunks || ChunkIndex < 0)
            return nullptr;
        FUObjectItem* chunk = chunks[ChunkIndex];
        if (!chunk)
            return nullptr;
        return reinterpret_cast<FUObjectItem*>(reinterpret_cast<uint8_t*>(chunk) + WithinChunk * ItemSize);
#else
        if (Version::IsAtMost(4, 19))
        {
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(GetObjects())[Index * ItemSize]);
        }
        else
        {
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(GetObjects())[Index * ItemSize]);
        }
#endif
    }

    FUObjectItem* TUObjectArray::GetObjectPtr(int32_t Index)
    {
        static const auto ItemSize = FUObjectItem::UEP_TotalSize();
#ifdef __linux__
        const int32_t ItemsPerChunk = 65536;
        const int32_t ChunkIndex = Index / ItemsPerChunk;
        const int32_t WithinChunk = Index % ItemsPerChunk;
        auto* obj_objects = Helper::Casting::ptr_cast<uint8_t*>(GUObjectArray, 0x10);
        FUObjectItem** chunks = *reinterpret_cast<FUObjectItem***>(obj_objects);
        if (!chunks || ChunkIndex < 0)
            return nullptr;
        FUObjectItem* chunk = chunks[ChunkIndex];
        if (!chunk)
            return nullptr;
        return reinterpret_cast<FUObjectItem*>(reinterpret_cast<uint8_t*>(chunk) + WithinChunk * ItemSize);
#else
        if (Version::IsAtMost(4, 19))
        {
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(GetObjects())[Index * ItemSize]);
        }
        else
        {
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(GetObjects())[Index * ItemSize]);
        }
#endif
    }

    const FUObjectItem& TUObjectArray::operator[](int32_t Index) const
    {
        return *GetObjectPtr(Index);
    }

    FUObjectItem& TUObjectArray::operator[](int32_t Index)
    {
        return *GetObjectPtr(Index);
    }

    void UObjectArray::SetupGUObjectArrayAddress(void* address)
    {
        GUObjectArray = static_cast<FUObjectArray*>(address);
    }

    void* UObjectArray::GetGUObjectArrayAddress()
    {
        return GUObjectArray;
    }

    bool UObjectArray::IsValid(FUObjectItem* ObjectItem, bool bEvenIfPendingKill)
    {
        return ObjectItem->IsValid(bEvenIfPendingKill);
    }

    bool UObjectArray::IsStale(FUObjectItem* ObjectItem, bool bEvenIfPendingKill)
    {
        return bEvenIfPendingKill ? (ObjectItem->IsPendingKill() || ObjectItem->IsUnreachable()) : (ObjectItem->IsUnreachable());
    }

    void UObjectArray::AddUObjectCreateListener(FUObjectCreateListener* Listener)
    {
        auto& CreateListeners = GUObjectArray->GetUObjectCreateListeners();
        if (CreateListeners.Contains(Listener))
        {
            throw std::runtime_error{"Cannot add a listener because it already exists in TArray"};
        }
        CreateListeners.Append(TArray{Listener});
    }

    void UObjectArray::RemoveUObjectCreateListener(FUObjectCreateListener* Listener)
    {
        GUObjectArray->GetUObjectCreateListeners().RemoveSingleSwap(Listener);
    }

    void UObjectArray::AddUObjectDeleteListener(FUObjectDeleteListener* Listener)
    {
        auto& DeleteListeners = GUObjectArray->GetUObjectDeleteListeners();
        if (DeleteListeners.Contains(Listener))
        {
            throw std::runtime_error{"Cannot add a listener because it already exists in TArray"};
        }
        DeleteListeners.Append(TArray{Listener});
    }

    void UObjectArray::RemoveUObjectDeleteListener(FUObjectDeleteListener* Listener)
    {
        GUObjectArray->GetUObjectDeleteListeners().RemoveSingleSwap(Listener);
    }

    int32_t UObjectArray::GetNumElements()
    {
#ifdef __linux__
        // Palworld Linux: FChunkedFixedUObjectArray layout.
        // GUObjectArray+0x10 = ObjObjects sub-struct. NumElements is at ObjObjects+0x14
        // (absolute GUObjectArray+0x24). Verified via patternsleuth Linux patterns
        // and runtime inspection (NumElements=357154 matches count of valid UObjects).
        return *Helper::Casting::ptr_cast<int32*>(GUObjectArray, 0x24);
#else
        return GUObjectArray->GetObjObjects().GetNumElements();
#endif
    }

    int32_t UObjectArray::GetNumChunks()
    {
#ifdef __linux__
        // Palworld Linux: NumChunks at GUObjectArray+0x2c
        return *Helper::Casting::ptr_cast<int32*>(GUObjectArray, 0x2c);
#else
        return GUObjectArray->GetObjObjects().GetNumChunks();
#endif
    }

    int32_t UObjectArray::GetObjectItemSize()
    {
        return FUObjectItem::UEP_TotalSize();
    }

    int32_t UObjectArray::GetObjectArraySize()
    {
        return UEP_TotalSize();
    }

    FUObjectItem* FUObjectArray::IndexToObject(int32_t Index)
    {
#ifdef __linux__
        if (Index >= 0 && Index < UObjectArray::GetNumElements())
        {
            return GUObjectArray->GetObjObjects().GetObjectPtr(Index);
        }
        else
        {
            return nullptr;
        }
#else
        if (Index >= 0 && Index < GUObjectArray->GetObjObjects().GetNumElements())
        {
            return &GUObjectArray->GetObjObjects()[Index];
        }
        else
        {
            return nullptr;
        }
#endif
    }

    int32 FUObjectArray::AllocateSerialNumber(int32 Index)
    {
        FUObjectItem* ObjectItem = IndexToObject(Index);
        checkSlow(ObjectItem);

        volatile int32 *SerialNumberPtr = &ObjectItem->GetSerialNumber();
        if (!*SerialNumberPtr)
        {
            // RE-UE4SS FIX (Corporalwill): [can't use MasterSerialNumber, so we use a library function that allocates as a side effect]
            // [TSoftObjectPtr<UObject> --> FWeakPtr --> AllocateSerialNumber]
            UKismetSystemLibrary::Conv_ObjectToSoftObjectReference(ObjectItem->GetUObject());
            // RE-UE4SS FIX END
        }
        return *SerialNumberPtr;
    }

    void UObjectArray::LockGUObjectArray()
    {
        // TODO: Implement in the mutex type in UVTD.
        //Windows::EnterCriticalSection(&GetObjObjectsCritical());
    }
    void UObjectArray::UnlockGUObjectArray()
    {
        // TODO: Implement in the mutex type in UVTD.
        //Windows::LeaveCriticalSection(&GetObjObjectsCritical());
    }

    FUObjectArray* GUObjectArray{};
}