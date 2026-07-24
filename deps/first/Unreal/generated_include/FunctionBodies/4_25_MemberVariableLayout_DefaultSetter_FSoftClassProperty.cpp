if (auto it = FSoftClassProperty::MemberOffsets.find(STR("MetaClass")); it == FSoftClassProperty::MemberOffsets.end())
{
    FSoftClassProperty::MemberOffsets.emplace(STR("MetaClass"), 0x80);
}

if (auto it = FSoftClassProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FSoftClassProperty::MemberOffsets.end())
{
    FSoftClassProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x88);
}
