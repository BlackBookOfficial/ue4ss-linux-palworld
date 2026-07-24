#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FSetProperty);

#include <MemberVariableLayout_SrcWrapper_FSetProperty.hpp>

    /*
    FSetProperty::FScriptSetLayout FSetProperty::GetSetLayout()
    {
        static_assert(false, "FSetProperty::GetSetLayout not implemented");
    }
    //*/
}
