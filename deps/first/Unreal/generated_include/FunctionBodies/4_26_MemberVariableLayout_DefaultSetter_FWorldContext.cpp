if (auto it = FWorldContext::MemberOffsets.find(STR("ContextHandle")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ContextHandle"), 0xB0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelURL"), 0xB8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("TravelType")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("TravelType"), 0xC8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastURL"), 0xD0);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LastRemoteURL")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LastRemoteURL"), 0x138);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("LevelsToLoadForPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("LevelsToLoadForPendingMapChange"), 0x1B8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PendingMapChangeFailureDescription")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PendingMapChangeFailureDescription"), 0x1D8);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bShouldCommitPendingMapChange")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bShouldCommitPendingMapChange"), 0x1E8);
    FWorldContext::BitfieldInfos.emplace(STR("bShouldCommitPendingMapChange"), BitfieldInfo{0, 1, 4});
}

if (auto it = FWorldContext::MemberOffsets.find(STR("GameViewport")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("GameViewport"), 0x210);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEInstance")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEInstance"), 0x230);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEPrefix")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEPrefix"), 0x238);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("RunAsDedicated")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("RunAsDedicated"), 0x24C);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("bWaitingOnOnlineSubsystem")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("bWaitingOnOnlineSubsystem"), 0x24D);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("AudioDeviceID")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("AudioDeviceID"), 0x250);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("CustomDescription")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("CustomDescription"), 0x258);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEFixedTickSeconds")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEFixedTickSeconds"), 0x268);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("PIEAccumulatedTickSeconds")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("PIEAccumulatedTickSeconds"), 0x26C);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ExternalReferences")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ExternalReferences"), 0x270);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("ThisCurrentWorld")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("ThisCurrentWorld"), 0x280);
}

if (auto it = FWorldContext::MemberOffsets.find(STR("UEP_TotalSize")); it == FWorldContext::MemberOffsets.end())
{
    FWorldContext::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x288);
}
