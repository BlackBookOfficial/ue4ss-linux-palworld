std::unordered_map<File::StringType, int32_t> UGameViewportClient::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> UGameViewportClient::BitfieldInfos{};

TObjectPtr<UConsole>& UGameViewportClient::GetViewportConsole()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportConsole"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportConsole' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UConsole>*>(this, offset);
}
const TObjectPtr<UConsole>& UGameViewportClient::GetViewportConsole() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportConsole"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportConsole' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UConsole>*>(this, offset);
}

TArray<FDebugDisplayProperty,TSizedDefaultAllocator<32> >& UGameViewportClient::GetDebugProperties()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DebugProperties"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::DebugProperties' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FDebugDisplayProperty,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FDebugDisplayProperty,TSizedDefaultAllocator<32> >& UGameViewportClient::GetDebugProperties() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DebugProperties"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::DebugProperties' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FDebugDisplayProperty,TSizedDefaultAllocator<32> >*>(this, offset);
}

FTitleSafeZoneArea& UGameViewportClient::GetTitleSafeZone()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TitleSafeZone"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::TitleSafeZone' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FTitleSafeZoneArea*>(this, offset);
}
const FTitleSafeZoneArea& UGameViewportClient::GetTitleSafeZone() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TitleSafeZone"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::TitleSafeZone' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FTitleSafeZoneArea*>(this, offset);
}

TArray<FSplitscreenData,TSizedDefaultAllocator<32> >& UGameViewportClient::GetSplitscreenInfo()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SplitscreenInfo"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::SplitscreenInfo' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FSplitscreenData,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FSplitscreenData,TSizedDefaultAllocator<32> >& UGameViewportClient::GetSplitscreenInfo() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SplitscreenInfo"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::SplitscreenInfo' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FSplitscreenData,TSizedDefaultAllocator<32> >*>(this, offset);
}

int32& UGameViewportClient::GetMaxSplitscreenPlayers()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxSplitscreenPlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MaxSplitscreenPlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UGameViewportClient::GetMaxSplitscreenPlayers() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxSplitscreenPlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MaxSplitscreenPlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

