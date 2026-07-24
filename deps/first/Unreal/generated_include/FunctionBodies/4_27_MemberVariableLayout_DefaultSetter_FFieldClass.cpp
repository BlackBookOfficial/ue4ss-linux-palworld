if (auto it = FFieldClass::MemberOffsets.find(STR("FName")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("FName"), 0x0);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("Id")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("Id"), 0x8);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("CastFlags")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("CastFlags"), 0x10);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("ClassFlags")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("ClassFlags"), 0x18);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("SuperClass")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("SuperClass"), 0x20);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("DefaultObject")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("DefaultObject"), 0x28);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("ConstructFn")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("ConstructFn"), 0x30);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("UnqiueNameIndexCounter")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("UnqiueNameIndexCounter"), 0x38);
}

if (auto it = FFieldClass::MemberOffsets.find(STR("UEP_TotalSize")); it == FFieldClass::MemberOffsets.end())
{
    FFieldClass::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x40);
}
