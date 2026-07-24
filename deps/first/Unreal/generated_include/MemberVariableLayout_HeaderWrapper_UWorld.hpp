static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& GetExtraReferencedObjects();
    const TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& GetExtraReferencedObjects() const;

public:
    TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& GetPerModuleDataObjects();
    const TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& GetPerModuleDataObjects() const;

public:
    FString& GetStreamingLevelsPrefix();
    const FString& GetStreamingLevelsPrefix() const;

public:
    TArray<FVector,TSizedDefaultAllocator<32> >& GetViewLocationsRenderedLastFrame();
    const TArray<FVector,TSizedDefaultAllocator<32> >& GetViewLocationsRenderedLastFrame() const;

public:
    BitfieldProxy GetbWorldWasLoadedThisTick();
    ConstBitfieldProxy GetbWorldWasLoadedThisTick() const;

public:
    BitfieldProxy GetbTriggerPostLoadMap();
    ConstBitfieldProxy GetbTriggerPostLoadMap() const;

public:
    TObjectPtr<AGameModeBase>& GetAuthorityGameMode();
    const TObjectPtr<AGameModeBase>& GetAuthorityGameMode() const;

public:
    TSet<AActor *,DefaultKeyFuncs<AActor *,0>,FDefaultSetAllocator>& GetNetworkActors();
    const TSet<AActor *,DefaultKeyFuncs<AActor *,0>,FDefaultSetAllocator>& GetNetworkActors() const;

public:
    BitfieldProxy GetbRequiresHitProxies();
    ConstBitfieldProxy GetbRequiresHitProxies() const;

public:
    BitfieldProxy GetbStreamingDataDirty();
    ConstBitfieldProxy GetbStreamingDataDirty() const;

public:
    double& GetBuildStreamingDataTimer();
    const double& GetBuildStreamingDataTimer() const;

public:
    FURL& GetURL();
    const FURL& GetURL() const;

public:
    BitfieldProxy GetbInTick();
    ConstBitfieldProxy GetbInTick() const;

public:
    BitfieldProxy GetbIsBuilt();
    ConstBitfieldProxy GetbIsBuilt() const;

public:
    BitfieldProxy GetbTickNewlySpawned();
    ConstBitfieldProxy GetbTickNewlySpawned() const;

public:
    BitfieldProxy GetbPostTickComponentUpdate();
    ConstBitfieldProxy GetbPostTickComponentUpdate() const;

public:
    int32& GetPlayerNum();
    const int32& GetPlayerNum() const;

public:
    float& GetTimeSinceLastPendingKillPurge();
    const float& GetTimeSinceLastPendingKillPurge() const;

public:
    bool& GetFullPurgeTriggered();
    const bool& GetFullPurgeTriggered() const;

public:
    bool& GetbShouldDelayGarbageCollect();
    const bool& GetbShouldDelayGarbageCollect() const;

public:
    BitfieldProxy GetbIsWorldInitialized();
    ConstBitfieldProxy GetbIsWorldInitialized() const;

public:
    int32& GetStreamingVolumeUpdateDelay();
    const int32& GetStreamingVolumeUpdateDelay() const;

public:
    BitfieldProxy GetbIsLevelStreamingFrozen();
    ConstBitfieldProxy GetbIsLevelStreamingFrozen() const;

public:
    BitfieldProxy GetbShouldForceUnloadStreamingLevels();
    ConstBitfieldProxy GetbShouldForceUnloadStreamingLevels() const;

public:
    BitfieldProxy GetbShouldForceVisibleStreamingLevels();
    ConstBitfieldProxy GetbShouldForceVisibleStreamingLevels() const;

public:
    BitfieldProxy GetbDoDelayedUpdateCullDistanceVolumes();
    ConstBitfieldProxy GetbDoDelayedUpdateCullDistanceVolumes() const;

public:
    bool& GetbHack_Force_UsesGameHiddenFlags_True();
    const bool& GetbHack_Force_UsesGameHiddenFlags_True() const;

public:
    BitfieldProxy GetbIsRunningConstructionScript();
    ConstBitfieldProxy GetbIsRunningConstructionScript() const;

public:
    BitfieldProxy GetbShouldSimulatePhysics();
    ConstBitfieldProxy GetbShouldSimulatePhysics() const;

public:
    FName& GetDebugDrawTraceTag();
    const FName& GetDebugDrawTraceTag() const;

