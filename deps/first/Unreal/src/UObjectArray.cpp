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
        if (Version::IsAtMost(4, 19))
        {
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(GetObjects())[Index * ItemSize]);
        }
        else
        {
            const int32_t ChunkIndex = Index / NumElementsPerChunk;
            const int32_t WithinChunkIndex = Index % NumElementsPerChunk;
            const auto Chunk = GetObjects()[ChunkIndex];
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(Chunk)[WithinChunkIndex * ItemSize]);
        }
    }

    FUObjectItem* TUObjectArray::GetObjectPtr(int32_t Index)
    {
        static const auto ItemSize = FUObjectItem::UEP_TotalSize();
        if (Version::IsAtMost(4, 19))
        {
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(GetObjects())[Index * ItemSize]);
        }
        else
        {
            const int32_t ChunkIndex = Index / NumElementsPerChunk;
            const int32_t WithinChunkIndex = Index % NumElementsPerChunk;
            const auto Chunk = GetObjects()[ChunkIndex];
            return std::bit_cast<FUObjectItem*>(&std::bit_cast<uint8_t*>(Chunk)[WithinChunkIndex * ItemSize]);
        }
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
        return GUObjectArray->GetObjObjects().GetNumElements();
    }

    int32_t UObjectArray::GetNumChunks()
    {
        return GUObjectArray->GetObjObjects().GetNumChunks();
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
        if (Index >= 0 && Index < GUObjectArray->GetObjObjects().GetNumElements())
        {
            return &GUObjectArray->GetObjObjects()[Index];
        }
        else
        {
            return nullptr;
        }
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