#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UKismetSystemLibrary.hpp>
#include <Unreal/BPMacros.hpp>

namespace RC::Unreal
{
    auto UKismetSystemLibrary::VerifySelf() -> bool
    {
        if (!Self)
        {
            Self = UObjectGlobals::StaticFindObject<UKismetSystemLibrary*>(nullptr, nullptr, STR("/Script/Engine.Default__KismetSystemLibrary"));
            if (!Self)
            {
                Output::send(STR("Was unable to locate KismetSystemLibrary\n"));
                return false;
            }
        }

        return true;
    }

    auto UKismetSystemLibrary::GetGameName() -> FString
    {
        if (!VerifySelf()) { return {}; }
        if (!StaticFunctions::GetGameName.IsValid()) { return {}; }

        GetGameName_Params Params{};
        StaticFunctions::GetGameName(Params);
        return Params.ReturnValue;
    }

    auto UKismetSystemLibrary::GetEngineVersion() -> FString
    {
        if (!VerifySelf()) { return {}; }
        if (!StaticFunctions::GetEngineVersion.IsValid()) { return {}; }

        GetEngineVersion_Params Params{};
        StaticFunctions::GetEngineVersion(Params);
        return Params.ReturnValue;
    }

    auto UKismetSystemLibrary::GetBuildConfiguration() -> FString
    {
        if (!VerifySelf()) { return {}; }
        if (!StaticFunctions::GetBuildConfiguration.IsValid()) { return {}; }

        GetBuildConfiguration_Params Params{};
        StaticFunctions::GetBuildConfiguration(Params);
        return Params.ReturnValue;
    }

    TSoftObjectPtr<UObject> UKismetSystemLibrary::Conv_ObjectToSoftObjectReference(UObject* Object)
    {
        if (Version::IsAtLeast(4, 17))
        {
            UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetSystemLibrary:Conv_ObjectToSoftObjectReference");

            UE_SET_STATIC_SELF("/Script/Engine.Default__KismetSystemLibrary")

            UE_COPY_PROPERTY(Object, UObject*)

            UE_CALL_STATIC_FUNCTION()

            UE_RETURN_PROPERTY(TSoftObjectPtr<UObject>)
        }
        else
        {
            throw std::runtime_error{"No equivalent to UKismetSystemLibrary::Conv_ObjectToSoftObjectReference 4.16 and below"};
        }
    }

    TSoftClassPtr<UObject> UKismetSystemLibrary::Conv_ClassToSoftClassReference(UClass* Class)
    {
        if (Version::IsAtLeast(4,17))
        {
            UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetSystemLibrary:Conv_ClassToSoftClassReference")
            UE_SET_STATIC_SELF("/Script/Engine.Default__KismetSystemLibrary")

            UE_COPY_PROPERTY(Class, UClass*)

            UE_CALL_STATIC_FUNCTION()

            UE_RETURN_PROPERTY(TSoftClassPtr<UObject>)
        }
        else
        {
            throw std::runtime_error{"No equivalent to UKismetSystemLibrary::Conv_ClassToSoftClassReference 4.16 and below"};
        }
    }

    UObject* UKismetSystemLibrary::Conv_SoftObjectReferenceToObject(const TSoftObjectPtr<UObject>& SoftObject)
    {
        if (Version::IsAtLeast(4,17))
        {
            UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetSystemLibrary:Conv_SoftObjectReferenceToObject")
            UE_SET_STATIC_SELF("/Script/Engine.Default__KismetSystemLibrary")

            UE_COPY_PROPERTY(SoftObject, TSoftObjectPtr<UObject>)

            UE_CALL_STATIC_FUNCTION()

            UE_RETURN_PROPERTY(UObject*)
        }
        else
        {
            UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetSystemLibrary:Conv_AssetToObject")
            UE_SET_STATIC_SELF("/Script/Engine.Default__KismetSystemLibrary")

            UE_COPY_PROPERTY(SoftObject, TSoftObjectPtr<UObject>)

            UE_CALL_STATIC_FUNCTION()

            UE_RETURN_PROPERTY(UObject*)
        }
    }

    UClass* UKismetSystemLibrary::Conv_SoftClassReferenceToClass(const TSoftClassPtr<UObject>& SoftClass)
    {
        if (Version::IsAtLeast(4,17))
        {
            UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetSystemLibrary:Conv_SoftClassReferenceToClass")
            UE_SET_STATIC_SELF("/Script/Engine.Default__KismetSystemLibrary")

            UE_COPY_PROPERTY(SoftClass, TSoftClassPtr<UObject>)

            UE_CALL_STATIC_FUNCTION()

            UE_RETURN_PROPERTY(UClass*)
        }
        else
        {
            UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetSystemLibrary:Conv_AssetClassToClass")
            UE_SET_STATIC_SELF("/Script/Engine.Default__KismetSystemLibrary")

            UE_COPY_PROPERTY(SoftClass, TSoftClassPtr<UObject>)

            UE_CALL_STATIC_FUNCTION()

            UE_RETURN_PROPERTY(UClass*)
        }
    }
}
