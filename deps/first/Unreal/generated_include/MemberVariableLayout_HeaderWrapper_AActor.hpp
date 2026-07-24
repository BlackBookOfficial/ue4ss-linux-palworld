static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FActorTickFunction& GetPrimaryActorTick();
    const FActorTickFunction& GetPrimaryActorTick() const;

public:
    float& GetCustomTimeDilation();
    const float& GetCustomTimeDilation() const;

public:
    BitfieldProxy GetbHidden();
    ConstBitfieldProxy GetbHidden() const;

public:
    BitfieldProxy GetbNetTemporary();
    ConstBitfieldProxy GetbNetTemporary() const;

public:
    BitfieldProxy GetbNetStartup();
    ConstBitfieldProxy GetbNetStartup() const;

public:
    BitfieldProxy GetbOnlyRelevantToOwner();
    ConstBitfieldProxy GetbOnlyRelevantToOwner() const;

public:
    BitfieldProxy GetbAlwaysRelevant();
    ConstBitfieldProxy GetbAlwaysRelevant() const;

public:
    BitfieldProxy GetbReplicateMovement();
    ConstBitfieldProxy GetbReplicateMovement() const;

public:
    BitfieldProxy GetbTearOff();
    ConstBitfieldProxy GetbTearOff() const;

public:
    BitfieldProxy GetbExchangedRoles();
    ConstBitfieldProxy GetbExchangedRoles() const;

public:
    BitfieldProxy GetbPendingNetUpdate();
    ConstBitfieldProxy GetbPendingNetUpdate() const;

public:
    BitfieldProxy GetbNetLoadOnClient();
    ConstBitfieldProxy GetbNetLoadOnClient() const;

public:
    BitfieldProxy GetbNetUseOwnerRelevancy();
    ConstBitfieldProxy GetbNetUseOwnerRelevancy() const;

public:
    BitfieldProxy GetbBlockInput();
    ConstBitfieldProxy GetbBlockInput() const;

public:
    BitfieldProxy GetbRunningUserConstructionScript();
    ConstBitfieldProxy GetbRunningUserConstructionScript() const;

public:
    BitfieldProxy GetbHasFinishedSpawning();
    ConstBitfieldProxy GetbHasFinishedSpawning() const;

public:
    BitfieldProxy GetbActorEnableCollision();
    ConstBitfieldProxy GetbActorEnableCollision() const;

public:
    BitfieldProxy GetbReplicates();
    ConstBitfieldProxy GetbReplicates() const;

public:
    TEnumAsByte<enum ENetRole>& GetRemoteRole();
    const TEnumAsByte<enum ENetRole>& GetRemoteRole() const;

public:
    TObjectPtr<AActor>& GetOwner();
    const TObjectPtr<AActor>& GetOwner() const;

public:
    FRepMovement& GetReplicatedMovement();
    const FRepMovement& GetReplicatedMovement() const;

public:
    FRepAttachment& GetAttachmentReplication();
    const FRepAttachment& GetAttachmentReplication() const;

public:
    TEnumAsByte<enum ENetRole>& GetRole();
    const TEnumAsByte<enum ENetRole>& GetRole() const;

public:
    TEnumAsByte<enum ENetDormancy>& GetNetDormancy();
    const TEnumAsByte<enum ENetDormancy>& GetNetDormancy() const;

public:
    TEnumAsByte<enum EAutoReceiveInput::Type>& GetAutoReceiveInput();
    const TEnumAsByte<enum EAutoReceiveInput::Type>& GetAutoReceiveInput() const;

public:
    int32& GetInputPriority();
    const int32& GetInputPriority() const;

public:
    TObjectPtr<UInputComponent>& GetInputComponent();
    const TObjectPtr<UInputComponent>& GetInputComponent() const;

public:
    TEnumAsByte<enum EInputConsumeOptions>& GetInputConsumeOption_DEPRECATED();
    const TEnumAsByte<enum EInputConsumeOptions>& GetInputConsumeOption_DEPRECATED() const;

public:
    float& GetNetCullDistanceSquared();
    const float& GetNetCullDistanceSquared() const;

