if (auto it = FConsoleCommandBase::MemberOffsets.find(STR("Flags")); it == FConsoleCommandBase::MemberOffsets.end())
{
    FConsoleCommandBase::MemberOffsets.emplace(STR("Flags"), 0x18);
}

if (auto it = FConsoleCommandBase::MemberOffsets.find(STR("Help")); it == FConsoleCommandBase::MemberOffsets.end())
{
    FConsoleCommandBase::MemberOffsets.emplace(STR("Help"), 0x8);
}

