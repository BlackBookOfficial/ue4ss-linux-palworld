if (auto it = UGameViewportClient::MemberOffsets.find(STR("ViewportConsole")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("ViewportConsole"), 0x40);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("DebugProperties")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("DebugProperties"), 0x48);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("SplitscreenInfo")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("SplitscreenInfo"), 0x58);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("MaxSplitscreenPlayers")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("MaxSplitscreenPlayers"), 0x68);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bShowTitleSafeZone")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bShowTitleSafeZone"), 0x6C);
    UGameViewportClient::BitfieldInfos.emplace(STR("bShowTitleSafeZone"), BitfieldInfo{0, 1, 16});
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bIsPlayInEditorViewport")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bIsPlayInEditorViewport"), 0x6C);
    UGameViewportClient::BitfieldInfos.emplace(STR("bIsPlayInEditorViewport"), BitfieldInfo{1, 1, 4});
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bDisableWorldRendering")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bDisableWorldRendering"), 0x6C);
    UGameViewportClient::BitfieldInfos.emplace(STR("bDisableWorldRendering"), BitfieldInfo{2, 1, 16});
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("ActiveSplitscreenType")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("ActiveSplitscreenType"), 0x70);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("World")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("World"), 0x78);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bSuppressTransitionMessage")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bSuppressTransitionMessage"), 0x88);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("ViewModeIndex")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("ViewModeIndex"), 0xB0);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("EngineShowFlags")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("EngineShowFlags"), 0xB8);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("Viewport")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("Viewport"), 0xE8);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("ViewportFrame")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("ViewportFrame"), 0xF0);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("AudioDeviceHandle")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("AudioDeviceHandle"), 0xF8);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bHasAudioFocus")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bHasAudioFocus"), 0xFC);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("Window")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("Window"), 0x100);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("ViewportOverlayWidget")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("ViewportOverlayWidget"), 0x110);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("GameLayerManagerPtr")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("GameLayerManagerPtr"), 0x120);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("CurrentBufferVisualizationMode")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("CurrentBufferVisualizationMode"), 0x130);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("CurrentNaniteVisualizationMode")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("CurrentNaniteVisualizationMode"), 0x138);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("CurrentLumenVisualizationMode")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("CurrentLumenVisualizationMode"), 0x140);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("CurrentVirtualShadowMapVisualizationMode")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("CurrentVirtualShadowMapVisualizationMode"), 0x148);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("HighResScreenshotDialog")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("HighResScreenshotDialog"), 0x150);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("HardwareCursorCache")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("HardwareCursorCache"), 0x160);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("HardwareCursors")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("HardwareCursors"), 0x1B0);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("CursorWidgets")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("CursorWidgets"), 0x200);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bUseSoftwareCursorWidgets")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bUseSoftwareCursorWidgets"), 0x250);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("StatUnitData")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("StatUnitData"), 0x388);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("StatHitchesData")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("StatHitchesData"), 0x390);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bDisableSplitScreenOverride")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bDisableSplitScreenOverride"), 0x398);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bIgnoreInput")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bIgnoreInput"), 0x399);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("MouseCaptureMode")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("MouseCaptureMode"), 0x39A);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bHideCursorDuringCapture")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bHideCursorDuringCapture"), 0x39B);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("MouseLockMode")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("MouseLockMode"), 0x39C);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("bIsMouseOverClient")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("bIsMouseOverClient"), 0x39D);
}

if (auto it = UGameViewportClient::MemberOffsets.find(STR("UEP_TotalSize")); it == UGameViewportClient::MemberOffsets.end())
{
    UGameViewportClient::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x3A0);
}
