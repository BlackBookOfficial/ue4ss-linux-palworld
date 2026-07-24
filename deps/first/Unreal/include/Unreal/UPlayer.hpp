#pragma once

#include <Unreal/UObject.hpp>

namespace RC::Unreal
{
    class RC_UE_API UPlayer : public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UPlayer, Engine);

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_UPlayer.hpp>
    };
}



