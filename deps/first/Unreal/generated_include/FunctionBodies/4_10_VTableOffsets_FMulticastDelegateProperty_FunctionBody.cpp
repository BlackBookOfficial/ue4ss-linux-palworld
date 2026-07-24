if (auto it = FMulticastDelegateProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FMulticastDelegateProperty::VTableLayoutMap.end())
{
    FMulticastDelegateProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

