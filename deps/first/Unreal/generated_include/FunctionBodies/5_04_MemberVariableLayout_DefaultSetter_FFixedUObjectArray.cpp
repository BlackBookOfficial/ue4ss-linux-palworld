if (auto it = TUObjectArray::MemberOffsets.find(STR("MaxElements")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("MaxElements"), 0x8);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("NumElements")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("NumElements"), 0xC);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("Objects")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("Objects"), 0x0);
}

