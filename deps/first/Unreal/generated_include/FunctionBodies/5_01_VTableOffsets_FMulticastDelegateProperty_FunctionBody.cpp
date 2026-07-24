if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("GetMulticastDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("GetMulticastDelegate"), 0x168);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("SetMulticastDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("SetMulticastDelegate"), 0x170);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("AddDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("AddDelegate"), 0x178);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("RemoveDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("RemoveDelegate"), 0x180);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("ClearDelegate")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("ClearDelegate"), 0x188);
}

if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("GetInvocationList")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("GetInvocationList"), 0x190);
}

