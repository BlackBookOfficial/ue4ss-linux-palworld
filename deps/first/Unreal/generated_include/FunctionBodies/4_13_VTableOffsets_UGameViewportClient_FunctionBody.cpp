if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("__vecDelDtor")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SSSwapControllers")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SSSwapControllers"), 0x1E0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("ShowTitleSafeArea")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("ShowTitleSafeArea"), 0x1E8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetConsoleTarget")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetConsoleTarget"), 0x1F0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("Init")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("Init"), 0x1F8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("FinalizeViews")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("FinalizeViews"), 0x200);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("AddViewportWidgetContent")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("AddViewportWidgetContent"), 0x208);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("RemoveViewportWidgetContent")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("RemoveViewportWidgetContent"), 0x210);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("AddViewportWidgetForPlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("AddViewportWidgetForPlayer"), 0x218);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("RemoveViewportWidgetForPlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("RemoveViewportWidgetForPlayer"), 0x220);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DetachViewportClient")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DetachViewportClient"), 0x228);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("Tick")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("Tick"), 0x230);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetViewportFrame")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetViewportFrame"), 0x238);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetViewport")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetViewport"), 0x240);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetDropDetail")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetDropDetail"), 0x248);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("ConsoleCommand")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("ConsoleCommand"), 0x250);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("SetupInitialLocalPlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("SetupInitialLocalPlayer"), 0x258);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("CreatePlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("CreatePlayer"), 0x260);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("RemovePlayer")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("RemovePlayer"), 0x268);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("UpdateActiveSplitscreenType")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("UpdateActiveSplitscreenType"), 0x270);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("LayoutPlayers")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("LayoutPlayers"), 0x278);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("GetSubtitleRegion")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("GetSubtitleRegion"), 0x280);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DrawTitleSafeArea")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DrawTitleSafeArea"), 0x288);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("PostRender")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("PostRender"), 0x290);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DrawTransition")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DrawTransition"), 0x298);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("DrawTransitionMessage")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("DrawTransitionMessage"), 0x2A0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("NotifyPlayerAdded")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("NotifyPlayerAdded"), 0x2A8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("NotifyPlayerRemoved")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("NotifyPlayerRemoved"), 0x2B0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("PeekTravelFailureMessages")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("PeekTravelFailureMessages"), 0x2B8);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("PeekNetworkFailureMessages")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("PeekNetworkFailureMessages"), 0x2C0);
}

if (auto it = UGameViewportClient::VTableLayoutMap.find(STR("VerifyPathRenderingComponents")); it == UGameViewportClient::VTableLayoutMap.end())
{
    UGameViewportClient::VTableLayoutMap.emplace(STR("VerifyPathRenderingComponents"), 0x2C8);
}

