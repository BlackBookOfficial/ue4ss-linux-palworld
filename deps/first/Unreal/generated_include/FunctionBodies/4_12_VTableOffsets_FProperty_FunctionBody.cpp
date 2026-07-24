if (auto it = FProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("GetCPPMacroType")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("GetCPPMacroType"), 0x1F0);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("PassCPPArgsByRef")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("PassCPPArgsByRef"), 0x1F8);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("GetCPPType")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("GetCPPType"), 0x200);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("GetCPPTypeForwardDeclaration")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("GetCPPTypeForwardDeclaration"), 0x208);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("LinkInternal")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("LinkInternal"), 0x210);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("Identical")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("Identical"), 0x218);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("SerializeItem")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("SerializeItem"), 0x220);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("NetSerializeItem")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("NetSerializeItem"), 0x228);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("ExportTextItem")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("ExportTextItem"), 0x230);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("ImportText_Internal")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("ImportText_Internal"), 0x238);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("CopyValuesInternal")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("CopyValuesInternal"), 0x240);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("GetValueTypeHashInternal")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("GetValueTypeHashInternal"), 0x248);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("CopySingleValueToScriptVM")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("CopySingleValueToScriptVM"), 0x250);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("CopyCompleteValueToScriptVM")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("CopyCompleteValueToScriptVM"), 0x258);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("CopySingleValueFromScriptVM")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("CopySingleValueFromScriptVM"), 0x260);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("CopyCompleteValueFromScriptVM")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("CopyCompleteValueFromScriptVM"), 0x268);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("ClearValueInternal")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("ClearValueInternal"), 0x270);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("DestroyValueInternal")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("DestroyValueInternal"), 0x278);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("InitializeValueInternal")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("InitializeValueInternal"), 0x280);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("GetID")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("GetID"), 0x288);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("InstanceSubobjects")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("InstanceSubobjects"), 0x290);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("GetMinAlignment")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("GetMinAlignment"), 0x298);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("ContainsObjectReference")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("ContainsObjectReference"), 0x2A0);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("ContainsWeakObjectReference")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("ContainsWeakObjectReference"), 0x2A8);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("EmitReferenceInfo")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("EmitReferenceInfo"), 0x2B0);
}

if (auto it = FProperty::VTableLayoutMap.find(STR("SameType")); it == FProperty::VTableLayoutMap.end())
{
    FProperty::VTableLayoutMap.emplace(STR("SameType"), 0x2B8);
}

