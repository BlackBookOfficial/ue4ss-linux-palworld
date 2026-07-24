if (auto it = UDataTable::MemberOffsets.find(STR("RowStruct")); it == UDataTable::MemberOffsets.end())
{
    UDataTable::MemberOffsets.emplace(STR("RowStruct"), 0x28);
}

if (auto it = UDataTable::MemberOffsets.find(STR("RowMap")); it == UDataTable::MemberOffsets.end())
{
    UDataTable::MemberOffsets.emplace(STR("RowMap"), 0x30);
}

if (auto it = UDataTable::MemberOffsets.find(STR("bStripFromClientBuilds")); it == UDataTable::MemberOffsets.end())
{
    UDataTable::MemberOffsets.emplace(STR("bStripFromClientBuilds"), 0x80);
    UDataTable::BitfieldInfos.emplace(STR("bStripFromClientBuilds"), BitfieldInfo{0, 1, 1});
}

if (auto it = UDataTable::MemberOffsets.find(STR("UEP_TotalSize")); it == UDataTable::MemberOffsets.end())
{
    UDataTable::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xA0);
}
