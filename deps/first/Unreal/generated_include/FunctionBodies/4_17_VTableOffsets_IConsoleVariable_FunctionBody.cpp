if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("__vecDelDtor")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("Set")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("Set"), 0x60);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("GetInt")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("GetInt"), 0x68);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("GetFloat")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("GetFloat"), 0x70);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("GetString")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("GetString"), 0x78);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("SetOnChangedCallback")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("SetOnChangedCallback"), 0x80);
}

