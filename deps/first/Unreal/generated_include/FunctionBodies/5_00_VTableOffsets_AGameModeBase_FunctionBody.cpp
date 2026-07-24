if (auto it = AGameModeBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitializeHUDForPlayer_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitializeHUDForPlayer_Implementation"), 0x6B0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitStartSpot_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitStartSpot_Implementation"), 0x6B8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnDefaultPawnAtTransform_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnDefaultPawnAtTransform_Implementation"), 0x6C0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnDefaultPawnFor_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnDefaultPawnFor_Implementation"), 0x6C8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PlayerCanRestart_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PlayerCanRestart_Implementation"), 0x6D0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("FindPlayerStart_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("FindPlayerStart_Implementation"), 0x6D8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ChoosePlayerStart_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ChoosePlayerStart_Implementation"), 0x6E0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("CanSpectate_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("CanSpectate_Implementation"), 0x6E8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("MustSpectate_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("MustSpectate_Implementation"), 0x6F0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("HandleStartingNewPlayer_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("HandleStartingNewPlayer_Implementation"), 0x6F8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ShouldReset_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ShouldReset_Implementation"), 0x700);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetDefaultPawnClassForController_Implementation")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetDefaultPawnClassForController_Implementation"), 0x708);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitGame")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitGame"), 0x710);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitGameState")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitGameState"), 0x718);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetGameSessionClass")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetGameSessionClass"), 0x720);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetNumPlayers")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetNumPlayers"), 0x728);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetNumSpectators")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetNumSpectators"), 0x730);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("StartPlay")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("StartPlay"), 0x738);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("HasMatchStarted")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("HasMatchStarted"), 0x740);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("HasMatchEnded")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("HasMatchEnded"), 0x748);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SetPause")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SetPause"), 0x750);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ClearPause")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ClearPause"), 0x758);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("AllowPausing")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("AllowPausing"), 0x760);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("IsPaused")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("IsPaused"), 0x768);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ResetLevel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ResetLevel"), 0x770);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ReturnToMainMenuHost")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ReturnToMainMenuHost"), 0x778);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("CanServerTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("CanServerTravel"), 0x780);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ProcessServerTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ProcessServerTravel"), 0x788);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetSeamlessTravelActorList")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetSeamlessTravelActorList"), 0x790);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SwapPlayerControllers")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SwapPlayerControllers"), 0x798);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GetPlayerControllerClassToSpawnForSeamlessTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GetPlayerControllerClassToSpawnForSeamlessTravel"), 0x7A0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("HandleSeamlessTravelPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("HandleSeamlessTravelPlayer"), 0x7A8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PostSeamlessTravel")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PostSeamlessTravel"), 0x7B0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("StartToLeaveMap")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("StartToLeaveMap"), 0x7B8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GameWelcomePlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GameWelcomePlayer"), 0x7C0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PreLogin")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PreLogin"), 0x7C8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("Login")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("Login"), 0x7D0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("PostLogin")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("PostLogin"), 0x7D8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("OnPostLogin")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("OnPostLogin"), 0x7E0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("Logout")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("Logout"), 0x7E8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnPlayerController__ENetRole__Ref_C_UE_Math_TVector_double___Ref_C_UE_Math_TRotator_double_")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnPlayerController__ENetRole__Ref_C_UE_Math_TVector_double___Ref_C_UE_Math_TRotator_double_"), 0x7F0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnPlayerController__ENetRole__Ref_C_FString")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnPlayerController__ENetRole__Ref_C_FString"), 0x7F8);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnReplayPlayerController")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnReplayPlayerController"), 0x800);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ChangeName")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ChangeName"), 0x808);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("RestartPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("RestartPlayer"), 0x810);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("RestartPlayerAtPlayerStart")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("RestartPlayerAtPlayerStart"), 0x818);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("RestartPlayerAtTransform")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("RestartPlayerAtTransform"), 0x820);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SetPlayerDefaults")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SetPlayerDefaults"), 0x828);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("AllowCheats")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("AllowCheats"), 0x830);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("IsHandlingReplays")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("IsHandlingReplays"), 0x838);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnPlayerFromSimulate")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnPlayerFromSimulate"), 0x840);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("UpdatePlayerStartSpot")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("UpdatePlayerStartSpot"), 0x848);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ShouldStartInCinematicMode")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ShouldStartInCinematicMode"), 0x850);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("UpdateGameplayMuteList")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("UpdateGameplayMuteList"), 0x858);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitNewPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitNewPlayer"), 0x860);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("GenericPlayerInitialization")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("GenericPlayerInitialization"), 0x868);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ReplicateStreamingStatus")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ReplicateStreamingStatus"), 0x870);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ShouldSpawnAtStartSpot")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ShouldSpawnAtStartSpot"), 0x878);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("FinishRestartPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("FinishRestartPlayer"), 0x880);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("FailedToRestartPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("FailedToRestartPlayer"), 0x888);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ProcessClientTravel__Ref_FString__FGuid__bool__bool")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ProcessClientTravel__Ref_FString__FGuid__bool__bool"), 0x890);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("ProcessClientTravel__Ref_FString__bool__bool")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("ProcessClientTravel__Ref_FString__bool__bool"), 0x898);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("InitSeamlessTravelPlayer")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("InitSeamlessTravelPlayer"), 0x8A0);
}

if (auto it = AGameModeBase::VTableLayoutMap.find(STR("SpawnPlayerControllerCommon")); it == AGameModeBase::VTableLayoutMap.end())
{
    AGameModeBase::VTableLayoutMap.emplace(STR("SpawnPlayerControllerCommon"), 0x8A8);
}

