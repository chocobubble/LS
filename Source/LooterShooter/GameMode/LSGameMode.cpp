// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameMode.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayerState.h"
#include "LSGameState.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "Engine/PawnIterator.h"

ALSGameMode::ALSGameMode()
{
    DefaultPawnClass = ALSPlayer::StaticClass();
    PlayerControllerClass = ALSPlayerController::StaticClass();
    PlayerStateClass = ALSPlayerState::StaticClass();
    GameStateClass = ALSGameState::StaticClass();
} 

void ALSGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    LSPlayerState = Cast<ALSPlayerState>(NewPlayer->PlayerState);
    if (LSPlayerState)
    {
        LSPlayerState->InitPlayerData();
    }
}

void ALSGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    LSGameState = Cast<ALSGameState>(GameState);
}
