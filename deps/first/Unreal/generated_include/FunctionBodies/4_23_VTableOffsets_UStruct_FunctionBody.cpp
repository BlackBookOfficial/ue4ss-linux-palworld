if (auto it = UStruct::VTableLayoutMap.find(STR("__vecDelDtor")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetInheritanceSuper")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetInheritanceSuper"), 0x258);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("Link")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("Link"), 0x260);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeBin_C__FStructuredArchive_FSlot__Ptr_void")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeBin_C__FStructuredArchive_FSlot__Ptr_void"), 0x268);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeBin_C__Ref_FArchive__Ptr_void")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeBin_C__Ref_FArchive__Ptr_void"), 0x270);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeTaggedProperties_C__FStructuredArchive_FSlot__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeTaggedProperties_C__FStructuredArchive_FSlot__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject"), 0x278);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeTaggedProperties_C__Ref_FArchive__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeTaggedProperties_C__Ref_FArchive__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject"), 0x280);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("InitializeStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("InitializeStruct"), 0x288);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("DestroyStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("DestroyStruct"), 0x290);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("CustomFindProperty")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("CustomFindProperty"), 0x298);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeExpr")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeExpr"), 0x2A0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetPrefixCPP")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetPrefixCPP"), 0x2A8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SetSuperStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SetSuperStruct"), 0x2B0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("PropertyNameToDisplayName")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("PropertyNameToDisplayName"), 0x2B8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetAuthoredNameForField")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetAuthoredNameForField"), 0x2C0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("FindPropertyNameFromGuid")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("FindPropertyNameFromGuid"), 0x2C8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("FindPropertyGuidFromName")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("FindPropertyGuidFromName"), 0x2D0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("ArePropertyGuidsAvailable")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("ArePropertyGuidsAvailable"), 0x2D8);
}

