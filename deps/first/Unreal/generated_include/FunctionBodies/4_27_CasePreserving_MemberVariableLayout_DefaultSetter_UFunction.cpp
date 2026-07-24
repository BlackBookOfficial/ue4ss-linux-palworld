if (auto it = UFunction::MemberOffsets.find(STR("FunctionFlags")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("FunctionFlags"), 0xB8);
}

if (auto it = UFunction::MemberOffsets.find(STR("NumParms")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("NumParms"), 0xBC);
}

if (auto it = UFunction::MemberOffsets.find(STR("ParmsSize")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("ParmsSize"), 0xBE);
}

if (auto it = UFunction::MemberOffsets.find(STR("ReturnValueOffset")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("ReturnValueOffset"), 0xC0);
}

if (auto it = UFunction::MemberOffsets.find(STR("RPCId")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("RPCId"), 0xC2);
}

if (auto it = UFunction::MemberOffsets.find(STR("RPCResponseId")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("RPCResponseId"), 0xC4);
}

if (auto it = UFunction::MemberOffsets.find(STR("FirstPropertyToInit")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("FirstPropertyToInit"), 0xC8);
}

if (auto it = UFunction::MemberOffsets.find(STR("EventGraphFunction")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("EventGraphFunction"), 0xD0);
}

if (auto it = UFunction::MemberOffsets.find(STR("EventGraphCallOffset")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("EventGraphCallOffset"), 0xD8);
}

if (auto it = UFunction::MemberOffsets.find(STR("Func")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("Func"), 0xE0);
}

if (auto it = UFunction::MemberOffsets.find(STR("UEP_TotalSize")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xE8);
}
