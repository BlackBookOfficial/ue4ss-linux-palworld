if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("__vecDelDtor")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetViewPoint")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetViewPoint"), 0x2B0);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetSlateUser_C")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetSlateUser_C"), 0x2B8);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetSlateUser")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetSlateUser"), 0x2C0);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("CalcSceneViewInitOptions")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("CalcSceneViewInitOptions"), 0x2C8);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("CalcSceneView")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("CalcSceneView"), 0x2D0);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("PlayerAdded")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("PlayerAdded"), 0x2D8);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("InitOnlineSession")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("InitOnlineSession"), 0x2E0);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("PlayerRemoved")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("PlayerRemoved"), 0x2E8);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("SpawnPlayActor")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("SpawnPlayActor"), 0x2F0);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("SendSplitJoin")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("SendSplitJoin"), 0x2F8);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("SetControllerId")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("SetControllerId"), 0x300);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("SetPlatformUserId")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("SetPlatformUserId"), 0x308);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetLocalPlayerIndex")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetLocalPlayerIndex"), 0x310);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetNickname")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetNickname"), 0x318);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetGameLoginOptions")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetGameLoginOptions"), 0x320);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetUniqueNetIdForPlatformUser")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetUniqueNetIdForPlatformUser"), 0x328);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetPreferredUniqueNetId")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetPreferredUniqueNetId"), 0x330);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetProjectionData")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetProjectionData"), 0x338);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("CleanupViewState")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("CleanupViewState"), 0x340);
}

