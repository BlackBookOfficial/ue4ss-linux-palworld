if (auto it = ULocalPlayer::MemberOffsets.find(STR("CachedUniqueNetId")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("CachedUniqueNetId"), 0x50);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("ViewportClient")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("ViewportClient"), 0x78);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("Origin")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("Origin"), 0x80);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("Size")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("Size"), 0x88);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("LastViewLocation")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("LastViewLocation"), 0x90);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("AspectRatioAxisConstraint")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("AspectRatioAxisConstraint"), 0x9C);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("bSentSplitJoin")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("bSentSplitJoin"), 0xA8);
    ULocalPlayer::BitfieldInfos.emplace(STR("bSentSplitJoin"), BitfieldInfo{0, 1, 4});
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("ControllerId")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("ControllerId"), 0xC0);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("SlateOperations")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("SlateOperations"), 0x1A8);
}

if (auto it = ULocalPlayer::MemberOffsets.find(STR("UEP_TotalSize")); it == ULocalPlayer::MemberOffsets.end())
{
    ULocalPlayer::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x268);
}