public:
    uint32& GetAudioDeviceHandle();
    const uint32& GetAudioDeviceHandle() const;

public:
    double& GetLastTimeUnbuiltLightingWasEncountered();
    const double& GetLastTimeUnbuiltLightingWasEncountered() const;

private:
    float& GetTimeSecondsBase();
    const float& GetTimeSecondsBase() const;
    double& GetTimeSeconds501();
    const double& GetTimeSeconds501() const;

private:
    float& GetRealTimeSecondsBase();
    const float& GetRealTimeSecondsBase() const;
    double& GetRealTimeSeconds501();
    const double& GetRealTimeSeconds501() const;

private:
    float& GetAudioTimeSecondsBase();
    const float& GetAudioTimeSecondsBase() const;
    double& GetAudioTimeSeconds501();
    const double& GetAudioTimeSeconds501() const;

public:
    float& GetDeltaTimeSeconds();
    const float& GetDeltaTimeSeconds() const;

private:
    float& GetPauseDelayBase();
    const float& GetPauseDelayBase() const;
    double& GetPauseDelay501();
    const double& GetPauseDelay501() const;

public:
    bool& GetbOriginOffsetThisFrame();
    const bool& GetbOriginOffsetThisFrame() const;

public:
    FString& GetNextURL();
    const FString& GetNextURL() const;

public:
    float& GetNextSwitchCountdown();
    const float& GetNextSwitchCountdown() const;

public:
    TArray<FName,TSizedDefaultAllocator<32> >& GetPreparingLevelNames();
    const TArray<FName,TSizedDefaultAllocator<32> >& GetPreparingLevelNames() const;

public:
    FName& GetCommittedPersistentLevelName();
    const FName& GetCommittedPersistentLevelName() const;

public:
    uint32& GetNumLightingUnbuiltObjects();
    const uint32& GetNumLightingUnbuiltObjects() const;

public:
    BitfieldProxy GetbDropDetail();
    ConstBitfieldProxy GetbDropDetail() const;

public:
    BitfieldProxy GetbAggressiveLOD();
    ConstBitfieldProxy GetbAggressiveLOD() const;

public:
    BitfieldProxy GetbIsDefaultLevel();
    ConstBitfieldProxy GetbIsDefaultLevel() const;

public:
    BitfieldProxy GetbRequestedBlockOnAsyncLoading();
    ConstBitfieldProxy GetbRequestedBlockOnAsyncLoading() const;

public:
    BitfieldProxy GetbActorsInitialized();
    ConstBitfieldProxy GetbActorsInitialized() const;

public:
    BitfieldProxy GetbBegunPlay();
    ConstBitfieldProxy GetbBegunPlay() const;

public:
    BitfieldProxy GetbMatchStarted();
    ConstBitfieldProxy GetbMatchStarted() const;

public:
    BitfieldProxy GetbPlayersOnly();
    ConstBitfieldProxy GetbPlayersOnly() const;

public:
    BitfieldProxy GetbPlayersOnlyPending();
    ConstBitfieldProxy GetbPlayersOnlyPending() const;

public:
    BitfieldProxy GetbStartup();
    ConstBitfieldProxy GetbStartup() const;

public:
    BitfieldProxy GetbIsTearingDown();
    ConstBitfieldProxy GetbIsTearingDown() const;

public:
    BitfieldProxy GetbKismetScriptError();
    ConstBitfieldProxy GetbKismetScriptError() const;

public:
    BitfieldProxy GetbDebugPauseExecution();
    ConstBitfieldProxy GetbDebugPauseExecution() const;

public:
    BitfieldProxy GetbAllowAudioPlayback();
    ConstBitfieldProxy GetbAllowAudioPlayback() const;

public:
    BitfieldProxy GetbDebugFrameStepExecution();
    ConstBitfieldProxy GetbDebugFrameStepExecution() const;

public:
    BitfieldProxy GetbAreConstraintsDirty();
    ConstBitfieldProxy GetbAreConstraintsDirty() const;

public:
    FThreadSafeCounter& GetAsyncPreRegisterLevelStreamingTasks();
    const FThreadSafeCounter& GetAsyncPreRegisterLevelStreamingTasks() const;

public:
    bool& GetbCreateRenderStateForHiddenComponents();
    const bool& GetbCreateRenderStateForHiddenComponents() const;

