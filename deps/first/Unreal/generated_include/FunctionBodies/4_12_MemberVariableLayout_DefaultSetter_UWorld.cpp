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
    UWorld::MemberOffsets.emplace(STR("StreamingLevelsPrefix"), 0xA0);
}

if (auto it = UWorld::MemberOffsets.find(STR("ViewLocationsRenderedLastFrame")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("ViewLocationsRenderedLastFrame"), 0xD0);
}

if (auto it = UWorld::MemberOffsets.find(STR("bWorldWasLoadedThisTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bWorldWasLoadedThisTick"), 0xE0);
    UWorld::BitfieldInfos.emplace(STR("bWorldWasLoadedThisTick"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bTriggerPostLoadMap")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bTriggerPostLoadMap"), 0xE0);
    UWorld::BitfieldInfos.emplace(STR("bTriggerPostLoadMap"), BitfieldInfo{1, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("AuthorityGameMode")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AuthorityGameMode"), 0xF0);
}

if (auto it = UWorld::MemberOffsets.find(STR("bRequiresHitProxies")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bRequiresHitProxies"), 0x358);
}

if (auto it = UWorld::MemberOffsets.find(STR("bStreamingDataDirty")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bStreamingDataDirty"), 0x4C8);
    UWorld::BitfieldInfos.emplace(STR("bStreamingDataDirty"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("BuildStreamingDataTimer")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("BuildStreamingDataTimer"), 0x4D0);
}

if (auto it = UWorld::MemberOffsets.find(STR("URL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("URL"), 0x6A0);
}

if (auto it = UWorld::MemberOffsets.find(STR("bInTick")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bInTick"), 0x720);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsBuilt")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsBuilt"), 0x721);
}

if (auto it = UWorld::MemberOffsets.find(STR("bTickNewlySpawned")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bTickNewlySpawned"), 0x722);
}

if (auto it = UWorld::MemberOffsets.find(STR("bPostTickComponentUpdate")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPostTickComponentUpdate"), 0x818);
}

if (auto it = UWorld::MemberOffsets.find(STR("PlayerNum")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PlayerNum"), 0x81C);
}

if (auto it = UWorld::MemberOffsets.find(STR("TimeSinceLastPendingKillPurge")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("TimeSinceLastPendingKillPurge"), 0x820);
}

if (auto it = UWorld::MemberOffsets.find(STR("FullPurgeTriggered")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("FullPurgeTriggered"), 0x824);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldDelayGarbageCollect")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldDelayGarbageCollect"), 0x825);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsWorldInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsWorldInitialized"), 0x826);
}

if (auto it = UWorld::MemberOffsets.find(STR("StreamingVolumeUpdateDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("StreamingVolumeUpdateDelay"), 0x828);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsLevelStreamingFrozen")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsLevelStreamingFrozen"), 0x82C);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceUnloadStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceUnloadStreamingLevels"), 0x82D);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldForceVisibleStreamingLevels")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldForceVisibleStreamingLevels"), 0x82E);
}

if (auto it = UWorld::MemberOffsets.find(STR("bDoDelayedUpdateCullDistanceVolumes")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDoDelayedUpdateCullDistanceVolumes"), 0x82F);
}

if (auto it = UWorld::MemberOffsets.find(STR("bHack_Force_UsesGameHiddenFlags_True")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bHack_Force_UsesGameHiddenFlags_True"), 0x831);
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsRunningConstructionScript")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsRunningConstructionScript"), 0x832);
}

if (auto it = UWorld::MemberOffsets.find(STR("bShouldSimulatePhysics")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bShouldSimulatePhysics"), 0x833);
}

if (auto it = UWorld::MemberOffsets.find(STR("bCreateRenderStateForHiddenComponents")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bCreateRenderStateForHiddenComponents"), 0x834);
}

if (auto it = UWorld::MemberOffsets.find(STR("DebugDrawTraceTag")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DebugDrawTraceTag"), 0x838);
}

if (auto it = UWorld::MemberOffsets.find(STR("AudioDeviceHandle")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AudioDeviceHandle"), 0x858);
}

if (auto it = UWorld::MemberOffsets.find(STR("LastTimeUnbuiltLightingWasEncountered")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("LastTimeUnbuiltLightingWasEncountered"), 0x860);
}

if (auto it = UWorld::MemberOffsets.find(STR("TimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("TimeSeconds"), 0x868);
}

if (auto it = UWorld::MemberOffsets.find(STR("RealTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("RealTimeSeconds"), 0x86C);
}

if (auto it = UWorld::MemberOffsets.find(STR("AudioTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AudioTimeSeconds"), 0x870);
}

if (auto it = UWorld::MemberOffsets.find(STR("DeltaTimeSeconds")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("DeltaTimeSeconds"), 0x874);
}

if (auto it = UWorld::MemberOffsets.find(STR("PauseDelay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PauseDelay"), 0x878);
}

if (auto it = UWorld::MemberOffsets.find(STR("bOriginOffsetThisFrame")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bOriginOffsetThisFrame"), 0x894);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextURL")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextURL"), 0x8A8);
}

if (auto it = UWorld::MemberOffsets.find(STR("NextSwitchCountdown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NextSwitchCountdown"), 0x8B8);
}

if (auto it = UWorld::MemberOffsets.find(STR("PreparingLevelNames")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("PreparingLevelNames"), 0x8C0);
}

if (auto it = UWorld::MemberOffsets.find(STR("CommittedPersistentLevelName")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("CommittedPersistentLevelName"), 0x8D0);
}

if (auto it = UWorld::MemberOffsets.find(STR("NumLightingUnbuiltObjects")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("NumLightingUnbuiltObjects"), 0x8D8);
}

if (auto it = UWorld::MemberOffsets.find(STR("bDropDetail")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDropDetail"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bDropDetail"), BitfieldInfo{0, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAggressiveLOD")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAggressiveLOD"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bAggressiveLOD"), BitfieldInfo{1, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsDefaultLevel")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsDefaultLevel"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bIsDefaultLevel"), BitfieldInfo{2, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bRequestedBlockOnAsyncLoading")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bRequestedBlockOnAsyncLoading"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bRequestedBlockOnAsyncLoading"), BitfieldInfo{3, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bActorsInitialized")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bActorsInitialized"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bActorsInitialized"), BitfieldInfo{4, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bBegunPlay")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bBegunPlay"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bBegunPlay"), BitfieldInfo{5, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bMatchStarted")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bMatchStarted"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bMatchStarted"), BitfieldInfo{6, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnly")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnly"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnly"), BitfieldInfo{7, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bPlayersOnlyPending")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bPlayersOnlyPending"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bPlayersOnlyPending"), BitfieldInfo{8, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bStartup")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bStartup"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bStartup"), BitfieldInfo{9, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bIsTearingDown")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bIsTearingDown"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bIsTearingDown"), BitfieldInfo{10, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bKismetScriptError")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bKismetScriptError"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bKismetScriptError"), BitfieldInfo{11, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugPauseExecution")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugPauseExecution"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bDebugPauseExecution"), BitfieldInfo{12, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAllowAudioPlayback")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAllowAudioPlayback"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bAllowAudioPlayback"), BitfieldInfo{13, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bDebugFrameStepExecution")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bDebugFrameStepExecution"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bDebugFrameStepExecution"), BitfieldInfo{14, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("bAreConstraintsDirty")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("bAreConstraintsDirty"), 0x8DC);
    UWorld::BitfieldInfos.emplace(STR("bAreConstraintsDirty"), BitfieldInfo{15, 1, 4});
}

if (auto it = UWorld::MemberOffsets.find(STR("AsyncPreRegisterLevelStreamingTasks")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("AsyncPreRegisterLevelStreamingTasks"), 0x8E0);
}

if (auto it = UWorld::MemberOffsets.find(STR("UEP_TotalSize")); it == UWorld::MemberOffsets.end())
{
    UWorld::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x8F0);
}
