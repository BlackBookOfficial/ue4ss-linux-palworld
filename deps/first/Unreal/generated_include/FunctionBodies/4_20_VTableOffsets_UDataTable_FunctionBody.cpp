if (auto it = UDataTable::VTableLayoutMap.find(STR("__vecDelDtor")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

