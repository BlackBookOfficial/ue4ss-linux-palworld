#pragma once

#include <vector>

#include <Unreal/UObject.hpp>
#include <Unreal/Transform.hpp>
#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/AActor.hpp>

namespace RC::Unreal
{
    class RC_UE_API UGameplayStatics : public UObject
    {
    private:
        struct StaticFunctions
        {
            static inline StaticReflectedFunctionBase<UGameplayStatics> BeginDeferredActorSpawnFromClass{STR("/Script/Engine.GameplayStatics:BeginDeferredActorSpawnFromClass")};
            static inline StaticReflectedFunctionBase<UGameplayStatics> FinishSpawningActor{STR("/Script/Engine.GameplayStatics:FinishSpawningActor")};
            static inline StaticReflectedFunctionBase<UGameplayStatics> GetAllActorsOfClass{STR("/Script/Engine.GameplayStatics:GetAllActorsOfClass")};
        };

    public:
        struct BeginDeferredActorSpawnFromClass_Params_As502Plus
        {
            const UObject* WorldContextObject{}; // 0x0
            class UClass* ActorClass{}; // 0x8
            FTransform_As500Plus SpawnTransform{}; // 0x10
            ESpawnActorCollisionHandlingMethod CollisionHandlingOverride{}; // 0x70
            class AActor* Owner{}; // 0x78
            ESpawnActorScaleMethod TransformScaleMethod{}; // 0x80
            class AActor* ReturnValue{}; // 0x88
        };
        struct BeginDeferredActorSpawnFromClass_Params_As500Plus
        {
            const UObject* WorldContextObject{}; // 0x0
            class UClass* ActorClass{}; // 0x8
            FTransform_As500Plus SpawnTransform{}; // 0x10
            ESpawnActorCollisionHandlingMethod CollisionHandlingOverride{}; // 0x70
            class AActor* Owner{}; // 0x78
            class AActor* ReturnValue{}; // 0x80
        };
        struct BeginDeferredActorSpawnFromClass_Params_AsPre500
        {
            const UObject* WorldContextObject{}; // 0x0
            class UClass* ActorClass{}; // 0x8
            FTransform_AsPre500 SpawnTransform{}; // 0x10
            ESpawnActorCollisionHandlingMethod CollisionHandlingOverride{}; // 0x40
            class AActor* Owner{}; // 0x48
            class AActor* ReturnValue{}; // 0x50
        };

        struct FinishSpawningActor_Params
        {
            class AActor* Actor{}; // 0x0
            FTransform SpawnTransform{}; // 0x10
            class AActor* ReturnValue{}; // 0x40
        };

        struct GetAllActorsOfClass_Params
        {
            const UObject* WorldContextObject{};
            const UClass* ActorClass{};
            TArray<AActor*> OutActors{};
        };

    public:
        static inline UGameplayStatics* Self{nullptr};

    private:
        static bool VerifySelf();

    public:
        static class AActor* BeginDeferredActorSpawnFromClass(const UObject* WorldContextObject,
                class UClass* ActorClass,
                const FTransform& SpawnTransform,
                ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined,
                AActor* Owner = nullptr);

        static class AActor* FinishSpawningActor(class AActor* Actor, const FTransform& SpawnTransform);

        static void GetAllActorsOfClass(const UObject* WorldContextObject, class UClass* ActorClass, TArray<AActor*>& OutActors);
        static void GetAllActorsOfClass(const UObject* WorldContextObject, class UClass* ActorClass, std::vector<AActor*>& OutActors);
        static AActor* FindNearestActor(FVector Origin, const std::vector<AActor*>& ActorsToCheck, float& Distance);
    };
}

