if (auto it = FField::VTableLayoutMap.find(STR("__vecDelDtor")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FField::VTableLayoutMap.find(STR("Serialize")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("Serialize"), 0x8);
}

if (auto it = FField::VTableLayoutMap.find(STR("PostLoad")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("PostLoad"), 0x10);
}

if (auto it = FField::VTableLayoutMap.find(STR("GetPreloadDependencies")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("GetPreloadDependencies"), 0x18);
}

if (auto it = FField::VTableLayoutMap.find(STR("BeginDestroy")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("BeginDestroy"), 0x20);
}

if (auto it = FField::VTableLayoutMap.find(STR("AddReferencedObjects")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("AddReferencedObjects"), 0x28);
}

if (auto it = FField::VTableLayoutMap.find(STR("AddCppProperty")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("AddCppProperty"), 0x30);
}

if (auto it = FField::VTableLayoutMap.find(STR("Bind")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("Bind"), 0x38);
}

if (auto it = FField::VTableLayoutMap.find(STR("PostDuplicate")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("PostDuplicate"), 0x40);
}

if (auto it = FField::VTableLayoutMap.find(STR("GetInnerFieldByName")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("GetInnerFieldByName"), 0x48);
}

if (auto it = FField::VTableLayoutMap.find(STR("GetInnerFields")); it == FField::VTableLayoutMap.end())
{
    FField::VTableLayoutMap.emplace(STR("GetInnerFields"), 0x50);
}

