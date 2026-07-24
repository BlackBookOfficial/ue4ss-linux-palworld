if (auto it = IConsoleObject::VTableLayoutMap.find(STR("__vecDelDtor")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("GetHelp")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("GetHelp"), 0x8);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("SetHelp")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("SetHelp"), 0x10);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("GetFlags")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("GetFlags"), 0x18);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("SetFlags")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("SetFlags"), 0x20);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("AsVariable")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("AsVariable"), 0x28);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("IsVariableInt")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("IsVariableInt"), 0x30);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("AsVariableInt")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("AsVariableInt"), 0x38);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("AsVariableFloat")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("AsVariableFloat"), 0x40);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("AsVariableString")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("AsVariableString"), 0x48);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("AsCommand")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("AsCommand"), 0x50);
}

if (auto it = IConsoleObject::VTableLayoutMap.find(STR("Release")); it == IConsoleObject::VTableLayoutMap.end())
{
    IConsoleObject::VTableLayoutMap.emplace(STR("Release"), 0x58);
}

