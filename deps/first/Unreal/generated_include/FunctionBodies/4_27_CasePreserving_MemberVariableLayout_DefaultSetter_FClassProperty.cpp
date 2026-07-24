if (auto it = FClassProperty::MemberOffsets.find(STR("MetaClass")); it == FClassProperty::MemberOffsets.end())
{
    FClassProperty::MemberOffsets.emplace(STR("MetaClass"), 0x88);
}

if (auto it = FClassProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FClassProperty::MemberOffsets.end())
{
    FClassProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x90);
}
