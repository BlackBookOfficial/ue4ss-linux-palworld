if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("__vecDelDtor")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("CalcSceneView")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("CalcSceneView"), 0x210);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("PlayerAdded")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("PlayerAdded"), 0x218);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("InitOnlineSession")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("InitOnlineSession"), 0x220);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("PlayerRemoved")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("PlayerRemoved"), 0x228);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("SpawnPlayActor")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("SpawnPlayActor"), 0x230);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("SendSplitJoin")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("SendSplitJoin"), 0x238);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("SetControllerId")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("SetControllerId"), 0x240);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetNickname")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetNickname"), 0x248);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetGameLoginOptions")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetGameLoginOptions"), 0x250);
}

if (auto it = ULocalPlayer::VTableLayoutMap.find(STR("GetProjectionData")); it == ULocalPlayer::VTableLayoutMap.end())
{
    ULocalPlayer::VTableLayoutMap.emplace(STR("GetProjectionData"), 0x258);
}

