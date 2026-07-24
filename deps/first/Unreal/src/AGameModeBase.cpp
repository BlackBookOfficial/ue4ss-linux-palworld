#include <Unreal/AGameModeBase.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(AGameModeBase)

    Function<AGameModeBase::InitGameStateSignature> AGameModeBase::InitGameStateInternal;
    std::unordered_map<File::StringType, uint32_t> AGameModeBase::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_AGameModeBase.hpp>
}