if (auto it = UDataTable::VTableLayoutMap.find(STR("__vecDelDtor")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("GetNonConstRowMap")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("GetNonConstRowMap"), 0x2B0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("AddRowInternal")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("AddRowInternal"), 0x2B8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("RemoveRowInternal")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("RemoveRowInternal"), 0x2C0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("GetRowMap")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("GetRowMap"), 0x2C8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("GetRowMap_C")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("GetRowMap_C"), 0x2D0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("AllowDuplicateRowsOnImport")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("AllowDuplicateRowsOnImport"), 0x2D8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("EmptyTable")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("EmptyTable"), 0x2E0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("RemoveRow")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("RemoveRow"), 0x2E8);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("AddRow__FName__Ptr_C_uint8__Ptr_C_UScriptStruct")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("AddRow__FName__Ptr_C_uint8__Ptr_C_UScriptStruct"), 0x2F0);
}

if (auto it = UDataTable::VTableLayoutMap.find(STR("AddRow__FName__Ref_C_FTableRowBase")); it == UDataTable::VTableLayoutMap.end())
{
    UDataTable::VTableLayoutMap.emplace(STR("AddRow__FName__Ref_C_FTableRowBase"), 0x2F8);
}