public:
    BitfieldProxy GetbShouldTick();
    ConstBitfieldProxy GetbShouldTick() const;

private:
    float& GetUnpausedTimeSecondsBase();
    const float& GetUnpausedTimeSecondsBase() const;
    double& GetUnpausedTimeSeconds501();
    const double& GetUnpausedTimeSeconds501() const;

public:
    uint32& GetNumInvalidReflectionCaptureComponents();
    const uint32& GetNumInvalidReflectionCaptureComponents() const;

public:
    int32& GetNumTextureStreamingUnbuiltComponents();
    const int32& GetNumTextureStreamingUnbuiltComponents() const;

public:
    int32& GetNumTextureStreamingDirtyResources();
    const int32& GetNumTextureStreamingDirtyResources() const;

public:
    BitfieldProxy GetbIsCameraMoveableWhenPaused();
    ConstBitfieldProxy GetbIsCameraMoveableWhenPaused() const;

public:
    FVector& GetOriginOffsetThisFrame();
    const FVector& GetOriginOffsetThisFrame() const;

public:
    bool& GetbDebugDrawAllTraceTags();
    const bool& GetbDebugDrawAllTraceTags() const;

public:
    int32& GetActiveLevelCollectionIndex();
    const int32& GetActiveLevelCollectionIndex() const;

public:
    uint32& GetNumUnbuiltReflectionCaptures();
    const uint32& GetNumUnbuiltReflectionCaptures() const;

public:
    BitfieldProxy GetbMaterialParameterCollectionInstanceNeedsDeferredUpdate();
    ConstBitfieldProxy GetbMaterialParameterCollectionInstanceNeedsDeferredUpdate() const;

public:
    BitfieldProxy GetbCleanedUpWorld();
    ConstBitfieldProxy GetbCleanedUpWorld() const;

public:
    BitfieldProxy GetbMarkedObjectsPendingKill();
    ConstBitfieldProxy GetbMarkedObjectsPendingKill() const;

public:
    TArray<AActor *,TSizedDefaultAllocator<32> >& GetLevelSequenceActors();
    const TArray<AActor *,TSizedDefaultAllocator<32> >& GetLevelSequenceActors() const;

public:
    uint16& GetNumStreamingLevelsBeingLoaded();
    const uint16& GetNumStreamingLevelsBeingLoaded() const;

public:
    uint32& GetCleanupWorldTag();
    const uint32& GetCleanupWorldTag() const;

public:
    bool& GetbAllowDeferredPhysicsStateCreation();
    const bool& GetbAllowDeferredPhysicsStateCreation() const;

public:
    BitfieldProxy GetbInitializedAndNeedsCleanup();
    ConstBitfieldProxy GetbInitializedAndNeedsCleanup() const;

public:
    uint32& GetIsInBlockTillLevelStreamingCompleted();
    const uint32& GetIsInBlockTillLevelStreamingCompleted() const;

public:
    int32& GetBlockTillLevelStreamingCompletedEpoch();
    const int32& GetBlockTillLevelStreamingCompletedEpoch() const;

public:
    uint32& GetLWILastAssignedUID();
    const uint32& GetLWILastAssignedUID() const;

public:
    float& GetDeltaRealTimeSeconds();
    const float& GetDeltaRealTimeSeconds() const;

public:
    TOptional<bool>& GetbSupportsMakingVisibleTransactionRequests();
    const TOptional<bool>& GetbSupportsMakingVisibleTransactionRequests() const;

public:
    TOptional<bool>& GetbSupportsMakingInvisibleTransactionRequests();
    const TOptional<bool>& GetbSupportsMakingInvisibleTransactionRequests() const;

public:
    double& GetLastRenderTime();
    const double& GetLastRenderTime() const;

public:
    BitfieldProxy GetbHasEverBeenInitialized();
    ConstBitfieldProxy GetbHasEverBeenInitialized() const;

public:
    bool& GetbIsBeingCleanedUp();
    const bool& GetbIsBeingCleanedUp() const;

public:
    UE::FPlatformRWLock& GetPendingVisibilityLock();
    const UE::FPlatformRWLock& GetPendingVisibilityLock() const;

public:
    TArray<double,TSizedDefaultAllocator<32> >& GetPostProcessVolumeCachedSizes();
    const TArray<double,TSizedDefaultAllocator<32> >& GetPostProcessVolumeCachedSizes() const;

public:
    static int32_t& UEP_TotalSize();
