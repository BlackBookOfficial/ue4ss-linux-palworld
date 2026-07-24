static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    TObjectPtr<UConsole>& GetViewportConsole();
    const TObjectPtr<UConsole>& GetViewportConsole() const;

public:
    TArray<FDebugDisplayProperty,TSizedDefaultAllocator<32> >& GetDebugProperties();
    const TArray<FDebugDisplayProperty,TSizedDefaultAllocator<32> >& GetDebugProperties() const;

public:
    FTitleSafeZoneArea& GetTitleSafeZone();
    const FTitleSafeZoneArea& GetTitleSafeZone() const;

public:
    TArray<FSplitscreenData,TSizedDefaultAllocator<32> >& GetSplitscreenInfo();
    const TArray<FSplitscreenData,TSizedDefaultAllocator<32> >& GetSplitscreenInfo() const;

public:
    int32& GetMaxSplitscreenPlayers();
    const int32& GetMaxSplitscreenPlayers() const;

public:
    BitfieldProxy GetbShowTitleSafeZone();
    ConstBitfieldProxy GetbShowTitleSafeZone() const;

public:
    BitfieldProxy GetbIsPlayInEditorViewport();
    ConstBitfieldProxy GetbIsPlayInEditorViewport() const;

public:
    BitfieldProxy GetbDisableWorldRendering();
    ConstBitfieldProxy GetbDisableWorldRendering() const;

public:
    TEnumAsByte<enum ESplitScreenType::Type>& GetActiveSplitscreenType();
    const TEnumAsByte<enum ESplitScreenType::Type>& GetActiveSplitscreenType() const;

public:
    TObjectPtr<UWorld>& GetWorld();
    const TObjectPtr<UWorld>& GetWorld() const;

public:
    bool& GetbSuppressTransitionMessage();
    const bool& GetbSuppressTransitionMessage() const;

public:
    int32& GetViewModeIndex();
    const int32& GetViewModeIndex() const;

public:
    FEngineShowFlags& GetEngineShowFlags();
    const FEngineShowFlags& GetEngineShowFlags() const;

public:
    FViewport*& GetViewport();
    const FViewport*& GetViewport() const;

public:
    FViewportFrame*& GetViewportFrame();
    const FViewportFrame*& GetViewportFrame() const;

private:
    TWeakPtr<SWindow,0>& GetWindowBase();
    const TWeakPtr<SWindow,0>& GetWindowBase() const;
    TWeakPtr<SWindow,1>& GetWindow500();
    const TWeakPtr<SWindow,1>& GetWindow500() const;

private:
    TWeakPtr<SOverlay,0>& GetViewportOverlayWidgetBase();
    const TWeakPtr<SOverlay,0>& GetViewportOverlayWidgetBase() const;
    TWeakPtr<SOverlay,1>& GetViewportOverlayWidget500();
    const TWeakPtr<SOverlay,1>& GetViewportOverlayWidget500() const;

private:
    TWeakPtr<IGameLayerManager,0>& GetGameLayerManagerPtrBase();
    const TWeakPtr<IGameLayerManager,0>& GetGameLayerManagerPtrBase() const;
    TWeakPtr<IGameLayerManager,1>& GetGameLayerManagerPtr500();
    const TWeakPtr<IGameLayerManager,1>& GetGameLayerManagerPtr500() const;

public:
    FName& GetCurrentBufferVisualizationMode();
    const FName& GetCurrentBufferVisualizationMode() const;

private:
    TWeakPtr<SWindow,0>& GetHighResScreenshotDialogBase();
    const TWeakPtr<SWindow,0>& GetHighResScreenshotDialogBase() const;
    TWeakPtr<SWindow,1>& GetHighResScreenshotDialog500();
    const TWeakPtr<SWindow,1>& GetHighResScreenshotDialog500() const;

private:
    TMap<enum EMouseCursor::Type, TSharedRef<SWidget,0>>& GetCursorWidgetsBase();
    const TMap<enum EMouseCursor::Type, TSharedRef<SWidget,0>>& GetCursorWidgetsBase() const;
    TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,0>>& GetCursorWidgets423();
    const TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,0>>& GetCursorWidgets423() const;
    TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,1>>& GetCursorWidgets500();
    const TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,1>>& GetCursorWidgets500() const;

public:
    FStatUnitData*& GetStatUnitData();
    const FStatUnitData*& GetStatUnitData() const;

public:
    FStatHitchesData*& GetStatHitchesData();
    const FStatHitchesData*& GetStatHitchesData() const;

public:
    bool& GetbDisableSplitScreenOverride();
    const bool& GetbDisableSplitScreenOverride() const;

public:
    bool& GetbIgnoreInput();
    const bool& GetbIgnoreInput() const;

private:
    EMouseCaptureMode::Type& GetMouseCaptureModeBase();
    const EMouseCaptureMode::Type& GetMouseCaptureModeBase() const;
    EMouseCaptureMode& GetMouseCaptureMode411();
    const EMouseCaptureMode& GetMouseCaptureMode411() const;

public:
    bool& GetbHideCursorDuringCapture();
    const bool& GetbHideCursorDuringCapture() const;

public:
    uint32& GetAudioDeviceHandle();
    const uint32& GetAudioDeviceHandle() const;

public:
    bool& GetbHasAudioFocus();
    const bool& GetbHasAudioFocus() const;

public:
    bool& GetbLockDuringCapture();
    const bool& GetbLockDuringCapture() const;

public:
    EMouseLockMode& GetMouseLockMode();
    const EMouseLockMode& GetMouseLockMode() const;

public:
    bool& GetbUseSoftwareCursorWidgets();
    const bool& GetbUseSoftwareCursorWidgets() const;

private:
    TMap<FName, TSharedPtr<FHardwareCursor,0>>& GetHardwareCursorCacheBase();
    const TMap<FName, TSharedPtr<FHardwareCursor,0>>& GetHardwareCursorCacheBase() const;
    TMap<FName, void *>& GetHardwareCursorCache423();
    const TMap<FName, void *>& GetHardwareCursorCache423() const;

private:
    TMap<enum EMouseCursor::Type, TSharedPtr<FHardwareCursor,0>>& GetHardwareCursorsBase();
    const TMap<enum EMouseCursor::Type, TSharedPtr<FHardwareCursor,0>>& GetHardwareCursorsBase() const;
    TMap<enum EMouseCursor::Type, void *>& GetHardwareCursors423();
    const TMap<enum EMouseCursor::Type, void *>& GetHardwareCursors423() const;

public:
    bool& GetbIsMouseOverClient();
    const bool& GetbIsMouseOverClient() const;

public:
    FName& GetCurrentNaniteVisualizationMode();
    const FName& GetCurrentNaniteVisualizationMode() const;

public:
    FName& GetCurrentLumenVisualizationMode();
    const FName& GetCurrentLumenVisualizationMode() const;

public:
    FName& GetCurrentVirtualShadowMapVisualizationMode();
    const FName& GetCurrentVirtualShadowMapVisualizationMode() const;

public:
    FName& GetCurrentStrataVisualizationMode();
    const FName& GetCurrentStrataVisualizationMode() const;

public:
    FName& GetCurrentGroomVisualizationMode();
    const FName& GetCurrentGroomVisualizationMode() const;

public:
    FName& GetCurrentSubstrateVisualizationMode();
    const FName& GetCurrentSubstrateVisualizationMode() const;

public:
    static int32_t& UEP_TotalSize();
