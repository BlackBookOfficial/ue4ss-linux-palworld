if (auto it = FObjectPropertyBase::MemberOffsets.find(STR("PropertyClass")); it == FObjectPropertyBase::MemberOffsets.end())
{
    FObjectPropertyBase::MemberOffsets.emplace(STR("PropertyClass"), 0x70);
}

if (auto it = FObjectPropertyBase::MemberOffsets.find(STR("UEP_TotalSize")); it == FObjectPropertyBase::MemberOffsets.end())
{
    FObjectPropertyBase::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x78);
}
