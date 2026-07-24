if (auto it = AActor::MemberOffsets.find(STR("PrimaryActorTick")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("PrimaryActorTick"), 0x28);
}

if (auto it = AActor::MemberOffsets.find(STR("bNetTemporary")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetTemporary"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bNetTemporary"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetStartup")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetStartup"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bNetStartup"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bOnlyRelevantToOwner")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bOnlyRelevantToOwner"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bOnlyRelevantToOwner"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAlwaysRelevant")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAlwaysRelevant"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bAlwaysRelevant"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplicateMovement")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplicateMovement"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bReplicateMovement"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCallPreReplication")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCallPreReplication"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bCallPreReplication"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCallPreReplicationForReplay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCallPreReplicationForReplay"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bCallPreReplicationForReplay"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bHidden")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHidden"), 0x58);
    AActor::BitfieldInfos.emplace(STR("bHidden"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bTearOff")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bTearOff"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bTearOff"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bForceNetAddressable")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bForceNetAddressable"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bForceNetAddressable"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bExchangedRoles")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bExchangedRoles"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bExchangedRoles"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetLoadOnClient")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetLoadOnClient"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bNetLoadOnClient"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetUseOwnerRelevancy")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetUseOwnerRelevancy"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bNetUseOwnerRelevancy"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bRelevantForNetworkReplays")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRelevantForNetworkReplays"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bRelevantForNetworkReplays"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bRelevantForLevelBounds")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRelevantForLevelBounds"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bRelevantForLevelBounds"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplayRewindable")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplayRewindable"), 0x59);
    AActor::BitfieldInfos.emplace(STR("bReplayRewindable"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAllowTickBeforeBeginPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAllowTickBeforeBeginPlay"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bAllowTickBeforeBeginPlay"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAutoDestroyWhenFinished")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAutoDestroyWhenFinished"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bAutoDestroyWhenFinished"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCanBeDamaged")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCanBeDamaged"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bCanBeDamaged"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bBlockInput")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bBlockInput"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bBlockInput"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCollideWhenPlacing")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCollideWhenPlacing"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bCollideWhenPlacing"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bFindCameraComponentWhenViewTarget")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bFindCameraComponentWhenViewTarget"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bFindCameraComponentWhenViewTarget"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bGenerateOverlapEventsDuringLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bGenerateOverlapEventsDuringLevelStreaming"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bGenerateOverlapEventsDuringLevelStreaming"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bIgnoresOriginShifting")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bIgnoresOriginShifting"), 0x5A);
    AActor::BitfieldInfos.emplace(STR("bIgnoresOriginShifting"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bEnableAutoLODGeneration")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bEnableAutoLODGeneration"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bEnableAutoLODGeneration"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bIsEditorOnlyActor")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bIsEditorOnlyActor"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bIsEditorOnlyActor"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorSeamlessTraveled")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorSeamlessTraveled"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bActorSeamlessTraveled"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplicates")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplicates"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bReplicates"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCanBeInCluster")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCanBeInCluster"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bCanBeInCluster"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAllowReceiveTickEventOnDedicatedServer")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAllowReceiveTickEventOnDedicatedServer"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bAllowReceiveTickEventOnDedicatedServer"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetCheckedInitialPhysicsState")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetCheckedInitialPhysicsState"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bNetCheckedInitialPhysicsState"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplicateUsingRegisteredSubObjectList")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplicateUsingRegisteredSubObjectList"), 0x5B);
    AActor::BitfieldInfos.emplace(STR("bReplicateUsingRegisteredSubObjectList"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bHasFinishedSpawning")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHasFinishedSpawning"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bHasFinishedSpawning"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorInitialized")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorInitialized"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bActorInitialized"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorBeginningPlayFromLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorBeginningPlayFromLevelStreaming"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bActorBeginningPlayFromLevelStreaming"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bTickFunctionsRegistered")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bTickFunctionsRegistered"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bTickFunctionsRegistered"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bHasDeferredComponentRegistration")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHasDeferredComponentRegistration"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bHasDeferredComponentRegistration"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bRunningUserConstructionScript")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRunningUserConstructionScript"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bRunningUserConstructionScript"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bHasRegisteredAllComponents")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHasRegisteredAllComponents"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bHasRegisteredAllComponents"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorEnableCollision")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorEnableCollision"), 0x5C);
    AActor::BitfieldInfos.emplace(STR("bActorEnableCollision"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorIsBeingDestroyed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorIsBeingDestroyed"), 0x5D);
    AActor::BitfieldInfos.emplace(STR("bActorIsBeingDestroyed"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorWantsDestroyDuringBeginPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorWantsDestroyDuringBeginPlay"), 0x5D);
    AActor::BitfieldInfos.emplace(STR("bActorWantsDestroyDuringBeginPlay"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("ActorHasBegunPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ActorHasBegunPlay"), 0x5D);
    AActor::BitfieldInfos.emplace(STR("ActorHasBegunPlay"), BitfieldInfo{2, 2, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorIsBeingConstructed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorIsBeingConstructed"), 0x5D);
    AActor::BitfieldInfos.emplace(STR("bActorIsBeingConstructed"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAsyncPhysicsTickEnabled")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAsyncPhysicsTickEnabled"), 0x5D);
    AActor::BitfieldInfos.emplace(STR("bAsyncPhysicsTickEnabled"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("UpdateOverlapsMethodDuringLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("UpdateOverlapsMethodDuringLevelStreaming"), 0x5E);
}

if (auto it = AActor::MemberOffsets.find(STR("DefaultUpdateOverlapsMethodDuringLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("DefaultUpdateOverlapsMethodDuringLevelStreaming"), 0x5F);
}

if (auto it = AActor::MemberOffsets.find(STR("RemoteRole")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("RemoteRole"), 0x60);
}

if (auto it = AActor::MemberOffsets.find(STR("ActorCategory")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ActorCategory"), 0x61);
}

if (auto it = AActor::MemberOffsets.find(STR("InitialLifeSpan")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InitialLifeSpan"), 0x64);
}

if (auto it = AActor::MemberOffsets.find(STR("CustomTimeDilation")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("CustomTimeDilation"), 0x68);
}

if (auto it = AActor::MemberOffsets.find(STR("RayTracingGroupId")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("RayTracingGroupId"), 0x6C);
}

if (auto it = AActor::MemberOffsets.find(STR("AttachmentReplication")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("AttachmentReplication"), 0x70);
}

if (auto it = AActor::MemberOffsets.find(STR("ReplicatedMovement")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ReplicatedMovement"), 0xD0);
}

if (auto it = AActor::MemberOffsets.find(STR("Owner")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Owner"), 0x140);
}

if (auto it = AActor::MemberOffsets.find(STR("NetDriverName")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetDriverName"), 0x148);
}

if (auto it = AActor::MemberOffsets.find(STR("Role")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Role"), 0x150);
}

if (auto it = AActor::MemberOffsets.find(STR("NetDormancy")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetDormancy"), 0x151);
}

if (auto it = AActor::MemberOffsets.find(STR("SpawnCollisionHandlingMethod")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("SpawnCollisionHandlingMethod"), 0x152);
}

if (auto it = AActor::MemberOffsets.find(STR("AutoReceiveInput")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("AutoReceiveInput"), 0x153);
}

if (auto it = AActor::MemberOffsets.find(STR("InputPriority")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InputPriority"), 0x154);
}

if (auto it = AActor::MemberOffsets.find(STR("CreationTime")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("CreationTime"), 0x158);
}

if (auto it = AActor::MemberOffsets.find(STR("InputComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InputComponent"), 0x160);
}

if (auto it = AActor::MemberOffsets.find(STR("NetCullDistanceSquared")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetCullDistanceSquared"), 0x168);
}

if (auto it = AActor::MemberOffsets.find(STR("NetTag")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetTag"), 0x16C);
}

if (auto it = AActor::MemberOffsets.find(STR("NetUpdateFrequency")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetUpdateFrequency"), 0x170);
}

if (auto it = AActor::MemberOffsets.find(STR("MinNetUpdateFrequency")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("MinNetUpdateFrequency"), 0x174);
}

if (auto it = AActor::MemberOffsets.find(STR("NetPriority")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetPriority"), 0x178);
}

if (auto it = AActor::MemberOffsets.find(STR("PhysicsReplicationMode")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("PhysicsReplicationMode"), 0x17C);
}

if (auto it = AActor::MemberOffsets.find(STR("LastRenderTime")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("LastRenderTime"), 0x180);
}

if (auto it = AActor::MemberOffsets.find(STR("Children")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Children"), 0x190);
}

if (auto it = AActor::MemberOffsets.find(STR("RootComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("RootComponent"), 0x1A0);
}

if (auto it = AActor::MemberOffsets.find(STR("TimerHandle_LifeSpanExpired")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("TimerHandle_LifeSpanExpired"), 0x1A8);
}

if (auto it = AActor::MemberOffsets.find(STR("Layers")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Layers"), 0x1B0);
}

if (auto it = AActor::MemberOffsets.find(STR("ParentComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ParentComponent"), 0x1C0);
}

if (auto it = AActor::MemberOffsets.find(STR("Tags")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Tags"), 0x1C8);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakeAnyDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakeAnyDamage"), 0x1D8);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakePointDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakePointDamage"), 0x1D9);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakeRadialDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakeRadialDamage"), 0x1DA);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorBeginOverlap")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorBeginOverlap"), 0x1DB);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorEndOverlap")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorEndOverlap"), 0x1DC);
}

if (auto it = AActor::MemberOffsets.find(STR("OnBeginCursorOver")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnBeginCursorOver"), 0x1DD);
}

if (auto it = AActor::MemberOffsets.find(STR("OnEndCursorOver")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnEndCursorOver"), 0x1DE);
}

if (auto it = AActor::MemberOffsets.find(STR("OnClicked")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnClicked"), 0x1DF);
}

if (auto it = AActor::MemberOffsets.find(STR("OnReleased")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnReleased"), 0x1E0);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchBegin")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchBegin"), 0x1E1);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchEnd")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchEnd"), 0x1E2);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchEnter")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchEnter"), 0x1E3);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchLeave")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchLeave"), 0x1E4);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorHit")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorHit"), 0x1E5);
}

if (auto it = AActor::MemberOffsets.find(STR("OnDestroyed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnDestroyed"), 0x1E6);
}

if (auto it = AActor::MemberOffsets.find(STR("OnEndPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnEndPlay"), 0x1E7);
}

if (auto it = AActor::MemberOffsets.find(STR("ReplicatedSubObjects")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ReplicatedSubObjects"), 0x1E8);
}

if (auto it = AActor::MemberOffsets.find(STR("ReplicatedComponentsInfo")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ReplicatedComponentsInfo"), 0x1F8);
}

if (auto it = AActor::MemberOffsets.find(STR("DetachFence")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("DetachFence"), 0x288);
}

if (auto it = AActor::MemberOffsets.find(STR("UEP_TotalSize")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x290);
}
