if (auto it = FFieldPathProperty::MemberOffsets.find(STR("PropertyClass")); it == FFieldPathProperty::MemberOffsets.end())
{
    FFieldPathProperty::MemberOffsets.emplace(STR("PropertyClass"), 0x78);
}

if (auto it = FFieldPathProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FFieldPathProperty::MemberOffsets.end())
{
    FFieldPathProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x80);
}
