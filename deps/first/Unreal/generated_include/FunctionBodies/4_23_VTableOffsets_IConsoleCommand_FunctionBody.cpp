if (auto it = IConsoleCommand::VTableLayoutMap.find(STR("__vecDelDtor")); it == IConsoleCommand::VTableLayoutMap.end())
{
    IConsoleCommand::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = IConsoleCommand::VTableLayoutMap.find(STR("Execute")); it == IConsoleCommand::VTableLayoutMap.end())
{
    IConsoleCommand::VTableLayoutMap.emplace(STR("Execute"), 0x70);
}

