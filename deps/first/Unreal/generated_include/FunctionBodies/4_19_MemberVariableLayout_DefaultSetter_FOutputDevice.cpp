if (auto it = FOutputDevice::MemberOffsets.find(STR("bSuppressEventTag")); it == FOutputDevice::MemberOffsets.end())
{
    FOutputDevice::MemberOffsets.emplace(STR("bSuppressEventTag"), 0x8);
}

if (auto it = FOutputDevice::MemberOffsets.find(STR("bAutoEmitLineTerminator")); it == FOutputDevice::MemberOffsets.end())
{
    FOutputDevice::MemberOffsets.emplace(STR("bAutoEmitLineTerminator"), 0x9);
}

if (auto it = FOutputDevice::MemberOffsets.find(STR("UEP_TotalSize")); it == FOutputDevice::MemberOffsets.end())
{
    FOutputDevice::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x10);
}
