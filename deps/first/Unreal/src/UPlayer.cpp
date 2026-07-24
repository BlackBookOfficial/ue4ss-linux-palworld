#include <Unreal/UPlayer.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UPlayer)

    std::unordered_map<File::StringType, uint32_t> UPlayer::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_UPlayer.hpp>
}