if (auto it = FStructProperty::MemberOffsets.find(STR("Struct")); it == FStructProperty::MemberOffsets.end())
{
    FStructProperty::MemberOffsets.emplace(STR("Struct"), 0x80);
}

if (auto it = FStructProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FStructProperty::MemberOffsets.end())
{
    FStructProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x88);
}
