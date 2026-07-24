if (auto it = FWorldContext::MemberOffsets.find(STR("ContextHandle")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ContextHandle"), 0xA0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelURL"), 0xA8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelType")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelType"), 0xB8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastURL"), 0xC0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastRemoteURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastRemoteURL"), 0x128);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LevelsToLoadForPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LevelsToLoadForPendingMapChange"), 0x1A8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PendingMapChangeFailureDescription")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PendingMapChangeFailureDescription"), 0x1C8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bShouldCommitPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bShouldCommitPendingMapChange"), 0x1D8);
    FWorldContext::BitfieldInfos.emplace(STR("bShouldCommitPendingMapChange"), BitfieldInfo{0, 1, 16});
}

if (auto it = FWorldContext::MemberOffsets.find(STR("GameViewport")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("GameViewport"), 0x200);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEInstance")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEInstance"), 0x220);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEPrefix")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEPrefix"), 0x228);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("RunAsDedicated")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("RunAsDedicated"), 0x23C);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bWaitingOnOnlineSubsystem")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bWaitingOnOnlineSubsystem"), 0x23D);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("AudioDeviceID")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("AudioDeviceID"), 0x240);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("CustomDescription")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("CustomDescription"), 0x248);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEFixedTickSeconds")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEFixedTickSeconds"), 0x258);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEAccumulatedTickSeconds")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEAccumulatedTickSeconds"), 0x25C);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ExternalReferences")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ExternalReferences"), 0x260);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ThisCurrentWorld")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ThisCurrentWorld"), 0x270);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("UEP_TotalSize")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x278);
}
