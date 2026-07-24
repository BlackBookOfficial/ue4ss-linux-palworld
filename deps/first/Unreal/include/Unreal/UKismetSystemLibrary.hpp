#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/SoftObjectPtr.hpp>

namespace RC::Unreal
{

    class RC_UE_API UKismetSystemLibrary : public UObject
    {
    public:
        using StaticReflectedFunction = StaticReflectedFunctionBase<UKismetSystemLibrary>;

        static inline UKismetSystemLibrary* Self{nullptr};
        struct StaticFunctions
        {
            static inline StaticReflectedFunction GetGameName{STR("/Script/Engine.KismetSystemLibrary:GetGameName")};
            static inline StaticReflectedFunction GetEngineVersion{STR("/Script/Engine.KismetSystemLibrary:GetEngineVersion")};
            static inline StaticReflectedFunction GetBuildConfiguration{STR("/Script/Engine.KismetSystemLibrary:GetBuildConfiguration")};
        };

    public:
        struct GetGameName_Params
        {
        public:
            FString ReturnValue; // 0x0
        };

        struct GetEngineVersion_Params
        {
        public:
            FString ReturnValue; // 0x0
        };

        struct GetBuildConfiguration_Params
        {
        public:
            FString ReturnValue; // 0x0
        };

    private:
        auto static VerifySelf() -> bool;

    public:
        auto static GetGameName() -> FString;
        auto static GetEngineVersion() -> FString;
        auto static GetBuildConfiguration() -> FString;
        static TSoftObjectPtr<UObject> Conv_ObjectToSoftObjectReference(UObject* Object);
        static TSoftClassPtr<UObject> Conv_ClassToSoftClassReference(UClass* Class);
        static UObject* Conv_SoftObjectReferenceToObject(const TSoftObjectPtr<UObject>& SoftObject);
        static UClass* Conv_SoftClassReferenceToClass(const TSoftClassPtr<UObject>& SoftClass);
    };
}


