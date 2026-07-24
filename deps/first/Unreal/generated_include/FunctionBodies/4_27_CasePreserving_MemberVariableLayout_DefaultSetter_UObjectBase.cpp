if (auto it = UObjectBase::MemberOffsets.find(STR("ObjectFlags")); it == UObjectBase::MemberOffsets.end())
{
    UObjectBase::MemberOffsets.emplace(STR("ObjectFlags"), 0x8);
}

if (auto it = UObjectBase::MemberOffsets.find(STR("InternalIndex_Private")); it == UObjectBase::MemberOffsets.end())
{
    UObjectBase::MemberOffsets.emplace(STR("InternalIndex_Private"), 0xC);
}

if (auto it = UObjectBase::MemberOffsets.find(STR("ClassPrivate")); it == UObjectBase::MemberOffsets.end())
{
    UObjectBase::MemberOffsets.emplace(STR("ClassPrivate"), 0x10);
}

if (auto it = UObjectBase::MemberOffsets.find(STR("NamePrivate")); it == UObjectBase::MemberOffsets.end())
{
    UObjectBase::MemberOffsets.emplace(STR("NamePrivate"), 0x18);
}

if (auto it = UObjectBase::MemberOffsets.find(STR("OuterPrivate")); it == UObjectBase::MemberOffsets.end())
{
    UObjectBase::MemberOffsets.emplace(STR("OuterPrivate"), 0x28);
}

if (auto it = UObjectBase::MemberOffsets.find(STR("UEP_TotalSize")); it == UObjectBase::MemberOffsets.end())
{
    UObjectBase::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x30);
}
