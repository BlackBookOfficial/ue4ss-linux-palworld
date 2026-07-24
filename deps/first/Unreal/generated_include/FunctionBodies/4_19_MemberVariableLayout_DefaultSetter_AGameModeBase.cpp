if (auto it = AGameModeBase::MemberOffsets.find(STR("OptionsString")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("OptionsString"), 0x318);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("GameSessionClass")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("GameSessionClass"), 0x328);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("PlayerStateClass")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("PlayerStateClass"), 0x340);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("HUDClass")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("HUDClass"), 0x348);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("SpectatorClass")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("SpectatorClass"), 0x358);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("ServerStatReplicatorClass")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("ServerStatReplicatorClass"), 0x368);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("GameSession")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("GameSession"), 0x370);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("ServerStatReplicator")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("ServerStatReplicator"), 0x380);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("DefaultPlayerName")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("DefaultPlayerName"), 0x388);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("bUseSeamlessTravel")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("bUseSeamlessTravel"), 0x3A0);
    AGameModeBase::BitfieldInfos.emplace(STR("bUseSeamlessTravel"), BitfieldInfo{0, 1, 4});
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("bStartPlayersAsSpectators")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("bStartPlayersAsSpectators"), 0x3A0);
    AGameModeBase::BitfieldInfos.emplace(STR("bStartPlayersAsSpectators"), BitfieldInfo{1, 1, 4});
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("bPauseable")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("bPauseable"), 0x3A0);
    AGameModeBase::BitfieldInfos.emplace(STR("bPauseable"), BitfieldInfo{2, 1, 4});
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("Pausers")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("Pausers"), 0x3A8);
}

if (auto it = AGameModeBase::MemberOffsets.find(STR("UEP_TotalSize")); it == AGameModeBase::MemberOffsets.end())
{
    AGameModeBase::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x3B8);
}
