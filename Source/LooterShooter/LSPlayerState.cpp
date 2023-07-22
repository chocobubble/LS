// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerState.h"
#include "LSGameInstance.h"
#include "LSSaveGame.h"
#include "Kismet/GameplayStatics.h"

ALSPlayerState::ALSPlayerState()
{
    CharacterLevel = 1;
    GameScore = 0;
    Exp = 0;
    GameHighScore = 0;
    SaveSlotName = TEXT("Player1");
/*
    CharacterIndex = 0;
*/
}

int32 ALSPlayerState::GetGameScore() const
{
    return GameScore;
}

int32 ALSPlayerState::GetCharacterLevel() const
{
    return CharacterLevel;
}

void ALSPlayerState::InitPlayerData()
{
    LSLOG_S(Warning);
    //	#include "Kismet/GameplayStatics.h"
    auto LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    if (nullptr == LSSaveGame)
    {
        LSLOG(Warning, TEXT("LSSaveGame is nullptr"));
        LSSaveGame = GetMutableDefault<ULSSaveGame>();
    }
    SetPlayerName(LSSaveGame->PlayerName);
    SetCharacterLevel(LSSaveGame->Level);
    GameScore = 0;
    GameHighScore = LSSaveGame->HighScore;
    Exp = LSSaveGame->Exp;
/*
    CharacterIndex = LSSaveGame->CharacterIndex;
*/
    SavePlayerData();

}

void ALSPlayerState::SavePlayerData()
{
    ULSSaveGame* NewPlayerData = NewObject<ULSSaveGame>();
    NewPlayerData->PlayerName = GetPlayerName();
    NewPlayerData->Level = CharacterLevel;
    NewPlayerData->Exp = Exp;
    NewPlayerData->HighScore = GameHighScore;
    // NewPlayerData->CharacterIndex = CharacterIndex;

    if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
    {
        LSLOG(Error, TEXT("SaveGame Error!"));
    }
}

float ALSPlayerState::GetExpRatio() const
{
    LSCHECK(nullptr != CurrentStatData, 0.0f);
    //LSCHECK(nullptr != CurrentStatData->NextExp, 0,0f);

    if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
    {
        return 0.0f;
    }

    float Result = (float) Exp / (float)CurrentStatData->NextExp;
    LSLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
    return Result;
}

bool ALSPlayerState::AddExp(int32 IncomeExp)
{
    if (CurrentStatData->NextExp == -1)
        return false;

    bool DidLevelUp = false;
    Exp = Exp + IncomeExp;
    if (Exp >= CurrentStatData->NextExp)
    {
        Exp -= CurrentStatData->NextExp;
        SetCharacterLevel(CharacterLevel + 1);
        DidLevelUp = true;
    }

    OnPlayerStateChanged.Broadcast();

    SavePlayerData();

    return DidLevelUp;
}

void ALSPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
    auto LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());
    LSCHECK(nullptr != LSGameInstance);

    CurrentStatData = LSGameInstance->GetLSPlayerData(NewCharacterLevel);
    LSCHECK(nullptr != CurrentStatData);
    if(CurrentStatData == nullptr)
    {
        LSLOG(Warning, TEXT("CurrentStatData nullptr"));
    }
    else
    {
        LSLOG(Warning, TEXT("CurrentStatData->Level : %d"), CurrentStatData->Level);
    }
    CharacterLevel = NewCharacterLevel;
}

void ALSPlayerState::AddGameScore()
{
    GameScore++;
    if (GameScore >= GameHighScore)
    {
        GameHighScore = GameScore;
    }
    OnPlayerStateChanged.Broadcast();
    SavePlayerData();
}

int32 ALSPlayerState::GetGameHighScore() const
{
    return GameHighScore;
}