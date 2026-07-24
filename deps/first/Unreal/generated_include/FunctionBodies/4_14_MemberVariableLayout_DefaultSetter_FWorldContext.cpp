if (auto it = FWorldContext::MemberOffsets.find(STR("ContextHandle")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ContextHandle"), 0xC8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelURL"), 0xD0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelType")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelType"), 0xE0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastURL"), 0xE8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastRemoteURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastRemoteURL"), 0x158);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LevelsToLoadForPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LevelsToLoadForPendingMapChange"), 0x1E0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PendingMapChangeFailureDescription")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PendingMapChangeFailureDescription"), 0x200);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bShouldCommitPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bShouldCommitPendingMapChange"), 0x210);
    FWorldContext::BitfieldInfos.emplace(STR("bShouldCommitPendingMapChange"), BitfieldInfo{0, 1, 4});
}

if (auto it = FWorldContext::MemberOffsets.find(STR("GameViewport")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("GameViewport"), 0x238);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEInstance")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEInstance"), 0x258);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEPrefix")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEPrefix"), 0x260);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIERemapPrefix")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIERemapPrefix"), 0x270);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("RunAsDedicated")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("RunAsDedicated"), 0x280);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bWaitingOnOnlineSubsystem")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bWaitingOnOnlineSubsystem"), 0x281);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("AudioDeviceHandle")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("AudioDeviceHandle"), 0x284);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ExternalReferences")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ExternalReferences"), 0x288);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ThisCurrentWorld")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ThisCurrentWorld"), 0x298);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("UEP_TotalSize")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x2A0);
}
