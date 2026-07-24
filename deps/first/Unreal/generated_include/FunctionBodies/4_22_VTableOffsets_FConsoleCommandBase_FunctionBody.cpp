if (auto it = FConsoleCommandBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == FConsoleCommandBase::VTableLayoutMap.end())
{
    FConsoleCommandBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

