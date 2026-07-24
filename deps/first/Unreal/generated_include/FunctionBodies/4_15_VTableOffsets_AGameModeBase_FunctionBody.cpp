if (auto it = AGameModeBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitializeHUDForPlayer_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitializeHUDForPlayer_Implementation"), 0x5B8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitStartSpot_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitStartSpot_Implementation"), 0x5C0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnDefaultPawnAtTransform_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnDefaultPawnAtTransform_Implementation"), 0x5C8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnDefaultPawnFor_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnDefaultPawnFor_Implementation"), 0x5D0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PlayerCanRestart_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PlayerCanRestart_Implementation"), 0x5D8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("FindPlayerStart_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("FindPlayerStart_Implementation"), 0x5E0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ChoosePlayerStart_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ChoosePlayerStart_Implementation"), 0x5E8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("CanSpectate_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("CanSpectate_Implementation"), 0x5F0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("MustSpectate_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("MustSpectate_Implementation"), 0x5F8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("HandleStartingNewPlayer_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("HandleStartingNewPlayer_Implementation"), 0x600);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ShouldReset_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ShouldReset_Implementation"), 0x608);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetDefaultPawnClassForController_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetDefaultPawnClassForController_Implementation"), 0x610);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitGame")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitGame"), 0x618);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitGameState")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitGameState"), 0x620);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetGameSessionClass")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetGameSessionClass"), 0x628);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetNumPlayers")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetNumPlayers"), 0x630);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetNumSpectators")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetNumSpectators"), 0x638);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("StartPlay")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("StartPlay"), 0x640);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("HasMatchStarted")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("HasMatchStarted"), 0x648);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SetPause")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SetPause"), 0x650);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ClearPause")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ClearPause"), 0x658);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("AllowPausing")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("AllowPausing"), 0x660);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("IsPaused")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("IsPaused"), 0x668);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ResetLevel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ResetLevel"), 0x670);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ReturnToMainMenuHost")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ReturnToMainMenuHost"), 0x678);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("CanServerTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("CanServerTravel"), 0x680);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ProcessServerTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ProcessServerTravel"), 0x688);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetSeamlessTravelActorList")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetSeamlessTravelActorList"), 0x690);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SwapPlayerControllers")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SwapPlayerControllers"), 0x698);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("HandleSeamlessTravelPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("HandleSeamlessTravelPlayer"), 0x6A0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PostSeamlessTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PostSeamlessTravel"), 0x6A8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("StartToLeaveMap")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("StartToLeaveMap"), 0x6B0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GameWelcomePlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GameWelcomePlayer"), 0x6B8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PreLogin__Ref_C_FString__Ref_C_FString__Ref_C_TSharedPtr_FUniqueNetId_const_0___Ref_FString")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PreLogin__Ref_C_FString__Ref_C_FString__Ref_C_TSharedPtr_FUniqueNetId_const_0___Ref_FString"), 0x6C0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PreLogin__Ref_C_FString__Ref_C_FString__Ref_C_FUniqueNetIdRepl__Ref_FString")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PreLogin__Ref_C_FString__Ref_C_FString__Ref_C_FUniqueNetIdRepl__Ref_FString"), 0x6C8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("Login__Ptr_UPlayer__ENetRole__Ref_C_FString__Ref_C_FString__Ref_C_TSharedPtr_FUniqueNetId_const_0___Ref_FString")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("Login__Ptr_UPlayer__ENetRole__Ref_C_FString__Ref_C_FString__Ref_C_TSharedPtr_FUniqueNetId_const_0___Ref_FString"), 0x6D0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("Login__Ptr_UPlayer__ENetRole__Ref_C_FString__Ref_C_FString__Ref_C_FUniqueNetIdRepl__Ref_FString")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("Login__Ptr_UPlayer__ENetRole__Ref_C_FString__Ref_C_FString__Ref_C_FUniqueNetIdRepl__Ref_FString"), 0x6D8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PostLogin")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PostLogin"), 0x6E0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("Logout")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("Logout"), 0x6E8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnPlayerController")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnPlayerController"), 0x6F0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ChangeName")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ChangeName"), 0x6F8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("RestartPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("RestartPlayer"), 0x700);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("RestartPlayerAtPlayerStart")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("RestartPlayerAtPlayerStart"), 0x708);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("RestartPlayerAtTransform")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("RestartPlayerAtTransform"), 0x710);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SetPlayerDefaults")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SetPlayerDefaults"), 0x718);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("AllowCheats")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("AllowCheats"), 0x720);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("IsHandlingReplays")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("IsHandlingReplays"), 0x728);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnPlayerFromSimulate")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnPlayerFromSimulate"), 0x730);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ShouldStartInCinematicMode")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ShouldStartInCinematicMode"), 0x738);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("UpdateGameplayMuteList")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("UpdateGameplayMuteList"), 0x740);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitNewPlayer__Ptr_APlayerController__Ref_C_TSharedPtr_FUniqueNetId_const_0___Ref_C_FString__Ref_C_FString")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitNewPlayer__Ptr_APlayerController__Ref_C_TSharedPtr_FUniqueNetId_const_0___Ref_C_FString__Ref_C_FString"), 0x748);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitNewPlayer__Ptr_APlayerController__Ref_C_FUniqueNetIdRepl__Ref_C_FString__Ref_C_FString")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitNewPlayer__Ptr_APlayerController__Ref_C_FUniqueNetIdRepl__Ref_C_FString__Ref_C_FString"), 0x750);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GenericPlayerInitialization")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GenericPlayerInitialization"), 0x758);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ReplicateStreamingStatus")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ReplicateStreamingStatus"), 0x760);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ShouldSpawnAtStartSpot")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ShouldSpawnAtStartSpot"), 0x768);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("FinishRestartPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("FinishRestartPlayer"), 0x770);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ProcessClientTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ProcessClientTravel"), 0x778);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitSeamlessTravelPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitSeamlessTravelPlayer"), 0x780);
}

