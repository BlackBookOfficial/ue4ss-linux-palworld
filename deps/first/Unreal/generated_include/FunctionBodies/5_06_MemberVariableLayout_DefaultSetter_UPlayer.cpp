if (auto it = UPlayer::MemberOffsets.find(STR("CurrentNetSpeed")); it == UPlayer::MemberOffsets.end())
{
    UPlayer::MemberOffsets.emplace(STR("CurrentNetSpeed"), 0x38);
}

if (auto it = UPlayer::MemberOffsets.find(STR("ConfiguredInternetSpeed")); it == UPlayer::MemberOffsets.end())
{
    UPlayer::MemberOffsets.emplace(STR("ConfiguredInternetSpeed"), 0x3C);
}

if (auto it = UPlayer::MemberOffsets.find(STR("ConfiguredLanSpeed")); it == UPlayer::MemberOffsets.end())
{
    UPlayer::MemberOffsets.emplace(STR("ConfiguredLanSpeed"), 0x40);
}

if (auto it = UPlayer::MemberOffsets.find(STR("UEP_TotalSize")); it == UPlayer::MemberOffsets.end())
{
    UPlayer::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x48);
}
