if (auto it = AGameMode::MemberOffsets.find(STR("MatchState")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("MatchState"), 0x380);
}

if (auto it = AGameMode::MemberOffsets.find(STR("bUseSeamlessTravel")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("bUseSeamlessTravel"), 0x388);
    AGameMode::BitfieldInfos.emplace(STR("bUseSeamlessTravel"), BitfieldInfo{0, 1, 4});
}

if (auto it = AGameMode::MemberOffsets.find(STR("bPauseable")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("bPauseable"), 0x388);
    AGameMode::BitfieldInfos.emplace(STR("bPauseable"), BitfieldInfo{1, 1, 4});
}

if (auto it = AGameMode::MemberOffsets.find(STR("bStartPlayersAsSpectators")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("bStartPlayersAsSpectators"), 0x388);
    AGameMode::BitfieldInfos.emplace(STR("bStartPlayersAsSpectators"), BitfieldInfo{2, 1, 4});
}

if (auto it = AGameMode::MemberOffsets.find(STR("bDelayedStart")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("bDelayedStart"), 0x388);
    AGameMode::BitfieldInfos.emplace(STR("bDelayedStart"), BitfieldInfo{3, 1, 4});
}

if (auto it = AGameMode::MemberOffsets.find(STR("OptionsString")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("OptionsString"), 0x390);
}

if (auto it = AGameMode::MemberOffsets.find(STR("HUDClass")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("HUDClass"), 0x3A8);
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumSpectators")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumSpectators"), 0x3B0);
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumPlayers")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumPlayers"), 0x3B4);
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumBots")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumBots"), 0x3B8);
}

if (auto it = AGameMode::MemberOffsets.find(STR("MinRespawnDelay")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("MinRespawnDelay"), 0x3BC);
}

if (auto it = AGameMode::MemberOffsets.find(STR("GameSession")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("GameSession"), 0x3C0);
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumTravellingPlayers")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumTravellingPlayers"), 0x3C8);
}

if (auto it = AGameMode::MemberOffsets.find(STR("CurrentID")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("CurrentID"), 0x3CC);
}

if (auto it = AGameMode::MemberOffsets.find(STR("DefaultPlayerName")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("DefaultPlayerName"), 0x3D0);
}

if (auto it = AGameMode::MemberOffsets.find(STR("EngineMessageClass")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("EngineMessageClass"), 0x3E8);
}

if (auto it = AGameMode::MemberOffsets.find(STR("SpectatorClass")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("SpectatorClass"), 0x3F8);
}

if (auto it = AGameMode::MemberOffsets.find(STR("PlayerStateClass")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("PlayerStateClass"), 0x408);
}

if (auto it = AGameMode::MemberOffsets.find(STR("InactivePlayerArray")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("InactivePlayerArray"), 0x420);
}

if (auto it = AGameMode::MemberOffsets.find(STR("Pausers")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("Pausers"), 0x430);
}

if (auto it = AGameMode::MemberOffsets.find(STR("GameModeClassAliases")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("GameModeClassAliases"), 0x440);
}

if (auto it = AGameMode::MemberOffsets.find(STR("InactivePlayerStateLifeSpan")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("InactivePlayerStateLifeSpan"), 0x450);
}

if (auto it = AGameMode::MemberOffsets.find(STR("bHandleDedicatedServerReplays")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("bHandleDedicatedServerReplays"), 0x454);
}

if (auto it = AGameMode::MemberOffsets.find(STR("UEP_TotalSize")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x458);
}
