#pragma once

#include <unordered_map>
#include <unordered_set>

#include <Unreal/UObjectArray.hpp>
#include <File/Macros.hpp>

namespace RC::Unreal
{
    // The global cache can be used from anywhere.
    // It's used to retrieve, by full name without type, a UObject stored in GUObjectArray.
    // This is an example of a correct name (without type): /Script/Engine.Actor:K2_SetActorLocation
    // This is an example of an incorrect name (with type): Function /Script/Engine.Actor:K2_SetActorLocation
    void CacheGlobalObject(UObject* Object);
    void InvalidateGlobalObject(UObject* Object);
    UObject* GetGlobalObject(const StringType& FullNameWithoutType);

    struct RC_UE_API FClassCreateListener : public FUObjectCreateListener
    {
        static FClassCreateListener ClassCreateListener;
        static std::unordered_map<StringType, UObject*> GlobalObjectCache;
        static std::unordered_map<UObject*, StringType> GlobalObjectValueCache;

        void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index) override;
        void OnUObjectArrayShutdown() override;
    };

    struct RC_UE_API FClassDeleteListener : public FUObjectDeleteListener
    {
        static FClassDeleteListener ClassDeleteListener;

        void NotifyUObjectDeleted(const class UObjectBase* Object, int32 Index) override;
        void OnUObjectArrayShutdown() override;
    };
}

