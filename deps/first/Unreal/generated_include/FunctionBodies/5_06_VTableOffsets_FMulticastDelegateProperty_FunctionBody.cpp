if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x8);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("GetMulticastDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("GetMulticastDelegate"), 0x1D0);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("SetMulticastDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("SetMulticastDelegate"), 0x1D8);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("AddDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("AddDelegate"), 0x1E0);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("RemoveDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("RemoveDelegate"), 0x1E8);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("ClearDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("ClearDelegate"), 0x1F0);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("GetMulticastScriptDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("GetMulticastScriptDelegate"), 0x1F8);
}

