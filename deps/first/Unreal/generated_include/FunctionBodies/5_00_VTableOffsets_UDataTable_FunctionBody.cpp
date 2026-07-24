if (auto it = UDataTable::VTableLayoutMap.find(STR("__vecDelDtor")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("GetNonConstRowMap")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("GetNonConstRowMap"), 0x2A8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("AddRowInternal")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("AddRowInternal"), 0x2B0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("GetRowMap")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("GetRowMap"), 0x2B8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("GetRowMap_C")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("GetRowMap_C"), 0x2C0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("AllowDuplicateRowsOnImport")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("AllowDuplicateRowsOnImport"), 0x2C8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("EmptyTable")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("EmptyTable"), 0x2D0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("RemoveRow")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("RemoveRow"), 0x2D8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("AddRow")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("AddRow"), 0x2E0);
}

