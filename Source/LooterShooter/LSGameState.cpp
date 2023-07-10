// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameState.h"

ALSGameState::ALSGameState()
{
    TotalGameScore = 0;
    
    // bGameCleared = false;
}

int32 ALSGameState::GetTotalGameScore() const
{
    return TotalGameScore;
}

void ALSGameState::AddGameScore()
{
    TotalGameScore++;
}
/*
void ALSGameState::SetGameCleared()
{
    bGameCleared = true;
}

bool ALSGameState::IsGameCleared() const
{
    return bGameCleared;
}
*/

