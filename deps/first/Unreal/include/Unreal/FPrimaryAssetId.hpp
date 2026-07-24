#pragma once

#include <NameTypes.hpp>

namespace RC::Unreal
{
    struct FPrimaryAssetType
    {
        FName Name{};
    };

    struct FPrimaryAssetId
    {
        FPrimaryAssetType PrimaryAssetType{};
        FName PrimaryAssetName{};

        FPrimaryAssetType GetPrimaryAssetType()
        {
            return PrimaryAssetType;
        }

        FName GetPrimaryAssetName()
        {
            return PrimaryAssetName;
        }
    };
}
