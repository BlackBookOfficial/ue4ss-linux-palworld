if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("GetMulticastDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("GetMulticastDelegate"), 0x338);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("SetMulticastDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("SetMulticastDelegate"), 0x340);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("AddDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("AddDelegate"), 0x348);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("RemoveDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("RemoveDelegate"), 0x350);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("ClearDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("ClearDelegate"), 0x358);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("GetInvocationList")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("GetInvocationList"), 0x360);
}