BitfieldProxy UGameViewportClient::GetbShowTitleSafeZone()
{
    static auto offset_it = MemberOffsets.find(STR("bShowTitleSafeZone"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bShowTitleSafeZone' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShowTitleSafeZone"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UGameViewportClient::bShowTitleSafeZone'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UGameViewportClient::GetbShowTitleSafeZone() const
{
    static auto offset_it = MemberOffsets.find(STR("bShowTitleSafeZone"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bShowTitleSafeZone' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShowTitleSafeZone"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UGameViewportClient::bShowTitleSafeZone'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UGameViewportClient::GetbIsPlayInEditorViewport()
{
    static auto offset_it = MemberOffsets.find(STR("bIsPlayInEditorViewport"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bIsPlayInEditorViewport' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsPlayInEditorViewport"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UGameViewportClient::bIsPlayInEditorViewport'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UGameViewportClient::GetbIsPlayInEditorViewport() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsPlayInEditorViewport"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bIsPlayInEditorViewport' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsPlayInEditorViewport"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UGameViewportClient::bIsPlayInEditorViewport'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UGameViewportClient::GetbDisableWorldRendering()
{
    static auto offset_it = MemberOffsets.find(STR("bDisableWorldRendering"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bDisableWorldRendering' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDisableWorldRendering"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UGameViewportClient::bDisableWorldRendering'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UGameViewportClient::GetbDisableWorldRendering() const
{
    static auto offset_it = MemberOffsets.find(STR("bDisableWorldRendering"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bDisableWorldRendering' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDisableWorldRendering"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UGameViewportClient::bDisableWorldRendering'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TEnumAsByte<enum ESplitScreenType::Type>& UGameViewportClient::GetActiveSplitscreenType()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ActiveSplitscreenType"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ActiveSplitscreenType' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TEnumAsByte<enum ESplitScreenType::Type>*>(this, offset);
}
const TEnumAsByte<enum ESplitScreenType::Type>& UGameViewportClient::GetActiveSplitscreenType() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ActiveSplitscreenType"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ActiveSplitscreenType' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TEnumAsByte<enum ESplitScreenType::Type>*>(this, offset);
}

TObjectPtr<UWorld>& UGameViewportClient::GetWorld()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("World"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::World' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UWorld>*>(this, offset);
}
const TObjectPtr<UWorld>& UGameViewportClient::GetWorld() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("World"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::World' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UWorld>*>(this, offset);
}

bool& UGameViewportClient::GetbSuppressTransitionMessage()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bSuppressTransitionMessage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bSuppressTransitionMessage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbSuppressTransitionMessage() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bSuppressTransitionMessage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bSuppressTransitionMessage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

int32& UGameViewportClient::GetViewModeIndex()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewModeIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewModeIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UGameViewportClient::GetViewModeIndex() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewModeIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewModeIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

FEngineShowFlags& UGameViewportClient::GetEngineShowFlags()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EngineShowFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::EngineShowFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FEngineShowFlags*>(this, offset);
}
const FEngineShowFlags& UGameViewportClient::GetEngineShowFlags() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EngineShowFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::EngineShowFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FEngineShowFlags*>(this, offset);
}

FViewport*& UGameViewportClient::GetViewport()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Viewport"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::Viewport' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FViewport**>(this, offset);
}
const FViewport*& UGameViewportClient::GetViewport() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Viewport"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::Viewport' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FViewport**>(this, offset);
}

FViewportFrame*& UGameViewportClient::GetViewportFrame()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FViewportFrame**>(this, offset);
}
const FViewportFrame*& UGameViewportClient::GetViewportFrame() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FViewportFrame**>(this, offset);
}

TWeakPtr<SWindow,0>& UGameViewportClient::GetWindowBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Window"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::Window' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<SWindow,0>*>(this, offset);
}
const TWeakPtr<SWindow,0>& UGameViewportClient::GetWindowBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Window"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::Window' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<SWindow,0>*>(this, offset);
}

TWeakPtr<SWindow,1>& UGameViewportClient::GetWindow500()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Window"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::Window' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<SWindow,1>*>(this, offset);
}
const TWeakPtr<SWindow,1>& UGameViewportClient::GetWindow500() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Window"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::Window' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<SWindow,1>*>(this, offset);
}

TWeakPtr<SOverlay,0>& UGameViewportClient::GetViewportOverlayWidgetBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportOverlayWidget"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportOverlayWidget' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<SOverlay,0>*>(this, offset);
}
const TWeakPtr<SOverlay,0>& UGameViewportClient::GetViewportOverlayWidgetBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportOverlayWidget"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportOverlayWidget' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<SOverlay,0>*>(this, offset);
}

TWeakPtr<SOverlay,1>& UGameViewportClient::GetViewportOverlayWidget500()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportOverlayWidget"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportOverlayWidget' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<SOverlay,1>*>(this, offset);
}
const TWeakPtr<SOverlay,1>& UGameViewportClient::GetViewportOverlayWidget500() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportOverlayWidget"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::ViewportOverlayWidget' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<SOverlay,1>*>(this, offset);
}

TWeakPtr<IGameLayerManager,0>& UGameViewportClient::GetGameLayerManagerPtrBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameLayerManagerPtr"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::GameLayerManagerPtr' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<IGameLayerManager,0>*>(this, offset);
}
const TWeakPtr<IGameLayerManager,0>& UGameViewportClient::GetGameLayerManagerPtrBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameLayerManagerPtr"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::GameLayerManagerPtr' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<IGameLayerManager,0>*>(this, offset);
}

TWeakPtr<IGameLayerManager,1>& UGameViewportClient::GetGameLayerManagerPtr500()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameLayerManagerPtr"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::GameLayerManagerPtr' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<IGameLayerManager,1>*>(this, offset);
}
const TWeakPtr<IGameLayerManager,1>& UGameViewportClient::GetGameLayerManagerPtr500() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameLayerManagerPtr"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::GameLayerManagerPtr' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<IGameLayerManager,1>*>(this, offset);
}

FName& UGameViewportClient::GetCurrentBufferVisualizationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentBufferVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentBufferVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UGameViewportClient::GetCurrentBufferVisualizationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentBufferVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentBufferVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

