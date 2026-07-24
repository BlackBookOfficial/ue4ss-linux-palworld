#include <bit>

#include <Unreal/ClassListener.hpp>
#include <Unreal/UnrealInitializer.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/Searcher/ObjectSearcher.hpp>
#include <Unreal/Searcher/ObjectSearcherProfiler.hpp>

namespace RC::Unreal
{
    FClassCreateListener FClassCreateListener::ClassCreateListener{};
    FClassDeleteListener FClassDeleteListener::ClassDeleteListener{};

    std::unordered_map<StringType, UObject*> FClassCreateListener::GlobalObjectCache{};
    std::unordered_map<UObject*, StringType> FClassCreateListener::GlobalObjectValueCache{};

    void CacheGlobalObject(UObject* Object)
    {
        if (!UnrealInitializer::StaticStorage::GlobalConfig.bUseUObjectArrayCache)
        {
            return;
        }
        auto [ValueIt, bWasEmplaced] = FClassCreateListener::GlobalObjectValueCache.emplace(Object, StringType{});
        if (bWasEmplaced)
        {
            auto FullName = Object->GetFullName();
            auto SpaceLocation = FullName.find(STR(" "));
            auto FullNameWithoutType = StringType{FullName.begin() + SpaceLocation + 1, FullName.end()};
            ValueIt->second = FullNameWithoutType;
            FClassCreateListener::GlobalObjectCache.emplace(FullNameWithoutType, Object);
        }
    }

    void InvalidateGlobalObject(UObject* Object)
    {
        if (!UnrealInitializer::StaticStorage::GlobalConfig.bUseUObjectArrayCache)
        {
            return;
        }
        if (auto ValueIt = FClassCreateListener::GlobalObjectValueCache.find(Object); ValueIt != FClassCreateListener::GlobalObjectValueCache.end())
        {
            FClassCreateListener::GlobalObjectCache.erase(ValueIt->second);
            FClassCreateListener::GlobalObjectValueCache.erase(ValueIt);
        }
    }

    UObject* GetGlobalObject(const StringType& FullNameWithoutType)
    {
        if (!UnrealInitializer::StaticStorage::GlobalConfig.bUseUObjectArrayCache)
        {
            return nullptr;
        }
        if (auto It = FClassCreateListener::GlobalObjectCache.find(FullNameWithoutType); It != FClassCreateListener::GlobalObjectCache.end())
        {
            return It->second;
        }
        else
        {
            return nullptr;
        }
    }

    void FClassCreateListener::NotifyUObjectCreated(const UObjectBase* Object, int32 Index)
    {
    }

    void FClassCreateListener::OnUObjectArrayShutdown()
    {
        UnrealInitializer::StaticStorage::bIsInitialized = false;
        UObjectArray::RemoveUObjectCreateListener(this);
    }

    void FClassDeleteListener::NotifyUObjectDeleted(const UObjectBase* Object, int32 Index)
    {
        OBJSEARCHER_PROFILE_REMOVE()
        InvalidateGlobalObject(std::bit_cast<UObject*>(Object));

        auto* ObjectItem = Object->GetObjectItem();

        // All classes.
        {
            std::lock_guard<std::mutex> Lock(ObjectSearcherPool<UClass, AnySuperStruct>::PoolMutex);
            ObjectSearcherPool<UClass, AnySuperStruct>::Remove(ObjectItem);
        }

        // All actor classes.
        {
            std::lock_guard<std::mutex> Lock(ObjectSearcherPool<UClass, AActor>::PoolMutex);
            ObjectSearcherPool<UClass, AActor>::Remove(ObjectItem);
        }

        // All actor instances.
        {
            std::lock_guard<std::mutex> Lock(ObjectSearcherPool<AActor, AnySuperStruct>::PoolMutex);
            ObjectSearcherPool<AActor, AnySuperStruct>::Remove(ObjectItem);
        }
    }

    void FClassDeleteListener::OnUObjectArrayShutdown()
    {
        UnrealInitializer::StaticStorage::bIsInitialized = false;
        UObjectArray::RemoveUObjectDeleteListener(this);
    }

}
