if (auto it = TUObjectArray::MemberOffsets.find(STR("MaxChunks")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("MaxChunks"), 0x18);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("MaxElements")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("MaxElements"), 0x10);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("NumChunks")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("NumChunks"), 0x1C);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("NumElements")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("NumElements"), 0x14);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("Objects")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("Objects"), 0x0);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("PreAllocatedObjects")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("PreAllocatedObjects"), 0x8);
}

