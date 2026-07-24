if (auto it = TUObjectArray::MemberOffsets.find(STR("Chunks")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("Chunks"), 0x0);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("NumElements")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("NumElements"), 0x1000);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("NumChunks")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("NumChunks"), 0x1004);
}

if (auto it = TUObjectArray::MemberOffsets.find(STR("UEP_TotalSize")); it == TUObjectArray::MemberOffsets.end())
{
    TUObjectArray::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x1008);
}
