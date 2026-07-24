if (auto it = AGameMode::MemberOffsets.find(STR("MatchState")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("MatchState"), 0x3D0);
}

if (auto it = AGameMode::MemberOffsets.find(STR("bDelayedStart")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("bDelayedStart"), 0x3D8);
    AGameMode::BitfieldInfos.emplace(STR("bDelayedStart"), BitfieldInfo{0, 1, 4});
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumSpectators")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumSpectators"), 0x3DC);
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumPlayers")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumPlayers"), 0x3E0);
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumBots")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumBots"), 0x3E4);
}

if (auto it = AGameMode::MemberOffsets.find(STR("MinRespawnDelay")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("MinRespawnDelay"), 0x3E8);
}

if (auto it = AGameMode::MemberOffsets.find(STR("NumTravellingPlayers")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("NumTravellingPlayers"), 0x3EC);
}

if (auto it = AGameMode::MemberOffsets.find(STR("EngineMessageClass")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("EngineMessageClass"), 0x3F0);
}

if (auto it = AGameMode::MemberOffsets.find(STR("InactivePlayerArray")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("InactivePlayerArray"), 0x3F8);
}

if (auto it = AGameMode::MemberOffsets.find(STR("InactivePlayerStateLifeSpan")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("InactivePlayerStateLifeSpan"), 0x408);
}

if (auto it = AGameMode::MemberOffsets.find(STR("MaxInactivePlayers")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("MaxInactivePlayers"), 0x40C);
}

if (auto it = AGameMode::MemberOffsets.find(STR("bHandleDedicatedServerReplays")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("bHandleDedicatedServerReplays"), 0x410);
}

if (auto it = AGameMode::MemberOffsets.find(STR("UEP_TotalSize")); it == AGameMode::MemberOffsets.end())
{
    AGameMode::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x418);
}
