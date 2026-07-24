if (auto it = UFunction::MemberOffsets.find(STR("FunctionFlags")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("FunctionFlags"), 0x88);
}

if (auto it = UFunction::MemberOffsets.find(STR("RepOffset")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("RepOffset"), 0x8C);
}

if (auto it = UFunction::MemberOffsets.find(STR("NumParms")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("NumParms"), 0x8E);
}

if (auto it = UFunction::MemberOffsets.find(STR("ParmsSize")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("ParmsSize"), 0x90);
}

if (auto it = UFunction::MemberOffsets.find(STR("ReturnValueOffset")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("ReturnValueOffset"), 0x92);
}

if (auto it = UFunction::MemberOffsets.find(STR("RPCId")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("RPCId"), 0x94);
}

if (auto it = UFunction::MemberOffsets.find(STR("RPCResponseId")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("RPCResponseId"), 0x96);
}

if (auto it = UFunction::MemberOffsets.find(STR("FirstPropertyToInit")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("FirstPropertyToInit"), 0x98);
}

if (auto it = UFunction::MemberOffsets.find(STR("EventGraphFunction")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("EventGraphFunction"), 0xA0);
}

if (auto it = UFunction::MemberOffsets.find(STR("EventGraphCallOffset")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("EventGraphCallOffset"), 0xA8);
}

if (auto it = UFunction::MemberOffsets.find(STR("Func")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("Func"), 0xB0);
}

if (auto it = UFunction::MemberOffsets.find(STR("UEP_TotalSize")); it == UFunction::MemberOffsets.end())
{
    UFunction::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xB8);
}
