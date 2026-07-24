if (auto it = UEngine::VTableLayoutMap.find(STR("__vecDelDtor")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("WorldAdded")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("WorldAdded"), 0x240);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("WorldDestroyed")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("WorldDestroyed"), 0x248);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("IsInitialized")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("IsInitialized"), 0x250);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("Init")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("Init"), 0x258);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("Start")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("Start"), 0x260);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("PreExit")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("PreExit"), 0x268);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ShutdownAudioDeviceManager")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ShutdownAudioDeviceManager"), 0x270);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("Tick")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("Tick"), 0x278);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("GetMaxTickRate")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("GetMaxTickRate"), 0x280);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("GetMaxFPS")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("GetMaxFPS"), 0x288);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("SetMaxFPS")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("SetMaxFPS"), 0x290);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("UpdateRunningAverageDeltaTime")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("UpdateRunningAverageDeltaTime"), 0x298);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("IsAllowedFramerateSmoothing")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("IsAllowedFramerateSmoothing"), 0x2A0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("OnLostFocusPause")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("OnLostFocusPause"), 0x2A8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ShouldThrottleCPUUsage")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ShouldThrottleCPUUsage"), 0x2B0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ShouldDrawBrushWireframe")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ShouldDrawBrushWireframe"), 0x2B8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("GetMapBuildCancelled")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("GetMapBuildCancelled"), 0x2C0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("SetMapBuildCancelled")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("SetMapBuildCancelled"), 0x2C8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("GetPropertyColorationColor")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("GetPropertyColorationColor"), 0x2D0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("AllowSelectTranslucent")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("AllowSelectTranslucent"), 0x2D8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("OnlyLoadEditorVisibleLevelsInPIE")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("OnlyLoadEditorVisibleLevelsInPIE"), 0x2E0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("PreferToStreamLevelsInPIE")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("PreferToStreamLevelsInPIE"), 0x2E8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("GetSpriteCategoryIndex")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("GetSpriteCategoryIndex"), 0x2F0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("StartFPSChart")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("StartFPSChart"), 0x2F8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("StopFPSChart")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("StopFPSChart"), 0x300);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ProcessToggleFreezeCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ProcessToggleFreezeCommand"), 0x308);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ProcessToggleFreezeStreamingCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ProcessToggleFreezeStreamingCommand"), 0x310);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("IsSettingUpPlayWorld")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("IsSettingUpPlayWorld"), 0x318);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("GetGameViewportWidget")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("GetGameViewportWidget"), 0x320);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("FocusNextPIEWorld")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("FocusNextPIEWorld"), 0x328);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ResetPIEAudioSetting")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ResetPIEAudioSetting"), 0x330);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("GetNextPIEViewport")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("GetNextPIEViewport"), 0x338);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("RemapGamepadControllerIdForPIE")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("RemapGamepadControllerIdForPIE"), 0x340);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("NotifyToolsOfObjectReplacement")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("NotifyToolsOfObjectReplacement"), 0x348);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("UseSound")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("UseSound"), 0x350);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("CreatePIEWorldByDuplication")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("CreatePIEWorldByDuplication"), 0x358);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("Experimental_ShouldPreDuplicateMap")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("Experimental_ShouldPreDuplicateMap"), 0x360);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("InitializeAudioDeviceManager")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("InitializeAudioDeviceManager"), 0x368);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("InitializeHMDDevice")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("InitializeHMDDevice"), 0x370);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("InitializeEyeTrackingDevice")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("InitializeEyeTrackingDevice"), 0x378);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("RecordHMDAnalytics")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("RecordHMDAnalytics"), 0x380);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("InitializeObjectReferences")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("InitializeObjectReferences"), 0x388);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("InitializePortalServices")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("InitializePortalServices"), 0x390);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("InitializeRunningAverageDeltaTime")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("InitializeRunningAverageDeltaTime"), 0x398);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("SpawnServerActors")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("SpawnServerActors"), 0x3A0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleNetworkFailure")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleNetworkFailure"), 0x3A8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleTravelFailure")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleTravelFailure"), 0x3B0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleNetworkLagStateChanged")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleNetworkLagStateChanged"), 0x3B8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("NetworkRemapPath__Ptr_UPendingNetGame__Ref_FString__bool")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("NetworkRemapPath__Ptr_UPendingNetGame__Ref_FString__bool"), 0x3C0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("NetworkRemapPath__Ptr_UNetDriver__Ref_FString__bool")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("NetworkRemapPath__Ptr_UNetDriver__Ref_FString__bool"), 0x3C8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleOpenCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleOpenCommand"), 0x3D0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleTravelCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleTravelCommand"), 0x3D8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleStreamMapCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleStreamMapCommand"), 0x3E0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleServerTravelCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleServerTravelCommand"), 0x3E8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleSayCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleSayCommand"), 0x3F0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleDisconnectCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleDisconnectCommand"), 0x3F8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleReconnectCommand")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleReconnectCommand"), 0x400);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("Browse")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("Browse"), 0x408);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("TickWorldTravel")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("TickWorldTravel"), 0x410);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("LoadMap")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("LoadMap"), 0x418);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("RedrawViewports")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("RedrawViewports"), 0x420);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("TriggerStreamingDataRebuild")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("TriggerStreamingDataRebuild"), 0x428);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("LoadMapRedrawViewports")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("LoadMapRedrawViewports"), 0x430);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("CancelAllPending")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("CancelAllPending"), 0x438);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("CancelPending__Ptr_UNetDriver")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("CancelPending__Ptr_UNetDriver"), 0x440);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("CancelPending__Ref_FWorldContext")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("CancelPending__Ref_FWorldContext"), 0x448);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("CancelPending__Ptr_UWorld__Ptr_UPendingNetGame")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("CancelPending__Ptr_UWorld__Ptr_UPendingNetGame"), 0x450);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("WorldIsPIEInNewViewport")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("WorldIsPIEInNewViewport"), 0x458);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("VerifyLoadMapWorldCleanup")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("VerifyLoadMapWorldCleanup"), 0x460);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("DestroyWorldContext")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("DestroyWorldContext"), 0x468);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("AreEditorAnalyticsEnabled")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("AreEditorAnalyticsEnabled"), 0x470);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("CreateStartupAnalyticsAttributes")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("CreateStartupAnalyticsAttributes"), 0x478);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("IsAutosaving")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("IsAutosaving"), 0x480);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ShouldDoAsyncEndOfFrameTasks")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ShouldDoAsyncEndOfFrameTasks"), 0x488);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("MovePendingLevel")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("MovePendingLevel"), 0x490);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("ShouldShutdownWorldNetDriver")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("ShouldShutdownWorldNetDriver"), 0x498);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleBrowseToDefaultMapFailure")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleBrowseToDefaultMapFailure"), 0x4A0);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleNetworkFailure_NotifyGameInstance")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleNetworkFailure_NotifyGameInstance"), 0x4A8);
}

if (auto it = UEngine::VTableLayoutMap.find(STR("HandleTravelFailure_NotifyGameInstance")); it == UEngine::VTableLayoutMap.end())
{
    UEngine::VTableLayoutMap.emplace(STR("HandleTravelFailure_NotifyGameInstance"), 0x4B0);
}

