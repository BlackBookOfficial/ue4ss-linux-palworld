#include <Unreal/GameplayStatics.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/BPMacros.hpp>
#include <DynamicOutput/DynamicOutput.hpp>

namespace RC::Unreal
{
    auto UGameplayStatics::VerifySelf() -> bool
    {
        if (!Self)
        {
            Self = UObjectGlobals::StaticFindObject<UGameplayStatics*>(nullptr, nullptr, STR("/Script/Engine.Default__GameplayStatics"));
            if (!Self)
            {
                Output::send(STR("Was unable to locate GameplayStatics\n"));
                return false;
            }
        }

        return true;
    }

    AActor* UGameplayStatics::BeginDeferredActorSpawnFromClass(const UObject* WorldContextObject,
                                                               class UClass* ActorClass,
                                                               const FTransform& SpawnTransform,
                                                               ESpawnActorCollisionHandlingMethod CollisionHandlingOverride,
                                                               AActor* Owner)
    {
        if (!VerifySelf()) { return nullptr; }
        if (!StaticFunctions::BeginDeferredActorSpawnFromClass.IsValid()) { return nullptr; }

        if (Version::IsBelow(5, 0))
        {
            BeginDeferredActorSpawnFromClass_Params_AsPre500 Params{
                    .WorldContextObject = WorldContextObject,
                    .ActorClass = ActorClass,
                    .SpawnTransform = {},
                    .CollisionHandlingOverride = CollisionHandlingOverride,
                    .Owner = Owner,
            };
            Params.SpawnTransform = SpawnTransform;

            StaticFunctions::BeginDeferredActorSpawnFromClass(Params);
            return Params.ReturnValue;
        }
        else if (Version::IsBelow(5, 2))
        {
            BeginDeferredActorSpawnFromClass_Params_As500Plus Params{
                    .WorldContextObject = WorldContextObject,
                    .ActorClass = ActorClass,
                    .SpawnTransform = {},
                    .CollisionHandlingOverride = CollisionHandlingOverride,
                    .Owner = Owner,
            };
            Params.SpawnTransform = SpawnTransform;

            StaticFunctions::BeginDeferredActorSpawnFromClass(Params);
            return Params.ReturnValue;
        }
        else
        {
            BeginDeferredActorSpawnFromClass_Params_As502Plus Params{
                .WorldContextObject = WorldContextObject,
                .ActorClass = ActorClass,
                .SpawnTransform = {},
                .CollisionHandlingOverride = CollisionHandlingOverride,
                .Owner = Owner,
                .TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot,
            };
            Params.SpawnTransform = SpawnTransform;

            StaticFunctions::BeginDeferredActorSpawnFromClass(Params);
            return Params.ReturnValue;
        }
    }

    AActor* UGameplayStatics::FinishSpawningActor(AActor* Actor, const FTransform& SpawnTransform)
    {
        if (!VerifySelf()) { return nullptr; }
        if (!StaticFunctions::FinishSpawningActor.IsValid()) { return nullptr; }

        FinishSpawningActor_Params Params{
                .Actor = Actor,
                .SpawnTransform = SpawnTransform,
        };
        StaticFunctions::FinishSpawningActor(Params);
        return Params.ReturnValue;
    }

   void UGameplayStatics::GetAllActorsOfClass(const UObject* WorldContextObject, class UClass* ActorClass, TArray<AActor*>& OutActors)
    {
        if (!VerifySelf()) { return; }
        if (!StaticFunctions::GetAllActorsOfClass.IsValid()) { return; }

        GetAllActorsOfClass_Params Params{
            .WorldContextObject = WorldContextObject,
            .ActorClass = ActorClass
        };
        StaticFunctions::GetAllActorsOfClass(Params);

        for (AActor* Elem : Params.OutActors)
        {
            OutActors.Add(Elem);
        }
    }

   void UGameplayStatics::GetAllActorsOfClass(const UObject* WorldContextObject, class UClass* ActorClass, std::vector<AActor*>& OutActors)
    {
        if (!VerifySelf()) { return; }
        if (!StaticFunctions::GetAllActorsOfClass.IsValid()) { return; }

        GetAllActorsOfClass_Params Params{
            .WorldContextObject = WorldContextObject,
            .ActorClass = ActorClass
        };
        StaticFunctions::GetAllActorsOfClass(Params);

        for (AActor* Elem : Params.OutActors)
        {
            OutActors.emplace_back(Elem);
        }
    }

    AActor* UGameplayStatics::FindNearestActor(FVector Origin, const std::vector<AActor*>& ActorsToCheck, float& Distance)
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.GameplayStatics:FindNearestActor")
        UE_SET_STATIC_SELF("/Script/Engine.Default__GameplayStatics")

        UE_COPY_STRUCT_PROPERTY_BEGIN(Origin)
        UE_COPY_VECTOR(Origin, Origin)

        UE_COPY_STL_VECTOR_AS_TARRAY(ActorsToCheck, AActor*, ActorsToCheck)

        UE_COPY_PROPERTY(Distance, float)

        UE_CALL_STATIC_FUNCTION()

        UE_COPY_OUT_PROPERTY(Distance, float)

        UE_RETURN_PROPERTY(AActor*)
    }
}