TWeakPtr<SWindow,0>& UGameViewportClient::GetHighResScreenshotDialogBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HighResScreenshotDialog"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HighResScreenshotDialog' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<SWindow,0>*>(this, offset);
}
const TWeakPtr<SWindow,0>& UGameViewportClient::GetHighResScreenshotDialogBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HighResScreenshotDialog"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HighResScreenshotDialog' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<SWindow,0>*>(this, offset);
}

TWeakPtr<SWindow,1>& UGameViewportClient::GetHighResScreenshotDialog500()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HighResScreenshotDialog"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HighResScreenshotDialog' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakPtr<SWindow,1>*>(this, offset);
}
const TWeakPtr<SWindow,1>& UGameViewportClient::GetHighResScreenshotDialog500() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HighResScreenshotDialog"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HighResScreenshotDialog' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakPtr<SWindow,1>*>(this, offset);
}

TMap<enum EMouseCursor::Type, TSharedRef<SWidget,0>>& UGameViewportClient::GetCursorWidgetsBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<enum EMouseCursor::Type, TSharedRef<SWidget,0>>*>(this, offset);
}
const TMap<enum EMouseCursor::Type, TSharedRef<SWidget,0>>& UGameViewportClient::GetCursorWidgetsBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<enum EMouseCursor::Type, TSharedRef<SWidget,0>>*>(this, offset);
}

TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,0>>& UGameViewportClient::GetCursorWidgets423()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,0>>*>(this, offset);
}
const TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,0>>& UGameViewportClient::GetCursorWidgets423() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,0>>*>(this, offset);
}

TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,1>>& UGameViewportClient::GetCursorWidgets500()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,1>>*>(this, offset);
}
const TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,1>>& UGameViewportClient::GetCursorWidgets500() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<enum EMouseCursor::Type, TSharedPtr<SWidget,1>>*>(this, offset);
}

FStatUnitData*& UGameViewportClient::GetStatUnitData()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StatUnitData"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::StatUnitData' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FStatUnitData**>(this, offset);
}
const FStatUnitData*& UGameViewportClient::GetStatUnitData() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StatUnitData"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::StatUnitData' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FStatUnitData**>(this, offset);
}

FStatHitchesData*& UGameViewportClient::GetStatHitchesData()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StatHitchesData"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::StatHitchesData' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FStatHitchesData**>(this, offset);
}
const FStatHitchesData*& UGameViewportClient::GetStatHitchesData() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StatHitchesData"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::StatHitchesData' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FStatHitchesData**>(this, offset);
}

bool& UGameViewportClient::GetbDisableSplitScreenOverride()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bDisableSplitScreenOverride"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bDisableSplitScreenOverride' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbDisableSplitScreenOverride() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bDisableSplitScreenOverride"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bDisableSplitScreenOverride' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

bool& UGameViewportClient::GetbIgnoreInput()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIgnoreInput"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bIgnoreInput' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbIgnoreInput() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIgnoreInput"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bIgnoreInput' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

EMouseCaptureMode::Type& UGameViewportClient::GetMouseCaptureModeBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MouseCaptureMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MouseCaptureMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EMouseCaptureMode::Type*>(this, offset);
}
const EMouseCaptureMode::Type& UGameViewportClient::GetMouseCaptureModeBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MouseCaptureMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MouseCaptureMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EMouseCaptureMode::Type*>(this, offset);
}

EMouseCaptureMode& UGameViewportClient::GetMouseCaptureMode411()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MouseCaptureMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MouseCaptureMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EMouseCaptureMode*>(this, offset);
}
const EMouseCaptureMode& UGameViewportClient::GetMouseCaptureMode411() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MouseCaptureMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MouseCaptureMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EMouseCaptureMode*>(this, offset);
}

bool& UGameViewportClient::GetbHideCursorDuringCapture()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHideCursorDuringCapture"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bHideCursorDuringCapture' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbHideCursorDuringCapture() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHideCursorDuringCapture"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bHideCursorDuringCapture' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

uint32& UGameViewportClient::GetAudioDeviceHandle()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::AudioDeviceHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UGameViewportClient::GetAudioDeviceHandle() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::AudioDeviceHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

bool& UGameViewportClient::GetbHasAudioFocus()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHasAudioFocus"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bHasAudioFocus' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbHasAudioFocus() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHasAudioFocus"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bHasAudioFocus' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