public:
    int32& GetNetTag();
    const int32& GetNetTag() const;

public:
    float& GetNetUpdateTime();
    const float& GetNetUpdateTime() const;

public:
    float& GetNetUpdateFrequency();
    const float& GetNetUpdateFrequency() const;

public:
    float& GetNetPriority();
    const float& GetNetPriority() const;

public:
    float& GetLastNetUpdateTime();
    const float& GetLastNetUpdateTime() const;

public:
    FName& GetNetDriverName();
    const FName& GetNetDriverName() const;

public:
    BitfieldProxy GetbAutoDestroyWhenFinished();
    ConstBitfieldProxy GetbAutoDestroyWhenFinished() const;

public:
    BitfieldProxy GetbCanBeDamaged();
    ConstBitfieldProxy GetbCanBeDamaged() const;

public:
    BitfieldProxy GetbActorIsBeingDestroyed();
    ConstBitfieldProxy GetbActorIsBeingDestroyed() const;

public:
    BitfieldProxy GetbCollideWhenPlacing();
    ConstBitfieldProxy GetbCollideWhenPlacing() const;

public:
    BitfieldProxy GetbFindCameraComponentWhenViewTarget();
    ConstBitfieldProxy GetbFindCameraComponentWhenViewTarget() const;

public:
    BitfieldProxy GetbRelevantForNetworkReplays();
    ConstBitfieldProxy GetbRelevantForNetworkReplays() const;

public:
    ESpawnActorCollisionHandlingMethod& GetSpawnCollisionHandlingMethod();
    const ESpawnActorCollisionHandlingMethod& GetSpawnCollisionHandlingMethod() const;

public:
    float& GetCreationTime();
    const float& GetCreationTime() const;

public:
    TArray<TObjectPtr<AActor>,TSizedDefaultAllocator<32> >& GetChildren();
    const TArray<TObjectPtr<AActor>,TSizedDefaultAllocator<32> >& GetChildren() const;

public:
    TObjectPtr<USceneComponent>& GetRootComponent();
    const TObjectPtr<USceneComponent>& GetRootComponent() const;

public:
    TArray<AMatineeActor *,TSizedDefaultAllocator<32> >& GetControllingMatineeActors();
    const TArray<AMatineeActor *,TSizedDefaultAllocator<32> >& GetControllingMatineeActors() const;

public:
    float& GetInitialLifeSpan();
    const float& GetInitialLifeSpan() const;

public:
    FTimerHandle& GetTimerHandle_LifeSpanExpired();
    const FTimerHandle& GetTimerHandle_LifeSpanExpired() const;

public:
    BitfieldProxy GetbAllowReceiveTickEventOnDedicatedServer();
    ConstBitfieldProxy GetbAllowReceiveTickEventOnDedicatedServer() const;

public:
    TArray<FName,TSizedDefaultAllocator<32> >& GetLayers();
    const TArray<FName,TSizedDefaultAllocator<32> >& GetLayers() const;

public:
    TWeakObjectPtr<AActor,FWeakObjectPtr>& GetParentComponentActor();
    const TWeakObjectPtr<AActor,FWeakObjectPtr>& GetParentComponentActor() const;

public:
    BitfieldProxy GetbActorInitialized();
    ConstBitfieldProxy GetbActorInitialized() const;

public:
    BitfieldProxy GetbActorHasBegunPlay();
    ConstBitfieldProxy GetbActorHasBegunPlay() const;

public:
    BitfieldProxy GetbActorSeamlessTraveled();
    ConstBitfieldProxy GetbActorSeamlessTraveled() const;

public:
    BitfieldProxy GetbIgnoresOriginShifting();
    ConstBitfieldProxy GetbIgnoresOriginShifting() const;

public:
    BitfieldProxy GetbEnableAutoLODGeneration();
    ConstBitfieldProxy GetbEnableAutoLODGeneration() const;

public:
    TArray<FName,TSizedDefaultAllocator<32> >& GetTags();
    const TArray<FName,TSizedDefaultAllocator<32> >& GetTags() const;

public:
    uint64& GetHiddenEditorViews();
    const uint64& GetHiddenEditorViews() const;

