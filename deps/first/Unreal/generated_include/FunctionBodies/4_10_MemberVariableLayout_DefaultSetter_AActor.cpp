if (auto it = AActor::MemberOffsets.find(STR("PrimaryActorTick")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("PrimaryActorTick"), 0x28);
}

if (auto it = AActor::MemberOffsets.find(STR("CustomTimeDilation")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("CustomTimeDilation"), 0x78);
}

if (auto it = AActor::MemberOffsets.find(STR("bHidden")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHidden"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bHidden"), BitfieldInfo{0, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetTemporary")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetTemporary"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bNetTemporary"), BitfieldInfo{1, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetStartup")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetStartup"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bNetStartup"), BitfieldInfo{2, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bOnlyRelevantToOwner")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bOnlyRelevantToOwner"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bOnlyRelevantToOwner"), BitfieldInfo{3, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bAlwaysRelevant")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAlwaysRelevant"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bAlwaysRelevant"), BitfieldInfo{4, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplicateMovement")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplicateMovement"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bReplicateMovement"), BitfieldInfo{5, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bTearOff")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bTearOff"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bTearOff"), BitfieldInfo{6, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bExchangedRoles")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bExchangedRoles"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bExchangedRoles"), BitfieldInfo{7, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bPendingNetUpdate")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bPendingNetUpdate"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bPendingNetUpdate"), BitfieldInfo{8, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetLoadOnClient")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetLoadOnClient"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bNetLoadOnClient"), BitfieldInfo{9, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bNetUseOwnerRelevancy")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bNetUseOwnerRelevancy"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bNetUseOwnerRelevancy"), BitfieldInfo{10, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bBlockInput")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bBlockInput"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bBlockInput"), BitfieldInfo{11, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bRunningUserConstructionScript")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRunningUserConstructionScript"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bRunningUserConstructionScript"), BitfieldInfo{12, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bHasFinishedSpawning")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bHasFinishedSpawning"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bHasFinishedSpawning"), BitfieldInfo{13, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorEnableCollision")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorEnableCollision"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bActorEnableCollision"), BitfieldInfo{14, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bReplicates")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bReplicates"), 0x7C);
    AActor::BitfieldInfos.emplace(STR("bReplicates"), BitfieldInfo{15, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("RemoteRole")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("RemoteRole"), 0x80);
}

