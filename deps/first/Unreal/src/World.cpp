#include <Unreal/World.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/Transform.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/GameplayStatics.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UWorld)

#include <MemberVariableLayout_SrcWrapper_UWorld.hpp>

    AActor* UWorld::SpawnActor(UClass* InClass, FVector const* Location, FRotator const* Rotation)
    {
        Unreal::FTransform Transform{
                Rotation ? FQuat(*Rotation) : FQuat(),
                Location ? *Location : FVector(),
                {1.0f, 1.0f, 1.0f},
        };
        AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, InClass, Transform);

        if (Actor)
        {
            UGameplayStatics::FinishSpawningActor(Actor, Transform);
        }

        return Actor;
    }

    AActor* UWorld::SpawnActor(UClass* Class, FTransform const* Transform)
    {
        if (!Transform)
        {
            throw std::runtime_error{"UWorld::SpawnActor: 'Transform' cannot be nullptr"};
        }

        AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, Class, *Transform);

        if (Actor)
        {
            UGameplayStatics::FinishSpawningActor(Actor, *Transform);
        }

        return Actor;
    }
}
