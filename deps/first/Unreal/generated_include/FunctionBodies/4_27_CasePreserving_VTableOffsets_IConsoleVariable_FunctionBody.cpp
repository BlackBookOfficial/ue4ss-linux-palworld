if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("__vecDelDtor")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("Set")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("Set"), 0x80);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("GetBool")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("GetBool"), 0x88);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("GetInt")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("GetInt"), 0x90);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("GetFloat")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("GetFloat"), 0x98);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("GetString")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("GetString"), 0xA0);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("SetOnChangedCallback")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("SetOnChangedCallback"), 0xA8);
}

if (auto it = IConsoleVariable::VTableLayoutMap.find(STR("OnChangedDelegate")); it == IConsoleVariable::VTableLayoutMap.end())
{
    IConsoleVariable::VTableLayoutMap.emplace(STR("OnChangedDelegate"), 0xB0);
}

