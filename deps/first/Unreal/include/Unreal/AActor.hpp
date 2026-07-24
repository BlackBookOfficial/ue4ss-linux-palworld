#pragma once

#include <Unreal/UObject.hpp>
#include <Unreal/Transform.hpp>
#include <Unreal/Rotator.hpp>
#include <Unreal/FHitResult.hpp>

namespace RC::Unreal
{
    enum class ESpawnActorScaleMethod : uint8
    {
        OverrideRootScale,
        MultiplyWithRoot,
        SelectDefaultAtRuntime,
    };

    enum class EEndPlayReason
    {
        Destroyed,
        LevelTransition,
        EndPlayInEditor,
        RemovedFromWorld,
        Quit,
    };

    class RC_UE_API AActor : public UObject
    {
    DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(AActor, Engine, CASTCLASS_AActor)

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
        using BeginPlaySignature = void(AActor* Context);
        static Function<BeginPlaySignature> BeginPlayInternal;
        using EndPlaySignature = void(AActor* Context, EEndPlayReason EndPlayReason);
        static Function<EndPlaySignature> EndPlayInternal;
        using TickSignature = void(AActor* Context, float DeltaSeconds);
        static Function<TickSignature> TickInternal;

    public:
        auto GetLevel() -> UObject*;
        auto GetWorld() -> UWorld*;

    public:
        // UFunction interfaces -> START
        auto K2_DestroyActor() -> void;
        auto K2_TeleportTo(FVector DestLocation, FRotator DestRotation) -> bool;
        auto K2_SetActorLocation(FVector NewLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport) -> bool;
        auto K2_SetActorRotation(FRotator NewRotation, bool bTeleportPhysics) -> bool;
        auto K2_SetActorLocationAndRotation(FVector NewLocation, FRotator NewRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport) -> bool;
        auto SetActorScale3D(FVector NewScale3D) -> void;
        auto SetActorEnableCollision(bool bNewActorEnableCollision) -> void;
        auto SetActorHiddenInGame(bool bNewHidden) -> void;
        auto SetActorTickEnabled(bool bEnabled) -> void;
        auto SetActorTickInterval(float TickInterval) -> void;
        auto K2_GetActorLocation() -> FVector;
        auto K2_GetActorRotation() -> FRotator;
        auto GetActorScale3D() -> FVector;
        auto GetActorEnableCollision() -> bool;
        auto GetActorTickInterval() -> float;
        auto GetActorTimeDilation() -> float;
        auto GetComponentsByClass(UClass* ComponentClass) -> TArray<UObject*>; // Should be TArray<UActorComponent*> but we don't have UActorComponent yet.
        auto K2_GetComponentsByClass(UClass* ComponentClass) -> TArray<UObject*>; // Should be TArray<UActorComponent*> but we don't have UActorComponent yet.
        auto GetActorForwardVector() -> FVector;
        FTransform GetTransform();
        auto IsActorTickEnabled() -> bool;
        // UFunction interfaces -> END
    };
}



