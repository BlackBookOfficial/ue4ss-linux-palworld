if (auto it = AActor::MemberOffsets.find(STR("PrimaryActorTick")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("PrimaryActorTick"), 0x30);
}

if (auto it = AActor::MemberOffsets.find(STR("bNetTemporary")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetTemporary"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bNetTemporary"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetStartup")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetStartup"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bNetStartup"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bOnlyRelevantToOwner")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bOnlyRelevantToOwner"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bOnlyRelevantToOwner"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAlwaysRelevant")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAlwaysRelevant"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bAlwaysRelevant"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplicateMovement")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplicateMovement"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bReplicateMovement"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bHidden")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHidden"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bHidden"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bTearOff")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bTearOff"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bTearOff"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bForceNetAddressable")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bForceNetAddressable"), 0x60);
    AActor::BitfieldInfos.emplace(STR("bForceNetAddressable"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bExchangedRoles")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bExchangedRoles"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bExchangedRoles"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetLoadOnClient")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetLoadOnClient"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bNetLoadOnClient"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetUseOwnerRelevancy")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetUseOwnerRelevancy"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bNetUseOwnerRelevancy"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bRelevantForNetworkReplays")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRelevantForNetworkReplays"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bRelevantForNetworkReplays"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bRelevantForLevelBounds")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRelevantForLevelBounds"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bRelevantForLevelBounds"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplayRewindable")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplayRewindable"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bReplayRewindable"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAllowTickBeforeBeginPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAllowTickBeforeBeginPlay"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bAllowTickBeforeBeginPlay"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAutoDestroyWhenFinished")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAutoDestroyWhenFinished"), 0x61);
    AActor::BitfieldInfos.emplace(STR("bAutoDestroyWhenFinished"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCanBeDamaged")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCanBeDamaged"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bCanBeDamaged"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bBlockInput")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bBlockInput"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bBlockInput"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCollideWhenPlacing")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCollideWhenPlacing"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bCollideWhenPlacing"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bFindCameraComponentWhenViewTarget")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bFindCameraComponentWhenViewTarget"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bFindCameraComponentWhenViewTarget"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bGenerateOverlapEventsDuringLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bGenerateOverlapEventsDuringLevelStreaming"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bGenerateOverlapEventsDuringLevelStreaming"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bIgnoresOriginShifting")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bIgnoresOriginShifting"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bIgnoresOriginShifting"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bEnableAutoLODGeneration")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bEnableAutoLODGeneration"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bEnableAutoLODGeneration"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bIsEditorOnlyActor")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bIsEditorOnlyActor"), 0x62);
    AActor::BitfieldInfos.emplace(STR("bIsEditorOnlyActor"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorSeamlessTraveled")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorSeamlessTraveled"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bActorSeamlessTraveled"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplicates")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplicates"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bReplicates"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bCanBeInCluster")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCanBeInCluster"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bCanBeInCluster"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bAllowReceiveTickEventOnDedicatedServer")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAllowReceiveTickEventOnDedicatedServer"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bAllowReceiveTickEventOnDedicatedServer"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetCheckedInitialPhysicsState")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetCheckedInitialPhysicsState"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bNetCheckedInitialPhysicsState"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bHasFinishedSpawning")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHasFinishedSpawning"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bHasFinishedSpawning"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorInitialized")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorInitialized"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bActorInitialized"), BitfieldInfo{6, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorBeginningPlayFromLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorBeginningPlayFromLevelStreaming"), 0x63);
    AActor::BitfieldInfos.emplace(STR("bActorBeginningPlayFromLevelStreaming"), BitfieldInfo{7, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bTickFunctionsRegistered")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bTickFunctionsRegistered"), 0x64);
    AActor::BitfieldInfos.emplace(STR("bTickFunctionsRegistered"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bHasDeferredComponentRegistration")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHasDeferredComponentRegistration"), 0x64);
    AActor::BitfieldInfos.emplace(STR("bHasDeferredComponentRegistration"), BitfieldInfo{1, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bRunningUserConstructionScript")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRunningUserConstructionScript"), 0x64);
    AActor::BitfieldInfos.emplace(STR("bRunningUserConstructionScript"), BitfieldInfo{2, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorEnableCollision")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorEnableCollision"), 0x64);
    AActor::BitfieldInfos.emplace(STR("bActorEnableCollision"), BitfieldInfo{3, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorIsBeingDestroyed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorIsBeingDestroyed"), 0x64);
    AActor::BitfieldInfos.emplace(STR("bActorIsBeingDestroyed"), BitfieldInfo{4, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorWantsDestroyDuringBeginPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorWantsDestroyDuringBeginPlay"), 0x64);
    AActor::BitfieldInfos.emplace(STR("bActorWantsDestroyDuringBeginPlay"), BitfieldInfo{5, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("ActorHasBegunPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ActorHasBegunPlay"), 0x64);
    AActor::BitfieldInfos.emplace(STR("ActorHasBegunPlay"), BitfieldInfo{6, 2, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("UpdateOverlapsMethodDuringLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("UpdateOverlapsMethodDuringLevelStreaming"), 0x65);
}

if (auto it = AActor::MemberOffsets.find(STR("DefaultUpdateOverlapsMethodDuringLevelStreaming")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("DefaultUpdateOverlapsMethodDuringLevelStreaming"), 0x66);
}

if (auto it = AActor::MemberOffsets.find(STR("RemoteRole")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("RemoteRole"), 0x67);
}

if (auto it = AActor::MemberOffsets.find(STR("ReplicatedMovement")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ReplicatedMovement"), 0x68);
}

if (auto it = AActor::MemberOffsets.find(STR("InitialLifeSpan")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InitialLifeSpan"), 0x9C);
}

if (auto it = AActor::MemberOffsets.find(STR("CustomTimeDilation")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("CustomTimeDilation"), 0xA0);
}

if (auto it = AActor::MemberOffsets.find(STR("CreationTime")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("CreationTime"), 0xA4);
}

if (auto it = AActor::MemberOffsets.find(STR("AttachmentReplication")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("AttachmentReplication"), 0xA8);
}

if (auto it = AActor::MemberOffsets.find(STR("Owner")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Owner"), 0xE8);
}

if (auto it = AActor::MemberOffsets.find(STR("NetDriverName")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetDriverName"), 0xF0);
}

if (auto it = AActor::MemberOffsets.find(STR("Role")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Role"), 0xFC);
}

if (auto it = AActor::MemberOffsets.find(STR("NetDormancy")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetDormancy"), 0xFD);
}

if (auto it = AActor::MemberOffsets.find(STR("SpawnCollisionHandlingMethod")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("SpawnCollisionHandlingMethod"), 0xFE);
}

if (auto it = AActor::MemberOffsets.find(STR("AutoReceiveInput")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("AutoReceiveInput"), 0xFF);
}

if (auto it = AActor::MemberOffsets.find(STR("InputPriority")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InputPriority"), 0x100);
}

if (auto it = AActor::MemberOffsets.find(STR("InputComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InputComponent"), 0x108);
}

if (auto it = AActor::MemberOffsets.find(STR("NetCullDistanceSquared")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetCullDistanceSquared"), 0x110);
}

if (auto it = AActor::MemberOffsets.find(STR("NetTag")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetTag"), 0x114);
}

if (auto it = AActor::MemberOffsets.find(STR("NetUpdateFrequency")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetUpdateFrequency"), 0x118);
}

if (auto it = AActor::MemberOffsets.find(STR("MinNetUpdateFrequency")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("MinNetUpdateFrequency"), 0x11C);
}

if (auto it = AActor::MemberOffsets.find(STR("NetPriority")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetPriority"), 0x120);
}

if (auto it = AActor::MemberOffsets.find(STR("LastRenderTime")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("LastRenderTime"), 0x124);
}

if (auto it = AActor::MemberOffsets.find(STR("Children")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Children"), 0x130);
}

if (auto it = AActor::MemberOffsets.find(STR("RootComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("RootComponent"), 0x140);
}

if (auto it = AActor::MemberOffsets.find(STR("ControllingMatineeActors")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ControllingMatineeActors"), 0x148);
}

if (auto it = AActor::MemberOffsets.find(STR("TimerHandle_LifeSpanExpired")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("TimerHandle_LifeSpanExpired"), 0x158);
}

if (auto it = AActor::MemberOffsets.find(STR("Layers")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Layers"), 0x160);
}

if (auto it = AActor::MemberOffsets.find(STR("ParentComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ParentComponent"), 0x170);
}

if (auto it = AActor::MemberOffsets.find(STR("bActorIsBeingConstructed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorIsBeingConstructed"), 0x178);
    AActor::BitfieldInfos.emplace(STR("bActorIsBeingConstructed"), BitfieldInfo{0, 1, 1});
}

if (auto it = AActor::MemberOffsets.find(STR("Tags")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Tags"), 0x180);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakeAnyDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakeAnyDamage"), 0x190);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakePointDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakePointDamage"), 0x191);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakeRadialDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakeRadialDamage"), 0x192);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorBeginOverlap")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorBeginOverlap"), 0x193);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorEndOverlap")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorEndOverlap"), 0x194);
}

if (auto it = AActor::MemberOffsets.find(STR("OnBeginCursorOver")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnBeginCursorOver"), 0x195);
}

if (auto it = AActor::MemberOffsets.find(STR("OnEndCursorOver")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnEndCursorOver"), 0x196);
}

if (auto it = AActor::MemberOffsets.find(STR("OnClicked")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnClicked"), 0x197);
}

if (auto it = AActor::MemberOffsets.find(STR("OnReleased")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnReleased"), 0x198);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchBegin")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchBegin"), 0x199);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchEnd")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchEnd"), 0x19A);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchEnter")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchEnter"), 0x19B);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchLeave")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchLeave"), 0x19C);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorHit")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorHit"), 0x19D);
}

if (auto it = AActor::MemberOffsets.find(STR("OnDestroyed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnDestroyed"), 0x19E);
}

if (auto it = AActor::MemberOffsets.find(STR("OnEndPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnEndPlay"), 0x19F);
}

if (auto it = AActor::MemberOffsets.find(STR("DetachFence")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("DetachFence"), 0x220);
}

if (auto it = AActor::MemberOffsets.find(STR("UEP_TotalSize")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x230);
}