public:
    FTakeAnyDamageSignature& GetOnTakeAnyDamage();
    const FTakeAnyDamageSignature& GetOnTakeAnyDamage() const;

public:
    FTakePointDamageSignature& GetOnTakePointDamage();
    const FTakePointDamageSignature& GetOnTakePointDamage() const;

public:
    FActorBeginOverlapSignature& GetOnActorBeginOverlap();
    const FActorBeginOverlapSignature& GetOnActorBeginOverlap() const;

public:
    FActorEndOverlapSignature& GetOnActorEndOverlap();
    const FActorEndOverlapSignature& GetOnActorEndOverlap() const;

public:
    FActorBeginCursorOverSignature& GetOnBeginCursorOver();
    const FActorBeginCursorOverSignature& GetOnBeginCursorOver() const;

public:
    FActorEndCursorOverSignature& GetOnEndCursorOver();
    const FActorEndCursorOverSignature& GetOnEndCursorOver() const;

public:
    FActorOnClickedSignature& GetOnClicked();
    const FActorOnClickedSignature& GetOnClicked() const;

public:
    FActorOnReleasedSignature& GetOnReleased();
    const FActorOnReleasedSignature& GetOnReleased() const;

public:
    FActorOnInputTouchBeginSignature& GetOnInputTouchBegin();
    const FActorOnInputTouchBeginSignature& GetOnInputTouchBegin() const;

public:
    FActorOnInputTouchEndSignature& GetOnInputTouchEnd();
    const FActorOnInputTouchEndSignature& GetOnInputTouchEnd() const;

public:
    FActorBeginTouchOverSignature& GetOnInputTouchEnter();
    const FActorBeginTouchOverSignature& GetOnInputTouchEnter() const;

public:
    FActorEndTouchOverSignature& GetOnInputTouchLeave();
    const FActorEndTouchOverSignature& GetOnInputTouchLeave() const;

public:
    FActorHitSignature& GetOnActorHit();
    const FActorHitSignature& GetOnActorHit() const;

public:
    FActorDestroyedSignature& GetOnDestroyed();
    const FActorDestroyedSignature& GetOnDestroyed() const;

public:
    FActorEndPlaySignature& GetOnEndPlay();
    const FActorEndPlaySignature& GetOnEndPlay() const;

public:
    FRenderCommandFence& GetDetachFence();
    const FRenderCommandFence& GetDetachFence() const;

public:
    BitfieldProxy GetbAllowTickBeforeBeginPlay();
    ConstBitfieldProxy GetbAllowTickBeforeBeginPlay() const;

public:
    BitfieldProxy GetbTickFunctionsRegistered();
    ConstBitfieldProxy GetbTickFunctionsRegistered() const;

public:
    BitfieldProxy GetbNetCheckedInitialPhysicsState();
    ConstBitfieldProxy GetbNetCheckedInitialPhysicsState() const;

public:
    TWeakObjectPtr<AActor,FWeakObjectPtr>& GetParentComponentActor_DEPRECATED();
    const TWeakObjectPtr<AActor,FWeakObjectPtr>& GetParentComponentActor_DEPRECATED() const;

public:
    TWeakObjectPtr<UChildActorComponent,FWeakObjectPtr>& GetParentComponent();
    const TWeakObjectPtr<UChildActorComponent,FWeakObjectPtr>& GetParentComponent() const;

public:
    BitfieldProxy GetActorHasBegunPlay();
    ConstBitfieldProxy GetActorHasBegunPlay() const;

public:
    float& GetMinNetUpdateFrequency();
    const float& GetMinNetUpdateFrequency() const;

public:
    BitfieldProxy GetbGenerateOverlapEventsDuringLevelStreaming();
    ConstBitfieldProxy GetbGenerateOverlapEventsDuringLevelStreaming() const;

public:
    BitfieldProxy GetbHasDeferredComponentRegistration();
    ConstBitfieldProxy GetbHasDeferredComponentRegistration() const;

public:
    BitfieldProxy GetbCanBeInCluster();
    ConstBitfieldProxy GetbCanBeInCluster() const;

