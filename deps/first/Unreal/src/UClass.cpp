#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UClass)
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UBlueprintGeneratedClass)
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UWidgetBlueprintGeneratedClass)
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UAnimBlueprintGeneratedClass)
    
    RC_UE_API std::unordered_map<File::StringType, uint32_t> UClass::VTableLayoutMap{};
    
#include <MemberVariableLayout_SrcWrapper_UClass.hpp>

    int32_t UClass::Offset::class_config_name{};
    
    auto UClass::CreateDefaultObject() -> UObject*
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UClass, CreateDefaultObject, UObject*)
    }

    auto UClass::HasAnyClassFlags(EClassFlags FlagsToCheck) -> bool
    {
        return (GetClassFlags() & FlagsToCheck) != 0;
    }

    auto UClass::HasAllClassFlags(EClassFlags FlagsToCheck) -> bool
    {
        return (GetClassFlags() & FlagsToCheck) == FlagsToCheck;
    }

    bool UClass::HasAnyCastFlag(EClassCastFlags FlagToCheck) const
    {
        return (GetClassCastFlags() & FlagToCheck) != 0;
    }

    bool UClass::HasAllCastFlags(EClassCastFlags FlagsToCheck) const
    {
        return (GetClassCastFlags() & FlagsToCheck) == FlagsToCheck;
    }
}