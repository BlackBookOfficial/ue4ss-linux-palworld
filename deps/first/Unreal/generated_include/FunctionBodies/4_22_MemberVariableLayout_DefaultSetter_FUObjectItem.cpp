if (auto it = FUObjectItem::MemberOffsets.find(STR("Object")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("Object"), 0x0);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("Flags")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("Flags"), 0x8);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("ClusterRootIndex")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("ClusterRootIndex"), 0xC);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("SerialNumber")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("SerialNumber"), 0x10);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("UEP_TotalSize")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x18);
}
