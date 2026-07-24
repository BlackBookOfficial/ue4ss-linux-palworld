if (auto it = ULocalPlayer::MemberOffsets.find(STR("CachedUniqueNetId")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("CachedUniqueNetId"), 0x48);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("ViewportClient")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("ViewportClient"), 0x78);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("AspectRatioAxisConstraint")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("AspectRatioAxisConstraint"), 0xB8);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("bSentSplitJoin")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("bSentSplitJoin"), 0xC8);
    ULocalPlayer::BitfieldInfos.emplace(STR("bSentSplitJoin"), BitfieldInfo{0, 1, 4});
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("ControllerId")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("ControllerId"), 0xE0);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("PlatformUserId")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("PlatformUserId"), 0x100);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("SlateOperations")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("SlateOperations"), 0x1E0);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("UEP_TotalSize")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x298);
}
