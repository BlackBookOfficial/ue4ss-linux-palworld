if (auto it = UWorld::MemberOffsets.find(STR("ExtraReferencedObjects")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("ExtraReferencedObjects"), 0x70);
}

if (auto it = UWorld::MemberOffsets.find(STR("PerModuleDataObjects")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PerModuleDataObjects"), 0x80);
}

if (auto it = UWorld::MemberOffsets.find(STR("StreamingLevelsPrefix")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("StreamingLevelsPrefix"), 0xD0);
}

if (auto it = UWorld::MemberOffsets.find(STR("bSupportsMakingVisibleTransactionRequests")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bSupportsMakingVisibleTransactionRequests"), 0x110);
}

if (auto it = UWorld::MemberOffsets.find(STR("bSupportsMakingInvisibleTransactionRequests")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bSupportsMakingInvisibleTransactionRequests"), 0x112);
}

if (auto it = UWorld::MemberOffsets.find(STR("PendingVisibilityLock")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PendingVisibilityLock"), 0x118);
}

if (auto it = UWorld::MemberOffsets.find(STR("bAllowDeferredPhysicsStateCreation")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAllowDeferredPhysicsStateCreation"), 0x158);
}

if (auto it = UWorld::MemberOffsets.find(STR("LastRenderTime")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("LastRenderTime"), 0x180);
}

if (auto it = UWorld::MemberOffsets.find(STR("bWorldWasLoadedThisTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bWorldWasLoadedThisTick"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bWorldWasLoadedThisTick"), BitfieldInfo{0, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bTriggerPostLoadMap")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bTriggerPostLoadMap"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bTriggerPostLoadMap"), BitfieldInfo{1, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bInTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bInTick"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bInTick"), BitfieldInfo{2, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsBuilt")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsBuilt"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bIsBuilt"), BitfieldInfo{3, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bTickNewlySpawned")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bTickNewlySpawned"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bTickNewlySpawned"), BitfieldInfo{4, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPostTickComponentUpdate")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPostTickComponentUpdate"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bPostTickComponentUpdate"), BitfieldInfo{5, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsWorldInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsWorldInitialized"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bIsWorldInitialized"), BitfieldInfo{6, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsLevelStreamingFrozen")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsLevelStreamingFrozen"), 0x18B);
    UWorld::BitfieldInfos.emplace(STR("bIsLevelStreamingFrozen"), BitfieldInfo{7, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDoDelayedUpdateCullDistanceVolumes")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDoDelayedUpdateCullDistanceVolumes"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bDoDelayedUpdateCullDistanceVolumes"), BitfieldInfo{0, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsRunningConstructionScript")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsRunningConstructionScript"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bIsRunningConstructionScript"), BitfieldInfo{1, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldSimulatePhysics")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldSimulatePhysics"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bShouldSimulatePhysics"), BitfieldInfo{2, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDropDetail")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDropDetail"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bDropDetail"), BitfieldInfo{3, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAggressiveLOD")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAggressiveLOD"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bAggressiveLOD"), BitfieldInfo{4, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsDefaultLevel")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsDefaultLevel"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bIsDefaultLevel"), BitfieldInfo{5, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bRequestedBlockOnAsyncLoading")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bRequestedBlockOnAsyncLoading"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bRequestedBlockOnAsyncLoading"), BitfieldInfo{6, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bActorsInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bActorsInitialized"), 0x18C);
    UWorld::BitfieldInfos.emplace(STR("bActorsInitialized"), BitfieldInfo{7, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bBegunPlay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bBegunPlay"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bBegunPlay"), BitfieldInfo{0, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bMatchStarted")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMatchStarted"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bMatchStarted"), BitfieldInfo{1, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnly")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnly"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnly"), BitfieldInfo{2, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnlyPending")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnlyPending"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnlyPending"), BitfieldInfo{3, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bStartup")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bStartup"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bStartup"), BitfieldInfo{4, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsTearingDown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsTearingDown"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bIsTearingDown"), BitfieldInfo{5, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bKismetScriptError")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bKismetScriptError"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bKismetScriptError"), BitfieldInfo{6, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugPauseExecution")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugPauseExecution"), 0x18D);
    UWorld::BitfieldInfos.emplace(STR("bDebugPauseExecution"), BitfieldInfo{7, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsCameraMoveableWhenPaused")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsCameraMoveableWhenPaused"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bIsCameraMoveableWhenPaused"), BitfieldInfo{0, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAllowAudioPlayback")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAllowAudioPlayback"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bAllowAudioPlayback"), BitfieldInfo{1, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAreConstraintsDirty")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAreConstraintsDirty"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bAreConstraintsDirty"), BitfieldInfo{2, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bRequiresHitProxies")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bRequiresHitProxies"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bRequiresHitProxies"), BitfieldInfo{3, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldTick"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bShouldTick"), BitfieldInfo{4, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bStreamingDataDirty")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bStreamingDataDirty"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bStreamingDataDirty"), BitfieldInfo{5, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceUnloadStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceUnloadStreamingLevels"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bShouldForceUnloadStreamingLevels"), BitfieldInfo{6, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceVisibleStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceVisibleStreamingLevels"), 0x18E);
    UWorld::BitfieldInfos.emplace(STR("bShouldForceVisibleStreamingLevels"), BitfieldInfo{7, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"), 0x18F);
    UWorld::BitfieldInfos.emplace(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"), BitfieldInfo{0, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bHasEverBeenInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bHasEverBeenInitialized"), 0x18F);
    UWorld::BitfieldInfos.emplace(STR("bHasEverBeenInitialized"), BitfieldInfo{1, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsBeingCleanedUp")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsBeingCleanedUp"), 0x190);
}

