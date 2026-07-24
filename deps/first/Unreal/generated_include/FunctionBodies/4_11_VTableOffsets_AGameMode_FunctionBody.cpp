if (auto it = AGameMode::VTableLayoutMap.find(STR("__vecDelDtor")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("PlayerCanRestart_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("PlayerCanRestart_Implementation"), 0x588);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ChoosePlayerStart_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ChoosePlayerStart_Implementation"), 0x590);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("FindPlayerStart_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("FindPlayerStart_Implementation"), 0x598);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("CanSpectate_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("CanSpectate_Implementation"), 0x5A0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SpawnDefaultPawnFor_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SpawnDefaultPawnFor_Implementation"), 0x5A8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("InitStartSpot_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("InitStartSpot_Implementation"), 0x5B0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetDefaultPawnClassForController_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetDefaultPawnClassForController_Implementation"), 0x5B8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("MustSpectate_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("MustSpectate_Implementation"), 0x5C0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ShouldReset_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ShouldReset_Implementation"), 0x5C8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ReadyToEndMatch_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ReadyToEndMatch_Implementation"), 0x5D0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ReadyToStartMatch_Implementation")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ReadyToStartMatch_Implementation"), 0x5D8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HasMatchStarted")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HasMatchStarted"), 0x5E0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("IsMatchInProgress")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("IsMatchInProgress"), 0x5E8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HasMatchEnded")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HasMatchEnded"), 0x5F0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("StartPlay")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("StartPlay"), 0x5F8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("PostSeamlessTravel")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("PostSeamlessTravel"), 0x600);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("StartMatch")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("StartMatch"), 0x608);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("EndMatch")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("EndMatch"), 0x610);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("StartToLeaveMap")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("StartToLeaveMap"), 0x618);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("RestartGame")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("RestartGame"), 0x620);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ReturnToMainMenuHost")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ReturnToMainMenuHost"), 0x628);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("AbortMatch")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("AbortMatch"), 0x630);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SetMatchState")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SetMatchState"), 0x638);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HandleMatchIsWaitingToStart")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HandleMatchIsWaitingToStart"), 0x640);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HandleMatchHasStarted")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HandleMatchHasStarted"), 0x648);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HandleMatchHasEnded")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HandleMatchHasEnded"), 0x650);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HandleLeavingMap")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HandleLeavingMap"), 0x658);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HandleMatchAborted")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HandleMatchAborted"), 0x660);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SetBandwidthLimit")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SetBandwidthLimit"), 0x668);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ResetLevel")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ResetLevel"), 0x670);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("InitGame")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("InitGame"), 0x678);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("InitGameState")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("InitGameState"), 0x680);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetNetworkNumber")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetNetworkNumber"), 0x688);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetNumPlayers")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetNumPlayers"), 0x690);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SetPause")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SetPause"), 0x698);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ClearPause")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ClearPause"), 0x6A0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetDefaultGameClassPath")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetDefaultGameClassPath"), 0x6A8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetGameModeClass")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetGameModeClass"), 0x6B0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetGameSessionClass")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetGameSessionClass"), 0x6B8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("NotifyPendingConnectionLost")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("NotifyPendingConnectionLost"), 0x6C0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetTravelType")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetTravelType"), 0x6C8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ProcessServerTravel")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ProcessServerTravel"), 0x6D0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ProcessClientTravel")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ProcessClientTravel"), 0x6D8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("PreLogin")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("PreLogin"), 0x6E0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("Login")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("Login"), 0x6E8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("PostLogin")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("PostLogin"), 0x6F0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SpawnPlayerController")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SpawnPlayerController"), 0x6F8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ReplicateStreamingStatus")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ReplicateStreamingStatus"), 0x700);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GenericPlayerInitialization")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GenericPlayerInitialization"), 0x708);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("StartNewPlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("StartNewPlayer"), 0x710);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("Logout")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("Logout"), 0x718);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SetPlayerDefaults")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SetPlayerDefaults"), 0x720);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ChangeName")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ChangeName"), 0x728);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SendPlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SendPlayer"), 0x730);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("Broadcast")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("Broadcast"), 0x738);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("BroadcastLocalized")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("BroadcastLocalized"), 0x740);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("ShouldSpawnAtStartSpot")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("ShouldSpawnAtStartSpot"), 0x748);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("UpdateGameplayMuteList")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("UpdateGameplayMuteList"), 0x750);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("AllowCheats")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("AllowCheats"), 0x758);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("AllowPausing")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("AllowPausing"), 0x760);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("PreCommitMapChange")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("PreCommitMapChange"), 0x768);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("PostCommitMapChange")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("PostCommitMapChange"), 0x770);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("AddInactivePlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("AddInactivePlayer"), 0x778);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("FindInactivePlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("FindInactivePlayer"), 0x780);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("OverridePlayerState")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("OverridePlayerState"), 0x788);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetSeamlessTravelActorList")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetSeamlessTravelActorList"), 0x790);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GetRedirectURL")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GetRedirectURL"), 0x798);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("GameWelcomePlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("GameWelcomePlayer"), 0x7A0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SwapPlayerControllers")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SwapPlayerControllers"), 0x7A8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("HandleSeamlessTravelPlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("HandleSeamlessTravelPlayer"), 0x7B0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("SetSeamlessTravelViewTarget")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("SetSeamlessTravelViewTarget"), 0x7B8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("MatineeCancelled")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("MatineeCancelled"), 0x7C0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("RestartPlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("RestartPlayer"), 0x7C8);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("IsHandlingReplays")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("IsHandlingReplays"), 0x7D0);
}

if (auto it = AGameMode::VTableLayoutMap.find(STR("InitNewPlayer")); it == AGameMode::VTableLayoutMap.end())
{
    AGameMode::VTableLayoutMap.emplace(STR("InitNewPlayer"), 0x7D8);
}

