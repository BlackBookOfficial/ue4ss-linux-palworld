#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

//#include <Unreal/UClass.hpp>
#include <mutex>
#include <Constructs/Loop.hpp>

namespace RC::Unreal
{
    struct FUObjectItem;
    class UObject;
    class UStruct;
    class UClass;

    using ObjectSearcherForEachPredicate = std::function<LoopAction(UObject*)>;
    using ObjectSearcherInternalSignature = void(*)(UClass* Class, UStruct* SuperStruct, const ObjectSearcherForEachPredicate& Predicate, std::vector<const FUObjectItem*>*);
    void ObjectSearcherFastInternal(UClass* Class, UStruct* SuperStruct, const ObjectSearcherForEachPredicate& Predicate, std::vector<const FUObjectItem*>* Pool);
    void ObjectSearcherSlowInternal(UClass* Class, UStruct* SuperStruct, const ObjectSearcherForEachPredicate& Predicate, std::vector<const FUObjectItem*>* Pool);

    struct EmptyStaticClass
    {
        static UClass* StaticClass() { return nullptr; }
    };

    using AnyClass = EmptyStaticClass;
    using AnySuperStruct = EmptyStaticClass;

    struct ObjectSearcherPoolBase
    {
    public:
        virtual ~ObjectSearcherPoolBase() = default;
        virtual std::vector<const FUObjectItem*>* GetPool() = 0;
        virtual std::mutex& GetMutex() = 0;

        // Delete copy constructor and copy assignment operator
        ObjectSearcherPoolBase(const ObjectSearcherPoolBase&) = delete;
        ObjectSearcherPoolBase& operator=(const ObjectSearcherPoolBase&) = delete;

        // Delete move constructor and move assignment operator
        ObjectSearcherPoolBase(ObjectSearcherPoolBase&&) = delete;
        ObjectSearcherPoolBase& operator=(ObjectSearcherPoolBase&&) = delete;

    protected:
        ObjectSearcherPoolBase() = default;
    };

    template<typename ClassType, typename SuperStructType>
    struct ObjectSearcherPool : ObjectSearcherPoolBase
    {
    public:
        static inline std::vector<const FUObjectItem*> Pool{};
        // Pointer to the default generic slow searcher.
        static inline std::unique_ptr<ObjectSearcherPoolBase> UnderlyingSearcher;
        static inline std::mutex PoolMutex;

        std::vector<const FUObjectItem*>* GetPool() override { return &Pool; }
        std::mutex& GetMutex() override { return PoolMutex; }

        static void Add(const FUObjectItem* Item)
        {
            Pool.emplace_back(Item);
        }

        static void Remove(const FUObjectItem* Item)
        {
            Pool.erase(std::remove(Pool.begin(), Pool.end(), Item), Pool.end());
        }
    };

    struct ObjectSearcher
    {
    protected:
        UClass* Class{};
        UStruct* SuperStruct{};
        ObjectSearcherPoolBase* PoolPtr;
        ObjectSearcherInternalSignature InternalSearcher;

    public:
        ObjectSearcher(UClass* C, UStruct* S, ObjectSearcherPoolBase* P, ObjectSearcherInternalSignature IS) 
            : Class(C), SuperStruct(S), PoolPtr(P), InternalSearcher(IS) {}

        size_t PoolSize()
        { 
            size_t Size = 0;
            if (PoolPtr) {
                std::lock_guard<std::mutex> Lock(PoolPtr->GetMutex());
                Size = PoolPtr->GetPool()->size();
            }
            return Size;
        }

        bool IsFast()
        { 
            bool bIsFast = false;
            if (PoolPtr) {
                std::lock_guard<std::mutex> Lock(PoolPtr->GetMutex());
                bIsFast = !PoolPtr->GetPool()->empty();
            }
            return bIsFast;
        }

        void ForEach(const ObjectSearcherForEachPredicate& Predicate)
        {
            if (PoolPtr)
            {
                std::lock_guard<std::mutex> Lock(PoolPtr->GetMutex());
                InternalSearcher(Class, SuperStruct, Predicate, PoolPtr->GetPool());
            }
            else
            {
                InternalSearcher(Class, SuperStruct, Predicate, nullptr);
            }
        }
    };

    size_t HashSearcherKey(UClass* Class, UStruct* SuperStruct);

    template<typename ClassType, typename SuperStructType>
    size_t HashSearcherKey()
    {
        return HashSearcherKey(ClassType::StaticClass(), SuperStructType::StaticClass());
    }

    extern std::unordered_map<size_t, std::unique_ptr<ObjectSearcherPoolBase>> AllSearcherPools;

    ObjectSearcher FindObjectSearcher(UClass* Class, UStruct* SuperStruct);

    template<typename ClassType, typename SuperStructType = AnySuperStruct>
    ObjectSearcher FindObjectSearcher()
    {
        return FindObjectSearcher(ClassType::StaticClass(), SuperStructType::StaticClass());
    }
}


