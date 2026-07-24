if (auto it = UPlayer::VTableLayoutMap.find(STR("__vecDelDtor")); it == UPlayer::VTableLayoutMap.end())
{
    UPlayer::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UPlayer::VTableLayoutMap.find(STR("SwitchController")); it == UPlayer::VTableLayoutMap.end())
{
    UPlayer::VTableLayoutMap.emplace(STR("SwitchController"), 0x208);
}

