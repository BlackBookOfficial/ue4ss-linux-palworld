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
    UWorld::MemberOffsets.emplace(STR("bStreamingDataDirty"), 0x4F0);
    UWorld::BitfieldInfos.emplace(STR("bStreamingDataDirty"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("BuildStreamingDataTimer")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("BuildStreamingDataTimer"), 0x4F8);
}

if (auto it = UWorld::MemberOffsets.find(STR("URL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("URL"), 0x560);
}

if (auto it = UWorld::MemberOffsets.find(STR("bInTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bInTick"), 0x5E0);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsBuilt")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsBuilt"), 0x5E1);
}

if (auto it = UWorld::MemberOffsets.find(STR("bTickNewlySpawned")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bTickNewlySpawned"), 0x5E2);
}

if (auto it = UWorld::MemberOffsets.find(STR("bPostTickComponentUpdate")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPostTickComponentUpdate"), 0x6F0);
}

if (auto it = UWorld::MemberOffsets.find(STR("PlayerNum")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PlayerNum"), 0x6F4);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsWorldInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsWorldInitialized"), 0x6F8);
}

if (auto it = UWorld::MemberOffsets.find(STR("StreamingVolumeUpdateDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("StreamingVolumeUpdateDelay"), 0x6FC);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsLevelStreamingFrozen")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsLevelStreamingFrozen"), 0x700);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceUnloadStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceUnloadStreamingLevels"), 0x701);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceVisibleStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceVisibleStreamingLevels"), 0x702);
}

if (auto it = UWorld::MemberOffsets.find(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"), 0x703);
    UWorld::BitfieldInfos.emplace(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"), BitfieldInfo{0, 1, 1});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDoDelayedUpdateCullDistanceVolumes")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDoDelayedUpdateCullDistanceVolumes"), 0x704);
}

if (auto it = UWorld::MemberOffsets.find(STR("bHack_Force_UsesGameHiddenFlags_True")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bHack_Force_UsesGameHiddenFlags_True"), 0x70C);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsRunningConstructionScript")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsRunningConstructionScript"), 0x70D);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldSimulatePhysics")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldSimulatePhysics"), 0x70E);
}

if (auto it = UWorld::MemberOffsets.find(STR("DebugDrawTraceTag")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DebugDrawTraceTag"), 0x710);
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugDrawAllTraceTags")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugDrawAllTraceTags"), 0x718);
}

if (auto it = UWorld::MemberOffsets.find(STR("AudioDeviceHandle")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AudioDeviceHandle"), 0x780);
}

if (auto it = UWorld::MemberOffsets.find(STR("LastTimeUnbuiltLightingWasEncountered")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("LastTimeUnbuiltLightingWasEncountered"), 0x788);
}

if (auto it = UWorld::MemberOffsets.find(STR("TimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("TimeSeconds"), 0x790);
}

if (auto it = UWorld::MemberOffsets.find(STR("UnpausedTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("UnpausedTimeSeconds"), 0x794);
}

if (auto it = UWorld::MemberOffsets.find(STR("RealTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("RealTimeSeconds"), 0x798);
}

if (auto it = UWorld::MemberOffsets.find(STR("AudioTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AudioTimeSeconds"), 0x79C);
}

if (auto it = UWorld::MemberOffsets.find(STR("DeltaTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DeltaTimeSeconds"), 0x7A0);
}

if (auto it = UWorld::MemberOffsets.find(STR("PauseDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PauseDelay"), 0x7A4);
}

if (auto it = UWorld::MemberOffsets.find(STR("OriginOffsetThisFrame")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("OriginOffsetThisFrame"), 0x7C0);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextURL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextURL"), 0x7E0);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextSwitchCountdown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextSwitchCountdown"), 0x7F0);
}

if (auto it = UWorld::MemberOffsets.find(STR("PreparingLevelNames")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PreparingLevelNames"), 0x7F8);
}

if (auto it = UWorld::MemberOffsets.find(STR("CommittedPersistentLevelName")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("CommittedPersistentLevelName"), 0x808);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumLightingUnbuiltObjects")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumLightingUnbuiltObjects"), 0x810);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumUnbuiltReflectionCaptures")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumUnbuiltReflectionCaptures"), 0x814);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumTextureStreamingUnbuiltComponents")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumTextureStreamingUnbuiltComponents"), 0x818);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumTextureStreamingDirtyResources")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumTextureStreamingDirtyResources"), 0x81C);
}

if (auto it = UWorld::MemberOffsets.find(STR("bDropDetail")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDropDetail"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bDropDetail"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAggressiveLOD")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAggressiveLOD"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bAggressiveLOD"), BitfieldInfo{1, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsDefaultLevel")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsDefaultLevel"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bIsDefaultLevel"), BitfieldInfo{2, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bRequestedBlockOnAsyncLoading")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bRequestedBlockOnAsyncLoading"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bRequestedBlockOnAsyncLoading"), BitfieldInfo{3, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bActorsInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bActorsInitialized"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bActorsInitialized"), BitfieldInfo{4, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bBegunPlay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bBegunPlay"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bBegunPlay"), BitfieldInfo{5, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bMatchStarted")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMatchStarted"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bMatchStarted"), BitfieldInfo{6, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnly")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnly"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnly"), BitfieldInfo{7, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnlyPending")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnlyPending"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnlyPending"), BitfieldInfo{8, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bStartup")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bStartup"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bStartup"), BitfieldInfo{9, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsTearingDown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsTearingDown"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bIsTearingDown"), BitfieldInfo{10, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bKismetScriptError")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bKismetScriptError"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bKismetScriptError"), BitfieldInfo{11, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugPauseExecution")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugPauseExecution"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bDebugPauseExecution"), BitfieldInfo{12, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsCameraMoveableWhenPaused")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsCameraMoveableWhenPaused"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bIsCameraMoveableWhenPaused"), BitfieldInfo{13, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAllowAudioPlayback")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAllowAudioPlayback"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bAllowAudioPlayback"), BitfieldInfo{14, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugFrameStepExecution")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugFrameStepExecution"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bDebugFrameStepExecution"), BitfieldInfo{15, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAreConstraintsDirty")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAreConstraintsDirty"), 0x820);
    UWorld::BitfieldInfos.emplace(STR("bAreConstraintsDirty"), BitfieldInfo{16, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("UEP_TotalSize")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x8A0);
}
