if (auto it = FUObjectItem::MemberOffsets.find(STR("FlagsAndRefCount")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("FlagsAndRefCount"), 0x0);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("RemoteId")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("RemoteId"), 0x0);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("Object")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("Object"), 0x8);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("ObjectPtrLow")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("ObjectPtrLow"), 0x8);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("SerialNumber")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("SerialNumber"), 0x10);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("ClusterRootIndex")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("ClusterRootIndex"), 0x14);
}

if (auto it = FUObjectItem::MemberOffsets.find(STR("UEP_TotalSize")); it == FUObjectItem::MemberOffsets.end())
{
    FUObjectItem::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x18);
}
