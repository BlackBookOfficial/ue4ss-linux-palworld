#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/UObjectMacros.hpp>
#include <Unreal/TypeChecker.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/CoreUObject/UObject/TopLevelAssetPath.hpp>

namespace RC::Unreal
{
    using FAssetDataTagMapSharedView = void*; // <-- Wrapper to a pointer to a map

    inline bool bFAssetDataAvailable = false;

    // Note that this struct is only valid in 4.27+
    // We don't actually use this right now but if we do later, then we'll need to abstract it the same way we did FAssetData
    struct FAssetBundleData
    {
        // Only in <4.27
        // FPrimaryAssetId BundleScope;

        FName BundleName;
        TArray<FSoftObjectPath> BundleAssets;
    };

    struct RC_UE_API FAssetData51Plus
    {
        // Reflected
        FName PackageName;                          // Size: 0x8
        FName PackagePath;                          // Size: 0x8
        FName AssetName;                            // Size: 0x8
        FName AssetClass;                           // Size: 0x8
        FTopLevelAssetPath AssetClassPath;          // Size: 0x10

        // Non-reflected
        // It gets bad below here because of changes that the ue devs made
        // I've put notes for each member variable where I noticed a changed
        // It looks like FAssetData needs to be put into a VC because of this
        // We really only need the reflected data but we also need the size so that the TArray for_each loop works properly
        // T size of '/Script/CoreUObject.AssetData' does take into account the unreflected variables, so we could use that instead of the hardcoded struct for the size
        using FSetElementId = int32_t;
        using FChunkArrayRegistryHandle = FSetElementId;
        FChunkArrayRegistryHandle ChunkArrayRegistryHandle; // Size: 0x4
        FAssetDataTagMapSharedView TagsAndValues;   // Size: 0x8
        // Real type: TSharedPtr<FAssetBundleData, ESPMode::ThreadSafe>
        FAssetBundleData* TaggedAssetBundles;
        // The ChunkIDs array allocator was changed to 'TInlineAllocator<2>' in 4.27
        TArray<int32, TInlineAllocator<2>> ChunkIDs;                   // Size: 0x18
        uint32 PackageFlags;                      // Size: 0x4
    };

    // Size in UE4.25 according to Rider: 84 (Is this dec or hex ? I'm thinking it's dec, but I'm not 100% sure)
    // Size in UE4.25 according to 'ScriptStruct::get_size()': 0x50
    // 0x4C currently (0x50 if you take into account alignment, sizeof(FAssetData) in UE4SS gives 0x50)
    struct RC_UE_API FAssetData427Plus
    {
        // Reflected
        FName ObjectPath;                           // Size: 0x8
        FName PackageName;                          // Size: 0x8
        FName PackagePath;                          // Size: 0x8
        FName AssetName;                            // Size: 0x8
        FName AssetClass;                           // Size: 0x8

        // Non-reflected
        // It gets bad below here because of changes that the ue devs made
        // I've put notes for each member variable where I noticed a changed
        // It looks like FAssetData needs to be put into a VC because of this
        // We really only need the reflected data but we also need the size so that the TArray for_each loop works properly
        // T size of '/Script/CoreUObject.AssetData' does take into account the unreflected variables, so we could use that instead of the hardcoded struct for the size
        FAssetDataTagMapSharedView TagsAndValues;   // Size: 0x8
        // Real type: TSharedPtr<FAssetBundleData, ESPMode::ThreadSafe>
        FAssetBundleData* TaggedAssetBundles;
        // The ChunkIDs array allocator was changed to 'TInlineAllocator<2>' in 4.27
        TArray<int32, TInlineAllocator<2>> ChunkIDs;                   // Size: 0x18
        uint32 PackageFlags;                      // Size: 0x4
    };

    struct RC_UE_API FAssetDataPre427
    {
        // Reflected
        FName ObjectPath;                           // Size: 0x8
        FName PackageName;                          // Size: 0x8
        FName PackagePath;                          // Size: 0x8
        FName AssetName;                            // Size: 0x8
        FName AssetClass;                           // Size: 0x8

        // Non-reflected
        // It gets bad below here because of changes that the ue devs made
        // I've put notes for each member variable where I noticed a changed
        // It looks like FAssetData needs to be put into a VC because of this
        // We really only need the reflected data but we also need the size so that the TArray for_each loop works properly
        // T size of '/Script/CoreUObject.AssetData' does take into account the unreflected variables, so we could use that instead of the hardcoded struct for the size
        FAssetDataTagMapSharedView TagsAndValues;   // Size: 0x8
        uint8_t padding[0x8]; // Appears to be right, but how am I missing 8 bytes ?
        // The ChunkIDs array allocator was changed to 'TInlineAllocator<2>' in 4.27
        TArray<int32> ChunkIDs;                   // Size: 0x10
        uint32 PackageFlags;                      // Size: 0x4
    };

    // Abstracted FAssetData
    // Used to ensure that it works before and after the 4.27 changes
    struct RC_UE_API FAssetData
    {
        // TODO: In 4.26+, AssetData is located in 'CoreUObject', in <4.26, AssetData is located in 'AssetRegistry'
        //       Do we need to solve this ? And if so, how ?
        DECLARE_EXTERNAL_OBJECT_CLASS(FAssetData, CoreUObject)

    public:
        FAssetData();
        FAssetData(const FAssetData& Other);

    public:
        static constexpr int32 FAssetDataAssumedStaticSize = (sizeof(FAssetData427Plus) > sizeof(FAssetDataPre427) ? sizeof(FAssetData427Plus) : sizeof(FAssetDataPre427)) + 0x20;

        FName ObjectPath();
        FName PackageName();
        FName PackagePath();
        FName AssetName();
        FName AssetClass();
        FAssetDataTagMapSharedView TagsAndValues();
        FAssetBundleData* TaggedAssetBundles();
        /*TArray<int32>*/void ChunkIDs();
        TArray<int32>& OldChunkIDsUnsafe();
        TArray<int32, TInlineAllocator<2>>& NewChunkIDsUnsafe();
        uint32 PackageFlags();
        FTopLevelAssetPath& AssetClassPath();

        void SetObjectPath(FName);
        void SetPackageName(FName);
        void SetPackagePath(FName);
        void SetAssetName(FName);
        void SetAssetClass(FName);
        void SetTagsAndValues(FAssetDataTagMapSharedView);
        void SetTaggedAssetBundles(FAssetBundleData*);
        void SetChunkIDs(/*TArray<int32>*/);
        void SetOldChunkIDsUnsafe(TArray<int32>&);
        void SetNewChunkIDsUnsafe(TArray<int32, TInlineAllocator<2>>&);
        void SetPackageFlags(uint32);
        void SetAssetClassPath(FTopLevelAssetPath&);

        static int32 StaticSize();


    private:
        static int32 StaticSize_Private;

    private:
        // Storage on the stack so that we don't corrupt stack when copying
        // Size must be large enough to fit entire struct
        // For now, let's give it a larger size than needed to be future safe
        // We're also making sure at runtime that this size is large enough
        std::uint8_t Data[FAssetDataAssumedStaticSize]{0};
    };
}


