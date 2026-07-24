#pragma once
#include <atomic>
#include <Unreal/Common.hpp>
#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/FAssetData.hpp>

namespace RC::Unreal
{
    class RC_UE_API UAssetRegistry : public UObject
    {
    public:
        struct Functions
        {
            static inline InstancedReflectedFunction GetAllAssets{STR("/Script/AssetRegistry.AssetRegistry:GetAllAssets")};
            static inline InstancedReflectedFunction GetAssetByObjectPath{STR("/Script/AssetRegistry.AssetRegistry:GetAssetByObjectPath")};
            static inline InstancedReflectedFunction GetAssetsByClass{STR("/Script/AssetRegistry.AssetRegistry:GetAssetsByClass")};
        };

    public:
        struct GetAllAssets_Params
        {
            TArray<FAssetData> OutAssetData; // 0x0 // Out-param
            bool bIncludeOnlyOnDiskAssets; // 0x10
            bool ReturnValue; // 0x11
        };

        struct GetAssetByObjectPath_Params
        {
            FName ObjectPath{}; // 0x0
            bool32 bIncludeOnlyOnDiskAssets{}; // 0x8
            uint32 Padding; // Alignment to make 'ReturnValue' be at its proper offset of 0x10
            FAssetData ReturnValue{}; // 0x10
        };

        struct GetAssetsByClass_Params
        {
            FName ClassName; // 0x0
            TArray<FAssetData> OutAssetData; // 0x8 // Out-param
            bool bSearchSubClasses; // 0x18
            bool ReturnValue; // 0x19
        };

    private:
        struct StaticStorage
        {
            static std::atomic_bool bAssetsAreLoading; // thread-safe bools
            static std::atomic_bool bShouldLoadAllAssets;
            static std::vector<FUObjectItem*> ForcefullyLoadedAssets;
            static uint64 MaxMemoryUsageDuringAssetLoading;
        };

    public:
        auto GetAllAssets(TArray<FAssetData>& OutAssetData, bool bIncludeOnlyOnDiskAssets) -> bool;
        FAssetData GetAssetByObjectPath(const FName ObjectPath, bool bIncludeOnlyOnDiskAssets = false);
        bool GetAssetsByClass(FName ClassName, TArray<FAssetData>& OutAssetData, bool bSearchSubClasses = false);

        // Custom functions -> START
        auto static AssetsAreLoading() -> bool { return StaticStorage::bAssetsAreLoading; }
        auto static ShouldLoadAllAssets() -> bool { return StaticStorage::bShouldLoadAllAssets; }
        auto static SetAssetsAreLoading(bool new_value) -> void { StaticStorage::bAssetsAreLoading = new_value; }
        auto static SetShouldLoadAllAssets(bool new_value) -> void { StaticStorage::bShouldLoadAllAssets = new_value; }
        auto static FreeAllForcefullyLoadedAssets() -> void;

    private:
        // Internal function, do not use!
        // Call 'load_all_assets()' to safely load all assets regardless of thread context
        // This function is responsible for loading all assets into GUObjectArray
        // Must be called from within the game thread
        auto static LoadAllAssetsThread() -> void;

    public:
        // Helper function to load all assets from the AssetRegistry into GUObjectArray
        auto static LoadAllAssets() -> void;
        auto static SetMaxMemoryUsageDuringAssetLoading(int64 NewMaxMemoryUsageDuringAssetLoading) { StaticStorage::MaxMemoryUsageDuringAssetLoading = NewMaxMemoryUsageDuringAssetLoading; }
        // Custom functions -> END
    };
}


