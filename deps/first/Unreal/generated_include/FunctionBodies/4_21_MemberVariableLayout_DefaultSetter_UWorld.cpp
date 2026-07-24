if (auto it = UWorld::MemberOffsets.find(STR("ExtraReferencedObjects")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("ExtraReferencedObjects"), 0x68);
}

if (auto it = UWorld::MemberOffsets.find(STR("PerModuleDataObjects")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PerModuleDataObjects"), 0x78);
}

if (auto it = UWorld::MemberOffsets.find(STR("StreamingLevelsPrefix")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("StreamingLevelsPrefix"), 0xE8);
}

if (auto it = UWorld::MemberOffsets.find(STR("ViewLocationsRenderedLastFrame")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("ViewLocationsRenderedLastFrame"), 0x120);
}

if (auto it = UWorld::MemberOffsets.find(STR("bWorldWasLoadedThisTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bWorldWasLoadedThisTick"), 0x130);
    UWorld::BitfieldInfos.emplace(STR("bWorldWasLoadedThisTick"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bTriggerPostLoadMap")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bTriggerPostLoadMap"), 0x130);
    UWorld::BitfieldInfos.emplace(STR("bTriggerPostLoadMap"), BitfieldInfo{1, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("AuthorityGameMode")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AuthorityGameMode"), 0x140);
}

if (auto it = UWorld::MemberOffsets.find(STR("ActiveLevelCollectionIndex")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("ActiveLevelCollectionIndex"), 0x180);
}

if (auto it = UWorld::MemberOffsets.find(STR("bRequiresHitProxies")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bRequiresHitProxies"), 0x3D8);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldTick"), 0x3D9);
}

if (auto it = UWorld::MemberOffsets.find(STR("bStreamingDataDirty")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bStreamingDataDirty"), 0x4A0);
    UWorld::BitfieldInfos.emplace(STR("bStreamingDataDirty"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("BuildStreamingDataTimer")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("BuildStreamingDataTimer"), 0x4A8);
}

if (auto it = UWorld::MemberOffsets.find(STR("URL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("URL"), 0x528);
}

if (auto it = UWorld::MemberOffsets.find(STR("bInTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bInTick"), 0x5A8);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsBuilt")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsBuilt"), 0x5A9);
}

if (auto it = UWorld::MemberOffsets.find(STR("bTickNewlySpawned")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bTickNewlySpawned"), 0x5AA);
}

if (auto it = UWorld::MemberOffsets.find(STR("bPostTickComponentUpdate")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPostTickComponentUpdate"), 0x6B8);
}

if (auto it = UWorld::MemberOffsets.find(STR("PlayerNum")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PlayerNum"), 0x6BC);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsWorldInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsWorldInitialized"), 0x6C0);
}

if (auto it = UWorld::MemberOffsets.find(STR("StreamingVolumeUpdateDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("StreamingVolumeUpdateDelay"), 0x6C4);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsLevelStreamingFrozen")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsLevelStreamingFrozen"), 0x6C8);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceUnloadStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceUnloadStreamingLevels"), 0x6C9);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceVisibleStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceVisibleStreamingLevels"), 0x6CA);
}

if (auto it = UWorld::MemberOffsets.find(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"), 0x6CB);
    UWorld::BitfieldInfos.emplace(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"), BitfieldInfo{0, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDoDelayedUpdateCullDistanceVolumes")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDoDelayedUpdateCullDistanceVolumes"), 0x6CC);
}

if (auto it = UWorld::MemberOffsets.find(STR("bHack_Force_UsesGameHiddenFlags_True")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bHack_Force_UsesGameHiddenFlags_True"), 0x6D4);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsRunningConstructionScript")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsRunningConstructionScript"), 0x6D5);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldSimulatePhysics")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldSimulatePhysics"), 0x6D6);
}

if (auto it = UWorld::MemberOffsets.find(STR("DebugDrawTraceTag")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DebugDrawTraceTag"), 0x6D8);
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugDrawAllTraceTags")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugDrawAllTraceTags"), 0x6E0);
}

if (auto it = UWorld::MemberOffsets.find(STR("AudioDeviceHandle")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AudioDeviceHandle"), 0x748);
}

if (auto it = UWorld::MemberOffsets.find(STR("LastTimeUnbuiltLightingWasEncountered")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("LastTimeUnbuiltLightingWasEncountered"), 0x750);
}

if (auto it = UWorld::MemberOffsets.find(STR("TimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("TimeSeconds"), 0x758);
}

if (auto it = UWorld::MemberOffsets.find(STR("UnpausedTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("UnpausedTimeSeconds"), 0x75C);
}

if (auto it = UWorld::MemberOffsets.find(STR("RealTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("RealTimeSeconds"), 0x760);
}

if (auto it = UWorld::MemberOffsets.find(STR("AudioTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AudioTimeSeconds"), 0x764);
}

if (auto it = UWorld::MemberOffsets.find(STR("DeltaTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DeltaTimeSeconds"), 0x768);
}

if (auto it = UWorld::MemberOffsets.find(STR("PauseDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PauseDelay"), 0x76C);
}

if (auto it = UWorld::MemberOffsets.find(STR("OriginOffsetThisFrame")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("OriginOffsetThisFrame"), 0x788);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextURL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextURL"), 0x7A8);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextSwitchCountdown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextSwitchCountdown"), 0x7B8);
}

if (auto it = UWorld::MemberOffsets.find(STR("PreparingLevelNames")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PreparingLevelNames"), 0x7C0);
}

if (auto it = UWorld::MemberOffsets.find(STR("CommittedPersistentLevelName")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("CommittedPersistentLevelName"), 0x7D0);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumLightingUnbuiltObjects")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumLightingUnbuiltObjects"), 0x7D8);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumUnbuiltReflectionCaptures")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumUnbuiltReflectionCaptures"), 0x7DC);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumTextureStreamingUnbuiltComponents")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumTextureStreamingUnbuiltComponents"), 0x7E0);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumTextureStreamingDirtyResources")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumTextureStreamingDirtyResources"), 0x7E4);
}

if (auto it = UWorld::MemberOffsets.find(STR("bDropDetail")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDropDetail"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bDropDetail"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAggressiveLOD")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAggressiveLOD"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bAggressiveLOD"), BitfieldInfo{1, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsDefaultLevel")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsDefaultLevel"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bIsDefaultLevel"), BitfieldInfo{2, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bRequestedBlockOnAsyncLoading")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bRequestedBlockOnAsyncLoading"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bRequestedBlockOnAsyncLoading"), BitfieldInfo{3, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bActorsInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bActorsInitialized"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bActorsInitialized"), BitfieldInfo{4, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bBegunPlay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bBegunPlay"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bBegunPlay"), BitfieldInfo{5, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bMatchStarted")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMatchStarted"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bMatchStarted"), BitfieldInfo{6, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnly")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnly"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnly"), BitfieldInfo{7, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnlyPending")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnlyPending"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnlyPending"), BitfieldInfo{8, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bStartup")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bStartup"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bStartup"), BitfieldInfo{9, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsTearingDown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsTearingDown"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bIsTearingDown"), BitfieldInfo{10, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bKismetScriptError")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bKismetScriptError"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bKismetScriptError"), BitfieldInfo{11, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugPauseExecution")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugPauseExecution"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bDebugPauseExecution"), BitfieldInfo{12, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsCameraMoveableWhenPaused")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsCameraMoveableWhenPaused"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bIsCameraMoveableWhenPaused"), BitfieldInfo{13, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAllowAudioPlayback")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAllowAudioPlayback"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bAllowAudioPlayback"), BitfieldInfo{14, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugFrameStepExecution")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugFrameStepExecution"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bDebugFrameStepExecution"), BitfieldInfo{15, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAreConstraintsDirty")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAreConstraintsDirty"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bAreConstraintsDirty"), BitfieldInfo{16, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bCleanedUpWorld")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bCleanedUpWorld"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bCleanedUpWorld"), BitfieldInfo{17, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bMarkedObjectsPendingKill")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMarkedObjectsPendingKill"), 0x7E8);
    UWorld::BitfieldInfos.emplace(STR("bMarkedObjectsPendingKill"), BitfieldInfo{18, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("UEP_TotalSize")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x868);
}
