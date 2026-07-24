if (auto it = FConsoleVariableBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == FConsoleVariableBase::VTableLayoutMap.end())
{
    FConsoleVariableBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

