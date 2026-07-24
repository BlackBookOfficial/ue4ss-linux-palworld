if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("__vecDelDtor")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SSSwapControllers")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SSSwapControllers"), 0x2A8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("ShowTitleSafeArea")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("ShowTitleSafeArea"), 0x2B0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetConsoleTarget")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetConsoleTarget"), 0x2B8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("CreateGameViewport")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("CreateGameViewport"), 0x2C0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("Init")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("Init"), 0x2C8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("FinalizeViews")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("FinalizeViews"), 0x2D0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("RemapControllerInput")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("RemapControllerInput"), 0x2D8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("AddViewportWidgetContent")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("AddViewportWidgetContent"), 0x2E0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("RemoveViewportWidgetContent")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("RemoveViewportWidgetContent"), 0x2E8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("AddViewportWidgetForPlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("AddViewportWidgetForPlayer"), 0x2F0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("RemoveViewportWidgetForPlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("RemoveViewportWidgetForPlayer"), 0x2F8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DetachViewportClient")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DetachViewportClient"), 0x300);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("Tick")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("Tick"), 0x308);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetViewportFrame")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetViewportFrame"), 0x310);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetViewport")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetViewport"), 0x318);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetDropDetail")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetDropDetail"), 0x320);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("ConsoleCommand")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("ConsoleCommand"), 0x328);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("GetMousePosition")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("GetMousePosition"), 0x330);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetupInitialLocalPlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetupInitialLocalPlayer"), 0x338);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("UpdateActiveSplitscreenType")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("UpdateActiveSplitscreenType"), 0x340);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("LayoutPlayers")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("LayoutPlayers"), 0x348);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("GetSubtitleRegion")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("GetSubtitleRegion"), 0x350);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DrawTitleSafeArea")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DrawTitleSafeArea"), 0x358);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("PostRender")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("PostRender"), 0x360);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DrawTransition")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DrawTransition"), 0x368);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DrawTransitionMessage")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DrawTransitionMessage"), 0x370);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("NotifyPlayerAdded")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("NotifyPlayerAdded"), 0x378);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("NotifyPlayerRemoved")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("NotifyPlayerRemoved"), 0x380);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("PeekTravelFailureMessages")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("PeekTravelFailureMessages"), 0x388);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("PeekNetworkFailureMessages")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("PeekNetworkFailureMessages"), 0x390);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("VerifyPathRenderingComponents")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("VerifyPathRenderingComponents"), 0x398);
}

