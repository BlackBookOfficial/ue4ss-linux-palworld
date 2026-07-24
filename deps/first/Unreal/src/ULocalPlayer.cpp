#include <Unreal/ULocalPlayer.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(ULocalPlayer)

    Function<ULocalPlayer::ExecSignature> ULocalPlayer::ExecInternal;
    std::unordered_map<File::StringType, uint32_t> ULocalPlayer::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_ULocalPlayer.hpp>
}