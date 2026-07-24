#pragma once

// User API for UObjectArray related abstractions
// See Base.hpp / DerivedX.hpp files for implementations

#include <unordered_map>

#include <Unreal/Common.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/Core/Containers/StaticIndirectArray.hpp>
#include <Unreal/Core/Containers/LockFreeList.hpp>
#include <Unreal/BitfieldProxy.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    // This is implemented as a regular polymorphic object instead of using the vtable generator.
    // That's because the struct is very small and so is the vtable, and it hasn't changed from 4.12.
    // It's just easier to not use the vtable generator for this.
    class RC_UE_API FUObjectCreateListener
    {
    public:
        virtual ~FUObjectCreateListener() = default;
        virtual void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index) = 0;
        virtual void OnUObjectArrayShutdown() = 0;
    };

    class RC_UE_API FUObjectDeleteListener
    {
    public:
        virtual ~FUObjectDeleteListener() = default;
        virtual void NotifyUObjectDeleted(const class UObjectBase* Object, int32 Index) = 0;
        virtual void OnUObjectArrayShutdown() = 0;
    };

    struct RC_UE_API FUObjectItem
    {
    public:
#include <MemberVariableLayout_HeaderWrapper_FUObjectItem.hpp>

        void SetRootSet();
        void UnsetRootSet();
        bool IsRootSet();

        void SetGCKeep();
        void UnsetGCKeep();
        bool IsGCKeepSet();

        [[nodiscard]] bool IsUnreachable() const;
        [[nodiscard]] bool IsPendingKill() const;
        [[nodiscard]] bool IsValid(bool bEvenIfPendingKill) const;
        [[nodiscard]] class UObject* GetUObject() const;
        [[nodiscard]] bool HasAnyFlags(EInternalObjectFlags InFlags) const;

    private:
        int32_t GetFlagsInternal();
        int32_t GetFlagsInternal() const;
        void SetFlagsInternal(EInternalObjectFlags InFlags);
        void UnsetFlagsInternal(EInternalObjectFlags InFlags);
        int32_t GetRefCountInternal();
        int32_t GetRefCountInternal() const;
    };

    class RC_UE_API TUObjectArray
    {
    public:
#include <MemberVariableLayout_HeaderWrapper_TUObjectArray.hpp>

    public:
        // TODO: Expose NumElementsPerChunk to ini.
        static constexpr auto NumElementsPerChunk = 64 * 1024;

    public:
        [[nodiscard]] FUObjectItem* GetObjectPtr(int32_t Index) const;
        [[nodiscard]] FUObjectItem* GetObjectPtr(int32_t Index);
        [[nodiscard]] const FUObjectItem& operator[](int32_t Index) const;
        [[nodiscard]] FUObjectItem& operator[](int32_t Index);
    };

    class RC_UE_API FUObjectArray
    {
    public:
        using FUObjectCreateListener = Unreal::FUObjectCreateListener;
        using FUObjectDeleteListener = Unreal::FUObjectDeleteListener;
#include <MemberVariableLayout_HeaderWrapper_FUObjectArray.hpp>

    public:
        static void SetupGUObjectArrayAddress(void* address);
        static void* GetGUObjectArrayAddress();

    public:
        static bool IsValid(FUObjectItem* ObjectItem, bool bEvenIfPendingKill);
        static bool IsStale(FUObjectItem* ObjectItem, bool bEvenIfPendingKill);
        static void AddUObjectCreateListener(FUObjectCreateListener* Listener);
        static void RemoveUObjectCreateListener(FUObjectCreateListener* Listener);
        static void AddUObjectDeleteListener(FUObjectDeleteListener* Listener);
        static void RemoveUObjectDeleteListener(FUObjectDeleteListener* Listener);
        static int32_t GetNumElements();
        static int32_t GetNumChunks();
        static int32_t GetObjectItemSize();
        static int32_t GetObjectArraySize();
        static FUObjectItem* IndexToObject(int32_t Index);
        static int32 AllocateSerialNumber(int32 Index);

        void LockGUObjectArray();
        void UnlockGUObjectArray();
    };

    // Compatibility for code written before we renamed to FUObjectArray.
    using UObjectArray = FUObjectArray;

    RC_UE_API extern FUObjectArray* GUObjectArray;
}



