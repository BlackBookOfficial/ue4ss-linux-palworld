if (auto it = UObject::VTableLayoutMap.find(STR("__vecDelDtor")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetDetailedInfoInternal")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetDetailedInfoInternal"), 0x18);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostInitProperties")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostInitProperties"), 0x20);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PreSaveRoot")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PreSaveRoot"), 0x28);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostSaveRoot")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostSaveRoot"), 0x30);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PreSave")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PreSave"), 0x38);
}

if (auto it = UObject::VTableLayoutMap.find(STR("Modify")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("Modify"), 0x40);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostLoad")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostLoad"), 0x48);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostLoadSubobjects")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostLoadSubobjects"), 0x50);
}

if (auto it = UObject::VTableLayoutMap.find(STR("BeginDestroy")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("BeginDestroy"), 0x58);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsReadyForFinishDestroy")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsReadyForFinishDestroy"), 0x60);
}

if (auto it = UObject::VTableLayoutMap.find(STR("FinishDestroy")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("FinishDestroy"), 0x68);
}

if (auto it = UObject::VTableLayoutMap.find(STR("Serialize")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("Serialize"), 0x70);
}

if (auto it = UObject::VTableLayoutMap.find(STR("ShutdownAfterError")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("ShutdownAfterError"), 0x78);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostInterpChange")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostInterpChange"), 0x80);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostRename")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostRename"), 0x88);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostDuplicate")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostDuplicate"), 0x90);
}

if (auto it = UObject::VTableLayoutMap.find(STR("NeedsLoadForClient")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("NeedsLoadForClient"), 0x98);
}

if (auto it = UObject::VTableLayoutMap.find(STR("NeedsLoadForServer")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("NeedsLoadForServer"), 0xA0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("NeedsLoadForEditorGame")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("NeedsLoadForEditorGame"), 0xA8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsPostLoadThreadSafe")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsPostLoadThreadSafe"), 0xB0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("ExportCustomProperties")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("ExportCustomProperties"), 0xB8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("ImportCustomProperties")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("ImportCustomProperties"), 0xC0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostEditImport")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostEditImport"), 0xC8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostReloadConfig")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostReloadConfig"), 0xD0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("Rename")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("Rename"), 0xD8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetDesc")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetDesc"), 0xE0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetWorld")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetWorld"), 0xE8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetNativePropertyValues")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetNativePropertyValues"), 0xF0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetResourceSize")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetResourceSize"), 0xF8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetExporterName")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetExporterName"), 0x100);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsLocalizedResource")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsLocalizedResource"), 0x108);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetRestoreForUObjectOverwrite")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetRestoreForUObjectOverwrite"), 0x110);
}

if (auto it = UObject::VTableLayoutMap.find(STR("AreNativePropertiesIdenticalTo")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("AreNativePropertiesIdenticalTo"), 0x118);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetAssetRegistryTags")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetAssetRegistryTags"), 0x120);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsAsset")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsAsset"), 0x128);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsSafeForRootSet")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsSafeForRootSet"), 0x130);
}

if (auto it = UObject::VTableLayoutMap.find(STR("TagSubobjects")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("TagSubobjects"), 0x138);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetLifetimeReplicatedProps")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetLifetimeReplicatedProps"), 0x140);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsNameStableForNetworking")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsNameStableForNetworking"), 0x148);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsFullNameStableForNetworking")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsFullNameStableForNetworking"), 0x150);
}

if (auto it = UObject::VTableLayoutMap.find(STR("IsSupportedForNetworking")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("IsSupportedForNetworking"), 0x158);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetSubobjectsWithStableNamesForNetworking")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetSubobjectsWithStableNamesForNetworking"), 0x160);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PreNetReceive")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PreNetReceive"), 0x168);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PostNetReceive")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PostNetReceive"), 0x170);
}

if (auto it = UObject::VTableLayoutMap.find(STR("PreDestroyFromReplication")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("PreDestroyFromReplication"), 0x178);
}

if (auto it = UObject::VTableLayoutMap.find(STR("SaveConfig")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("SaveConfig"), 0x180);
}

if (auto it = UObject::VTableLayoutMap.find(STR("LoadConfig")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("LoadConfig"), 0x188);
}

if (auto it = UObject::VTableLayoutMap.find(STR("ProcessEvent")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("ProcessEvent"), 0x190);
}

if (auto it = UObject::VTableLayoutMap.find(STR("GetFunctionCallspace")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("GetFunctionCallspace"), 0x198);
}

if (auto it = UObject::VTableLayoutMap.find(STR("CallRemoteFunction")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("CallRemoteFunction"), 0x1A0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("ProcessConsoleExec")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("ProcessConsoleExec"), 0x1A8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("RegenerateClass")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("RegenerateClass"), 0x1B0);
}

if (auto it = UObject::VTableLayoutMap.find(STR("MarkAsEditorOnlySubobject")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("MarkAsEditorOnlySubobject"), 0x1B8);
}

if (auto it = UObject::VTableLayoutMap.find(STR("CheckDefaultSubobjectsInternal")); it == UObject::VTableLayoutMap.end())
{
    UObject::VTableLayoutMap.emplace(STR("CheckDefaultSubobjectsInternal"), 0x1C0);
}

