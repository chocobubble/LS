// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameMode.h"
#include "LSCharacter.h"
#include "LSPlayerController.h"
#include "LSPlayerState.h"
#include "LSGameState.h"
#include "LSPlayer.h"
#include "Engine/PawnIterator.h"

ALSGameMode::ALSGameMode()
{
    //DefaultPawnClass = ALSCharacter::StaticClass();
    DefaultPawnClass = ALSPlayer::StaticClass();
    PlayerControllerClass = ALSPlayerController::StaticClass();
    PlayerStateClass = ALSPlayerState::StaticClass();
    GameStateClass = ALSGameState::StaticClass();

    ScoreToClear = 2;
} 

void ALSGameMode::PostLogin(APlayerController * NewPlayer)
{
    LSLOG(Warning, TEXT("PostLogin Begin"));
    Super::PostLogin(NewPlayer);
    LSLOG(Warning, TEXT("PostLogin End"));

    ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(NewPlayer->PlayerState);
    LSCHECK(nullptr != LSPlayerState);
    
    LSPlayerState->InitPlayerData();
}

void ALSGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    LSGameState = Cast<ALSGameState>(GameState);
}

void ALSGameMode::AddScore(ALSPlayerController* ScoredPlayer)
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const auto LSPlayerController = Cast<ALSPlayerController>(It->Get());
        if ((nullptr != LSPlayerController) && (ScoredPlayer == LSPlayerController))
        {
            LSPlayerController->AddGameScore();
            break;
        }
    }

    LSGameState->AddGameScore();


    if (GetScore() >= ScoreToClear)
    {
        LSGameState->SetGameCleared();
        // #include "Engine/PawnIterator.h"
        for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
        {
            (*It)->TurnOff();
        }

        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            const auto LSPlayerController = Cast<ALSPlayerController>(It->Get());
            if (nullptr != LSPlayerController)
            {
                LSPlayerController->ShowResultUI();
            }
        }
    }
}

int32 ALSGameMode::GetScore() const
{
    return LSGameState->GetTotalGameScore();
}