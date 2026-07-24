#include <Unreal/AActor.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/UObjectArray.hpp>
#include <Unreal/World.hpp>

#include <Unreal/BPMacros.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(AActor)

    Function<AActor::BeginPlaySignature> AActor::BeginPlayInternal;
    Function<AActor::EndPlaySignature> AActor::EndPlayInternal;
    Function<AActor::TickSignature> AActor::TickInternal;
    std::unordered_map<File::StringType, uint32_t> AActor::VTableLayoutMap;

    auto AActor::GetLevel() -> UObject*
    {
        UObject* Outer = GetOuterPrivate();
        if (!Outer) { return nullptr; }

        if (!HasAnyFlags(Unreal::RF_ClassDefaultObject) && !Outer->HasAnyFlags(Unreal::RF_BeginDestroyed) && !Outer->GetObjectItem()->IsUnreachable())
        {
            while (Outer)
            {
                if (Outer->GetClassPrivate()->GetNamePrivate() == TypeChecker::get_level_name()) { return Outer; }

                Outer = Outer->GetOuterPrivate();
            }
        }

        return nullptr;
    }

    auto AActor::GetWorld() -> UWorld*
    {
        UObject* Outer = GetOuterPrivate();
        if (!Outer) { return nullptr; }

        if (!HasAnyFlags(Unreal::RF_ClassDefaultObject) && !Outer->HasAnyFlags(Unreal::RF_BeginDestroyed) && !Outer->GetObjectItem()->IsUnreachable())
        {
            while (Outer)
            {
                if (Outer->GetClassPrivate()->GetNamePrivate() == TypeChecker::get_world_name()) { return static_cast<UWorld*>(Outer); }

                Outer = Outer->GetOuterPrivate();
            }
        }

        return nullptr;
    }

    auto AActor::K2_DestroyActor() -> void
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_DestroyActor")
        UE_CALL_FUNCTION()
        UE_END_VOID_FUNCTION()
    }

    auto AActor::K2_TeleportTo(FVector DestLocation, FRotator DestRotation) -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_TeleportTo")

        UE_COPY_STRUCT_PROPERTY_BEGIN(DestLocation)
        UE_COPY_VECTOR(DestLocation, DestLocation)

        UE_COPY_STRUCT_PROPERTY_BEGIN(DestRotation)
        UE_COPY_STRUCT_INNER_PROPERTY(DestRotation, Pitch, float, DestRotation.GetPitch())
        UE_COPY_STRUCT_INNER_PROPERTY(DestRotation, Yaw, float, DestRotation.GetYaw())
        UE_COPY_STRUCT_INNER_PROPERTY(DestRotation, Roll, float, DestRotation.GetRoll())

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }

    auto AActor::K2_SetActorLocation(FVector NewLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport) -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_SetActorLocation")

        UE_COPY_STRUCT_PROPERTY_BEGIN(NewLocation)
        UE_COPY_VECTOR(NewLocation, NewLocation)

        UE_COPY_PROPERTY(bSweep, bool)

        UE_COPY_PROPERTY(bTeleport, bool)

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }

    auto AActor::K2_SetActorRotation(FRotator NewRotation, bool bTeleportPhysics) -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_SetActorRotation")
        UE_COPY_STRUCT_PROPERTY_BEGIN(NewRotation)
        UE_COPY_STRUCT_INNER_PROPERTY(NewRotation, Pitch, float, NewRotation.GetPitch())
        UE_COPY_STRUCT_INNER_PROPERTY(NewRotation, Yaw, float, NewRotation.GetYaw())
        UE_COPY_STRUCT_INNER_PROPERTY(NewRotation, Roll, float, NewRotation.GetRoll())

        UE_COPY_PROPERTY(bTeleportPhysics, bool)

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }

    auto AActor::SetActorScale3D(FVector NewScale3D) -> void
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:SetActorScale3D")

        UE_COPY_STRUCT_PROPERTY_BEGIN(NewScale3D)
        UE_COPY_VECTOR(NewScale3D, NewScale3D)

        UE_CALL_FUNCTION()

        UE_END_VOID_FUNCTION()
    }

    bool AActor::K2_SetActorLocationAndRotation(FVector NewLocation, FRotator NewRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport)
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_SetActorLocationAndRotation")

        UE_COPY_STRUCT_PROPERTY_BEGIN(NewLocation)
        UE_COPY_VECTOR(NewLocation, NewLocation)

        UE_COPY_STRUCT_PROPERTY_BEGIN(NewRotation)
        UE_COPY_STRUCT_INNER_PROPERTY(NewRotation, Pitch, float, NewRotation.GetPitch())
        UE_COPY_STRUCT_INNER_PROPERTY(NewRotation, Yaw, float, NewRotation.GetYaw())
        UE_COPY_STRUCT_INNER_PROPERTY(NewRotation, Roll, float, NewRotation.GetRoll())

        UE_COPY_PROPERTY(bSweep, bool)

        UE_COPY_PROPERTY(bTeleport, bool)

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }
    
    auto AActor::SetActorEnableCollision(bool bNewActorEnableCollision) -> void
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:SetActorEnableCollision")

        UE_COPY_PROPERTY(bNewActorEnableCollision, bool)

        UE_CALL_FUNCTION()

        UE_END_VOID_FUNCTION()
    }

    auto AActor::SetActorHiddenInGame(bool bNewHidden) -> void
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:SetActorHiddenInGame")

        UE_COPY_PROPERTY(bNewHidden, bool)

        UE_CALL_FUNCTION()

        UE_END_VOID_FUNCTION()
    }

    auto AActor::SetActorTickEnabled(bool bEnabled) -> void
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:SetActorTickEnabled")

        UE_COPY_PROPERTY(bEnabled, bool)

        UE_CALL_FUNCTION()

        UE_END_VOID_FUNCTION()
    }

    auto AActor::SetActorTickInterval(float TickInterval) -> void
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:SetActorTickInterval")

        UE_COPY_PROPERTY(TickInterval, float)

        UE_CALL_FUNCTION()

        UE_END_VOID_FUNCTION()
    }

    auto AActor::K2_GetActorLocation() -> FVector
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_GetActorLocation")

        UE_CALL_FUNCTION()

        UE_RETURN_VECTOR()
    }

    auto AActor::K2_GetActorRotation() -> FRotator
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_GetActorRotation")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(FRotator)
    }

    auto AActor::GetActorScale3D() -> FVector
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:GetActorScale3D")

        UE_CALL_FUNCTION()

        UE_RETURN_VECTOR()
    }

    auto AActor::GetActorEnableCollision() -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:GetActorEnableCollision")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }

    auto AActor::GetActorTickInterval() -> float
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:GetActorTickInterval")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(float)
    }
    
    auto AActor::GetActorTimeDilation() -> float
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:GetActorTimeDilation")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(float)
    }
    
    auto AActor::IsActorTickEnabled() -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:IsActorTickEnabled")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }

    auto AActor::GetComponentsByClass(UClass* ComponentClass) -> TArray<UObject*>
    {
        if (Version::IsAtLeast(4, 24)) {
          return K2_GetComponentsByClass(ComponentClass);
        }
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:GetComponentsByClass")

        UE_COPY_PROPERTY(ComponentClass, UClass*)

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(TArray<UObject*>)
    }

    auto AActor::K2_GetComponentsByClass(UClass* ComponentClass) -> TArray<UObject*>
    {
        if (Version::IsAtMost(4, 23)) {
          return GetComponentsByClass(ComponentClass);
        }
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:K2_GetComponentsByClass")

        UE_COPY_PROPERTY(ComponentClass, UClass*)

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(TArray<UObject*>)
    }

    auto AActor::GetActorForwardVector() -> FVector
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:GetActorForwardVector")

        UE_CALL_FUNCTION()

        UE_RETURN_VECTOR()
    }

    FTransform AActor::GetTransform()
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.Actor:GetTransform")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(FTransform)
    }
}
