#pragma once

#include <Unreal/AGameModeBase.hpp>

namespace RC::Unreal
{
    class ULocalMessage;

    struct FGameClassShortName
    {
        FString ShortName;
        FString GameClassName;
    };

    class RC_UE_API AGameMode : public AGameModeBase
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(AGameMode, Engine);

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_AGameMode.hpp>
    };
}



