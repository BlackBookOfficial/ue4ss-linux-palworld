if (auto it = UFunction::MemberOffsets.find(STR("FunctionFlags")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("FunctionFlags"), 0x98);
}

if (auto it = UFunction::MemberOffsets.find(STR("NumParms")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("NumParms"), 0x9C);
}

if (auto it = UFunction::MemberOffsets.find(STR("ParmsSize")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("ParmsSize"), 0x9E);
}

if (auto it = UFunction::MemberOffsets.find(STR("ReturnValueOffset")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("ReturnValueOffset"), 0xA0);
}

if (auto it = UFunction::MemberOffsets.find(STR("RPCId")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("RPCId"), 0xA2);
}

if (auto it = UFunction::MemberOffsets.find(STR("RPCResponseId")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("RPCResponseId"), 0xA4);
}

if (auto it = UFunction::MemberOffsets.find(STR("FirstPropertyToInit")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("FirstPropertyToInit"), 0xA8);
}

if (auto it = UFunction::MemberOffsets.find(STR("EventGraphFunction")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("EventGraphFunction"), 0xB0);
}

if (auto it = UFunction::MemberOffsets.find(STR("EventGraphCallOffset")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("EventGraphCallOffset"), 0xB8);
}

if (auto it = UFunction::MemberOffsets.find(STR("Func")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("Func"), 0xC0);
}

if (auto it = UFunction::MemberOffsets.find(STR("UEP_TotalSize")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xC8);
}
