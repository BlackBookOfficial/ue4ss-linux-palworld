#include <Unreal/AGameMode.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(AGameMode)

    std::unordered_map<File::StringType, uint32_t> AGameMode::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_AGameMode.hpp>
}