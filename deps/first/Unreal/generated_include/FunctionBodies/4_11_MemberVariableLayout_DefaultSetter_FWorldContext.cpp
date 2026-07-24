if (auto it = FWorldContext::MemberOffsets.find(STR("ContextHandle")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ContextHandle"), 0xC0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelURL"), 0xC8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelType")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelType"), 0xD8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastURL"), 0xE0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastRemoteURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastRemoteURL"), 0x150);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LevelsToLoadForPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LevelsToLoadForPendingMapChange"), 0x1D8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PendingMapChangeFailureDescription")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PendingMapChangeFailureDescription"), 0x1F8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bShouldCommitPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bShouldCommitPendingMapChange"), 0x208);
    FWorldContext::BitfieldInfos.emplace(STR("bShouldCommitPendingMapChange"), BitfieldInfo{0, 1, 4});
}

if (auto it = FWorldContext::MemberOffsets.find(STR("GameViewport")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("GameViewport"), 0x230);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEInstance")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEInstance"), 0x250);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEPrefix")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEPrefix"), 0x258);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIERemapPrefix")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIERemapPrefix"), 0x268);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("RunAsDedicated")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("RunAsDedicated"), 0x278);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bWaitingOnOnlineSubsystem")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bWaitingOnOnlineSubsystem"), 0x279);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("AudioDeviceHandle")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("AudioDeviceHandle"), 0x27C);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ExternalReferences")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ExternalReferences"), 0x280);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ThisCurrentWorld")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ThisCurrentWorld"), 0x290);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("UEP_TotalSize")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x298);
}