if (auto it = AActor::MemberOffsets.find(STR("Owner")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Owner"), 0x88);
}

if (auto it = AActor::MemberOffsets.find(STR("ReplicatedMovement")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ReplicatedMovement"), 0x90);
}

if (auto it = AActor::MemberOffsets.find(STR("AttachmentReplication")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("AttachmentReplication"), 0xC8);
}

if (auto it = AActor::MemberOffsets.find(STR("Role")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Role"), 0x108);
}

if (auto it = AActor::MemberOffsets.find(STR("NetDormancy")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetDormancy"), 0x109);
}

if (auto it = AActor::MemberOffsets.find(STR("AutoReceiveInput")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("AutoReceiveInput"), 0x10A);
}

if (auto it = AActor::MemberOffsets.find(STR("InputPriority")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InputPriority"), 0x10C);
}

if (auto it = AActor::MemberOffsets.find(STR("InputComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InputComponent"), 0x110);
}

if (auto it = AActor::MemberOffsets.find(STR("InputConsumeOption_DEPRECATED")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InputConsumeOption_DEPRECATED"), 0x118);
}

if (auto it = AActor::MemberOffsets.find(STR("NetCullDistanceSquared")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetCullDistanceSquared"), 0x11C);
}

if (auto it = AActor::MemberOffsets.find(STR("NetTag")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetTag"), 0x120);
}

if (auto it = AActor::MemberOffsets.find(STR("NetUpdateTime")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetUpdateTime"), 0x124);
}

if (auto it = AActor::MemberOffsets.find(STR("NetUpdateFrequency")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetUpdateFrequency"), 0x128);
}

if (auto it = AActor::MemberOffsets.find(STR("NetPriority")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetPriority"), 0x12C);
}

if (auto it = AActor::MemberOffsets.find(STR("LastNetUpdateTime")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("LastNetUpdateTime"), 0x130);
}

if (auto it = AActor::MemberOffsets.find(STR("NetDriverName")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("NetDriverName"), 0x134);
}

if (auto it = AActor::MemberOffsets.find(STR("bAutoDestroyWhenFinished")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAutoDestroyWhenFinished"), 0x13C);
    AActor::BitfieldInfos.emplace(STR("bAutoDestroyWhenFinished"), BitfieldInfo{0, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bCanBeDamaged")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCanBeDamaged"), 0x13C);
    AActor::BitfieldInfos.emplace(STR("bCanBeDamaged"), BitfieldInfo{1, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorIsBeingDestroyed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorIsBeingDestroyed"), 0x13C);
    AActor::BitfieldInfos.emplace(STR("bActorIsBeingDestroyed"), BitfieldInfo{2, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bCollideWhenPlacing")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bCollideWhenPlacing"), 0x13C);
    AActor::BitfieldInfos.emplace(STR("bCollideWhenPlacing"), BitfieldInfo{3, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bFindCameraComponentWhenViewTarget")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bFindCameraComponentWhenViewTarget"), 0x13C);
    AActor::BitfieldInfos.emplace(STR("bFindCameraComponentWhenViewTarget"), BitfieldInfo{4, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bRelevantForNetworkReplays")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bRelevantForNetworkReplays"), 0x13C);
    AActor::BitfieldInfos.emplace(STR("bRelevantForNetworkReplays"), BitfieldInfo{5, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("SpawnCollisionHandlingMethod")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("SpawnCollisionHandlingMethod"), 0x140);
}

if (auto it = AActor::MemberOffsets.find(STR("CreationTime")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("CreationTime"), 0x144);
}

if (auto it = AActor::MemberOffsets.find(STR("Children")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Children"), 0x150);
}

if (auto it = AActor::MemberOffsets.find(STR("RootComponent")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("RootComponent"), 0x160);
}

if (auto it = AActor::MemberOffsets.find(STR("ControllingMatineeActors")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ControllingMatineeActors"), 0x168);
}

if (auto it = AActor::MemberOffsets.find(STR("InitialLifeSpan")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("InitialLifeSpan"), 0x178);
}

if (auto it = AActor::MemberOffsets.find(STR("TimerHandle_LifeSpanExpired")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("TimerHandle_LifeSpanExpired"), 0x17C);
}

if (auto it = AActor::MemberOffsets.find(STR("bAllowReceiveTickEventOnDedicatedServer")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bAllowReceiveTickEventOnDedicatedServer"), 0x180);
    AActor::BitfieldInfos.emplace(STR("bAllowReceiveTickEventOnDedicatedServer"), BitfieldInfo{0, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("Layers")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Layers"), 0x188);
}

if (auto it = AActor::MemberOffsets.find(STR("ParentComponentActor")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("ParentComponentActor"), 0x198);
}

if (auto it = AActor::MemberOffsets.find(STR("bActorInitialized")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorInitialized"), 0x1A0);
    AActor::BitfieldInfos.emplace(STR("bActorInitialized"), BitfieldInfo{0, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorHasBegunPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorHasBegunPlay"), 0x1A0);
    AActor::BitfieldInfos.emplace(STR("bActorHasBegunPlay"), BitfieldInfo{1, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bActorSeamlessTraveled")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bActorSeamlessTraveled"), 0x1A0);
    AActor::BitfieldInfos.emplace(STR("bActorSeamlessTraveled"), BitfieldInfo{2, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bIgnoresOriginShifting")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bIgnoresOriginShifting"), 0x1A0);
    AActor::BitfieldInfos.emplace(STR("bIgnoresOriginShifting"), BitfieldInfo{3, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("bEnableAutoLODGeneration")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("bEnableAutoLODGeneration"), 0x1A0);
    AActor::BitfieldInfos.emplace(STR("bEnableAutoLODGeneration"), BitfieldInfo{4, 1, 4});
}

if (auto it = AActor::MemberOffsets.find(STR("Tags")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("Tags"), 0x1A8);
}

if (auto it = AActor::MemberOffsets.find(STR("HiddenEditorViews")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("HiddenEditorViews"), 0x1B8);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakeAnyDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakeAnyDamage"), 0x1C0);
}

if (auto it = AActor::MemberOffsets.find(STR("OnTakePointDamage")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnTakePointDamage"), 0x1D0);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorBeginOverlap")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorBeginOverlap"), 0x1E0);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorEndOverlap")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorEndOverlap"), 0x1F0);
}

if (auto it = AActor::MemberOffsets.find(STR("OnBeginCursorOver")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnBeginCursorOver"), 0x200);
}

if (auto it = AActor::MemberOffsets.find(STR("OnEndCursorOver")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnEndCursorOver"), 0x210);
}

if (auto it = AActor::MemberOffsets.find(STR("OnClicked")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnClicked"), 0x220);
}

if (auto it = AActor::MemberOffsets.find(STR("OnReleased")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnReleased"), 0x230);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchBegin")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchBegin"), 0x240);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchEnd")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchEnd"), 0x250);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchEnter")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchEnter"), 0x260);
}

if (auto it = AActor::MemberOffsets.find(STR("OnInputTouchLeave")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnInputTouchLeave"), 0x270);
}

if (auto it = AActor::MemberOffsets.find(STR("OnActorHit")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnActorHit"), 0x280);
}

if (auto it = AActor::MemberOffsets.find(STR("OnDestroyed")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnDestroyed"), 0x290);
}

if (auto it = AActor::MemberOffsets.find(STR("OnEndPlay")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("OnEndPlay"), 0x2A0);
}

if (auto it = AActor::MemberOffsets.find(STR("DetachFence")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("DetachFence"), 0x340);
}

if (auto it = AActor::MemberOffsets.find(STR("UEP_TotalSize")); it == AActor::MemberOffsets.end())
{
    AActor::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x348);
}