if (auto it = UWorld::MemberOffsets.find(STR("IsInBlockTillLevelStreamingCompleted")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("IsInBlockTillLevelStreamingCompleted"), 0x194);
}

if (auto it = UWorld::MemberOffsets.find(STR("BlockTillLevelStreamingCompletedEpoch")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("BlockTillLevelStreamingCompletedEpoch"), 0x198);
}

if (auto it = UWorld::MemberOffsets.find(STR("AuthorityGameMode")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AuthorityGameMode"), 0x1A8);
}

if (auto it = UWorld::MemberOffsets.find(STR("ActiveLevelCollectionIndex")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("ActiveLevelCollectionIndex"), 0x1E8);
}

if (auto it = UWorld::MemberOffsets.find(STR("BuildStreamingDataTimer")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("BuildStreamingDataTimer"), 0x5F0);
}

if (auto it = UWorld::MemberOffsets.find(STR("URL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("URL"), 0x718);
}

if (auto it = UWorld::MemberOffsets.find(STR("PlayerNum")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PlayerNum"), 0x7E8);
}

if (auto it = UWorld::MemberOffsets.find(STR("StreamingVolumeUpdateDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("StreamingVolumeUpdateDelay"), 0x7EC);
}

if (auto it = UWorld::MemberOffsets.find(STR("PostProcessVolumeCachedSizes")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PostProcessVolumeCachedSizes"), 0x818);
}

if (auto it = UWorld::MemberOffsets.find(STR("LastTimeUnbuiltLightingWasEncountered")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("LastTimeUnbuiltLightingWasEncountered"), 0x838);
}

if (auto it = UWorld::MemberOffsets.find(STR("TimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("TimeSeconds"), 0x840);
}

if (auto it = UWorld::MemberOffsets.find(STR("UnpausedTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("UnpausedTimeSeconds"), 0x848);
}

if (auto it = UWorld::MemberOffsets.find(STR("RealTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("RealTimeSeconds"), 0x850);
}

if (auto it = UWorld::MemberOffsets.find(STR("AudioTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AudioTimeSeconds"), 0x858);
}

if (auto it = UWorld::MemberOffsets.find(STR("DeltaRealTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DeltaRealTimeSeconds"), 0x860);
}

if (auto it = UWorld::MemberOffsets.find(STR("DeltaTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DeltaTimeSeconds"), 0x864);
}

if (auto it = UWorld::MemberOffsets.find(STR("PauseDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PauseDelay"), 0x868);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextSwitchCountdown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextSwitchCountdown"), 0x8A0);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumStreamingLevelsBeingLoaded")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumStreamingLevelsBeingLoaded"), 0x8BA);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextURL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextURL"), 0x8C0);
}

if (auto it = UWorld::MemberOffsets.find(STR("PreparingLevelNames")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PreparingLevelNames"), 0x8D0);
}

if (auto it = UWorld::MemberOffsets.find(STR("CommittedPersistentLevelName")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("CommittedPersistentLevelName"), 0x8E0);
}

if (auto it = UWorld::MemberOffsets.find(STR("bMarkedObjectsPendingKill")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMarkedObjectsPendingKill"), 0x8E8);
    UWorld::BitfieldInfos.emplace(STR("bMarkedObjectsPendingKill"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("CleanupWorldTag")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("CleanupWorldTag"), 0x8EC);
}

if (auto it = UWorld::MemberOffsets.find(STR("UEP_TotalSize")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xA98);
}
