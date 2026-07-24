#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/FAssetData.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>

namespace RC::Unreal
{
    class UAssetRegistry;

    class RC_UE_API UAssetRegistryHelpers : public UObject
    {
    public:
        using StaticReflectedFunction = StaticReflectedFunctionBase<UAssetRegistryHelpers>;

        static inline UAssetRegistryHelpers* Self{nullptr};
        struct StaticFunctions
        {
            static inline StaticReflectedFunction GetAssetRegistry{STR("/Script/AssetRegistry.AssetRegistryHelpers:GetAssetRegistry")};
            static inline StaticReflectedFunction GetAsset{STR("/Script/AssetRegistry.AssetRegistryHelpers:GetAsset")};
        };

    public:
        struct GetAssetRegistry_Params
        {
            FScriptInterface ReturnValue; // 0x0
        };

        struct GetAsset_Params
        {
        private:
            FAssetData InAssetData_Private; // 0x0
            UObject* ReturnValue_Private; // 0x50

        public:
            GetAsset_Params(const FAssetData& InAssetData);
            FAssetData InAssetData();
            UObject* ReturnValue();
        };

    private:
        auto static VerifySelf() -> bool;

    public:
        auto static GetAssetRegistry() -> FScriptInterface;
        auto static GetAsset(FAssetData& InAssetData) -> UObject*;
    };
}