public:
    BitfieldProxy GetbReplayRewindable();
    ConstBitfieldProxy GetbReplayRewindable() const;

public:
    BitfieldProxy GetbIsEditorOnlyActor();
    ConstBitfieldProxy GetbIsEditorOnlyActor() const;

public:
    BitfieldProxy GetbActorWantsDestroyDuringBeginPlay();
    ConstBitfieldProxy GetbActorWantsDestroyDuringBeginPlay() const;

public:
    FTakeRadialDamageSignature& GetOnTakeRadialDamage();
    const FTakeRadialDamageSignature& GetOnTakeRadialDamage() const;

public:
    float& GetCachedLastRenderTime();
    const float& GetCachedLastRenderTime() const;

public:
    BitfieldProxy GetbRelevantForLevelBounds();
    ConstBitfieldProxy GetbRelevantForLevelBounds() const;

private:
    float& GetLastRenderTimeBase();
    const float& GetLastRenderTimeBase() const;
    FActorLastRenderTime& GetLastRenderTime505();
    const FActorLastRenderTime& GetLastRenderTime505() const;

public:
    BitfieldProxy GetbActorBeginningPlayFromLevelStreaming();
    ConstBitfieldProxy GetbActorBeginningPlayFromLevelStreaming() const;

public:
    EActorUpdateOverlapsMethod& GetUpdateOverlapsMethodDuringLevelStreaming();
    const EActorUpdateOverlapsMethod& GetUpdateOverlapsMethodDuringLevelStreaming() const;

public:
    EActorUpdateOverlapsMethod& GetDefaultUpdateOverlapsMethodDuringLevelStreaming();
    const EActorUpdateOverlapsMethod& GetDefaultUpdateOverlapsMethodDuringLevelStreaming() const;

public:
    BitfieldProxy GetbActorIsBeingConstructed();
    ConstBitfieldProxy GetbActorIsBeingConstructed() const;

public:
    BitfieldProxy GetbForceNetAddressable();
    ConstBitfieldProxy GetbForceNetAddressable() const;

public:
    BitfieldProxy GetbCallPreReplication();
    ConstBitfieldProxy GetbCallPreReplication() const;

public:
    BitfieldProxy GetbCallPreReplicationForReplay();
    ConstBitfieldProxy GetbCallPreReplicationForReplay() const;

public:
    int32& GetRayTracingGroupId();
    const int32& GetRayTracingGroupId() const;

public:
    BitfieldProxy GetbReplicateUsingRegisteredSubObjectList();
    ConstBitfieldProxy GetbReplicateUsingRegisteredSubObjectList() const;

public:
    BitfieldProxy GetbHasRegisteredAllComponents();
    ConstBitfieldProxy GetbHasRegisteredAllComponents() const;

public:
    BitfieldProxy GetbAsyncPhysicsTickEnabled();
    ConstBitfieldProxy GetbAsyncPhysicsTickEnabled() const;

public:
    UE::Net::FSubObjectRegistry& GetReplicatedSubObjects();
    const UE::Net::FSubObjectRegistry& GetReplicatedSubObjects() const;

public:
    TArray<UE::Net::FReplicatedComponentInfo,TSizedDefaultAllocator<32> >& GetReplicatedComponentsInfo();
    const TArray<UE::Net::FReplicatedComponentInfo,TSizedDefaultAllocator<32> >& GetReplicatedComponentsInfo() const;

public:
    EPhysicsReplicationMode& GetPhysicsReplicationMode();
    const EPhysicsReplicationMode& GetPhysicsReplicationMode() const;

public:
    uint8& GetActorCategory();
    const uint8& GetActorCategory() const;

public:
    BitfieldProxy GetbHasPreRegisteredAllComponents();
    ConstBitfieldProxy GetbHasPreRegisteredAllComponents() const;

public:
    BitfieldProxy GetbActorIsPendingPostNetInit();
    ConstBitfieldProxy GetbActorIsPendingPostNetInit() const;

public:
    TObjectPtr<UHLODLayer>& GetHLODLayer();
    const TObjectPtr<UHLODLayer>& GetHLODLayer() const;

public:
    static int32_t& UEP_TotalSize();
