#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UAssetRegistryHelpers.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    FAssetData UAssetRegistryHelpers::GetAsset_Params::InAssetData()
    {
        return InAssetData_Private;
    }

    UObject* UAssetRegistryHelpers::GetAsset_Params::ReturnValue()
    {
        return Helper::Casting::ptr_cast_deref<UObject*>(this, UAssetRegistryHelpers::StaticFunctions::GetAsset.GetReturnValueOffset());
    }

    UAssetRegistryHelpers::GetAsset_Params::GetAsset_Params(const FAssetData& InAssetData) : InAssetData_Private(InAssetData)
    {
    }

    auto UAssetRegistryHelpers::VerifySelf() -> bool
    {
        if (!Self)
        {
            Self = UObjectGlobals::StaticFindObject<UAssetRegistryHelpers*>(nullptr, nullptr, STR("/Script/AssetRegistry.Default__AssetRegistryHelpers"));
            if (!Self)
            {
                Output::send(STR("Was unable to locate AssetRegistryHelpers\n"));
                return false;
            }
        }

        return true;
    }

    auto UAssetRegistryHelpers::GetAssetRegistry() -> FScriptInterface
    {
        if (!VerifySelf()) { return {}; }
        if (!StaticFunctions::GetAssetRegistry.IsValid()) { return {}; }

        GetAssetRegistry_Params Params{};
        StaticFunctions::GetAssetRegistry(Params);
        return Params.ReturnValue;
    }

    auto UAssetRegistryHelpers::GetAsset(FAssetData& InAssetData) -> UObject*
    {
        if (!VerifySelf()) { return nullptr; }
        if (!StaticFunctions::GetAsset.IsValid()) { return nullptr; }

        GetAsset_Params Params{InAssetData};
        StaticFunctions::GetAsset(Params);
        return Params.ReturnValue();
    }
}
