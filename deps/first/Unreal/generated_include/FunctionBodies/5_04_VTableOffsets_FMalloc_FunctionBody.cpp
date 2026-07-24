if (auto it = FMalloc::VTableLayoutMap.find(STR("__vecDelDtor")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("Malloc")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("Malloc"), 0x28);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("TryMalloc")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("TryMalloc"), 0x30);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("Realloc")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("Realloc"), 0x38);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("TryRealloc")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("TryRealloc"), 0x40);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("Free")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("Free"), 0x48);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("QuantizeSize")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("QuantizeSize"), 0x50);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("GetAllocationSize")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("GetAllocationSize"), 0x58);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("Trim")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("Trim"), 0x60);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("SetupTLSCachesOnCurrentThread")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("SetupTLSCachesOnCurrentThread"), 0x68);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("ClearAndDisableTLSCachesOnCurrentThread")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("ClearAndDisableTLSCachesOnCurrentThread"), 0x70);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("InitializeStatsMetadata")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("InitializeStatsMetadata"), 0x78);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("UpdateStats")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("UpdateStats"), 0x80);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("GetAllocatorStats")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("GetAllocatorStats"), 0x88);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("DumpAllocatorStats")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("DumpAllocatorStats"), 0x90);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("IsInternallyThreadSafe")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("IsInternallyThreadSafe"), 0x98);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("ValidateHeap")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("ValidateHeap"), 0xA0);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("GetDescriptiveName")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("GetDescriptiveName"), 0xA8);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("OnMallocInitialized")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("OnMallocInitialized"), 0xB0);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("OnPreFork")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("OnPreFork"), 0xB8);
}

if (auto it = FMalloc::VTableLayoutMap.find(STR("OnPostFork")); it == FMalloc::VTableLayoutMap.end())
{
    FMalloc::VTableLayoutMap.emplace(STR("OnPostFork"), 0xC0);
}

