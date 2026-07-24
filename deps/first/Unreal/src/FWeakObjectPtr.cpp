#include <Unreal/FWeakObjectPtr.hpp>
#include <Unreal/VersionedContainer/Container.hpp>
#include <Unreal/UObjectArray.hpp>
#include <Unreal/UObject.hpp>
#include <DynamicOutput/Output.hpp>

namespace RC::Unreal
{
    auto FWeakObjectPtr::SerialNumbersMatch(FUObjectItem* ObjectItem) const -> bool
    {
        return ObjectItem->GetSerialNumber() == ObjectSerialNumber;
    }

    auto FWeakObjectPtr::InternalGetObjectItem() const -> FUObjectItem*
    {
        if (ObjectSerialNumber == 0) { return nullptr; }
        if (ObjectIndex < 0) { return nullptr; }

        FUObjectItem* const ObjectItem = FUObjectArray::IndexToObject(ObjectIndex);

        if (!ObjectItem) { return nullptr; }
        if (!SerialNumbersMatch(ObjectItem)) { return nullptr; }

        return ObjectItem;
    }

    /**
    * Reset the weak pointer back to the null state
    */
    auto FWeakObjectPtr::Reset() -> void
    {
        ObjectIndex = INDEX_NONE;
        ObjectSerialNumber = 0;
    }

    /**
    * Copy from an object pointer
    * @param Object object to create a weak pointer to
    **/
    auto FWeakObjectPtr::operator=(const class UObject* Object) -> void
    {
        if (Object)
        {
            ObjectIndex = Object->GetInternalIndex();
            ObjectSerialNumber = FUObjectArray::AllocateSerialNumber(ObjectIndex);
        }
        else
        {
            Reset();
        }
    }

    auto FWeakObjectPtr::InternalGet(bool bEvenIfPendingKill) const -> UObject*
    {
        FUObjectItem* const ObjectItem = InternalGetObjectItem();
        return ((ObjectItem != nullptr) && UObjectArray::IsValid(ObjectItem, bEvenIfPendingKill)) ? ObjectItem->GetUObject() : nullptr;
    }

    UObject* FWeakObjectPtr::Get(/*bool bEvenIfGarbage = false*/) const
    {
        // Using a literal here allows the optimizer to remove branches later down the chain.
        return InternalGet(false);
    }

    UObject* FWeakObjectPtr::Get(bool bEvenIfGarbage) const
    {
        return InternalGet(bEvenIfGarbage);
    }

    bool FWeakObjectPtr::IsStale(bool bEvenIfPendingKill, bool bThreadsafeTest) const
    {
        if (ObjectSerialNumber == 0)
        {
            checkSlow(ObjectIndex == 0 || ObjectIndex == -1); // otherwise this is a corrupted weak pointer
            return false;
        }
        if (ObjectIndex < 0)
        {
            return true;
        }
        FUObjectItem* ObjectItem = FUObjectArray::IndexToObject(ObjectIndex);
        if (!ObjectItem)
        {
            return true;
        }
        if (!SerialNumbersMatch(ObjectItem))
        {
            return true;
        }
        if (bThreadsafeTest)
        {
            return false;
        }
        return FUObjectArray::IsStale(ObjectItem, bEvenIfPendingKill);
    }

    UObject* FWeakObjectPtr::GetEvenIfUnreachable() const
    {
        UObject* Result = nullptr;
        if (Internal_IsValid(true, true))
        {
            FUObjectItem* ObjectItem = FUObjectArray::IndexToObject(GetObjectIndex_Private());
            Result = static_cast<UObject*>(ObjectItem->GetUObject());
        }
        return Result;
    }
}