bool& UGameViewportClient::GetbLockDuringCapture()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bLockDuringCapture"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bLockDuringCapture' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbLockDuringCapture() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bLockDuringCapture"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bLockDuringCapture' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

EMouseLockMode& UGameViewportClient::GetMouseLockMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MouseLockMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MouseLockMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EMouseLockMode*>(this, offset);
}
const EMouseLockMode& UGameViewportClient::GetMouseLockMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MouseLockMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::MouseLockMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EMouseLockMode*>(this, offset);
}

bool& UGameViewportClient::GetbUseSoftwareCursorWidgets()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bUseSoftwareCursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bUseSoftwareCursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbUseSoftwareCursorWidgets() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bUseSoftwareCursorWidgets"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bUseSoftwareCursorWidgets' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

TMap<FName, TSharedPtr<FHardwareCursor,0>>& UGameViewportClient::GetHardwareCursorCacheBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursorCache"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursorCache' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<FName, TSharedPtr<FHardwareCursor,0>>*>(this, offset);
}
const TMap<FName, TSharedPtr<FHardwareCursor,0>>& UGameViewportClient::GetHardwareCursorCacheBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursorCache"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursorCache' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<FName, TSharedPtr<FHardwareCursor,0>>*>(this, offset);
}

TMap<FName, void *>& UGameViewportClient::GetHardwareCursorCache423()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursorCache"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursorCache' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<FName, void *>*>(this, offset);
}
const TMap<FName, void *>& UGameViewportClient::GetHardwareCursorCache423() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursorCache"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursorCache' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<FName, void *>*>(this, offset);
}

TMap<enum EMouseCursor::Type, TSharedPtr<FHardwareCursor,0>>& UGameViewportClient::GetHardwareCursorsBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<enum EMouseCursor::Type, TSharedPtr<FHardwareCursor,0>>*>(this, offset);
}
const TMap<enum EMouseCursor::Type, TSharedPtr<FHardwareCursor,0>>& UGameViewportClient::GetHardwareCursorsBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<enum EMouseCursor::Type, TSharedPtr<FHardwareCursor,0>>*>(this, offset);
}

TMap<enum EMouseCursor::Type, void *>& UGameViewportClient::GetHardwareCursors423()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<enum EMouseCursor::Type, void *>*>(this, offset);
}
const TMap<enum EMouseCursor::Type, void *>& UGameViewportClient::GetHardwareCursors423() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HardwareCursors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::HardwareCursors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<enum EMouseCursor::Type, void *>*>(this, offset);
}

bool& UGameViewportClient::GetbIsMouseOverClient()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIsMouseOverClient"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bIsMouseOverClient' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UGameViewportClient::GetbIsMouseOverClient() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIsMouseOverClient"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::bIsMouseOverClient' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

FName& UGameViewportClient::GetCurrentNaniteVisualizationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentNaniteVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentNaniteVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UGameViewportClient::GetCurrentNaniteVisualizationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentNaniteVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentNaniteVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

FName& UGameViewportClient::GetCurrentLumenVisualizationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentLumenVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentLumenVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UGameViewportClient::GetCurrentLumenVisualizationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentLumenVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentLumenVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

FName& UGameViewportClient::GetCurrentVirtualShadowMapVisualizationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentVirtualShadowMapVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentVirtualShadowMapVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UGameViewportClient::GetCurrentVirtualShadowMapVisualizationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentVirtualShadowMapVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentVirtualShadowMapVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

FName& UGameViewportClient::GetCurrentStrataVisualizationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentStrataVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentStrataVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UGameViewportClient::GetCurrentStrataVisualizationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentStrataVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentStrataVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

FName& UGameViewportClient::GetCurrentGroomVisualizationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentGroomVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentGroomVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UGameViewportClient::GetCurrentGroomVisualizationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentGroomVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentGroomVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

FName& UGameViewportClient::GetCurrentSubstrateVisualizationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentSubstrateVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentSubstrateVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UGameViewportClient::GetCurrentSubstrateVisualizationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentSubstrateVisualizationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UGameViewportClient::CurrentSubstrateVisualizationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

int32_t& UGameViewportClient::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

