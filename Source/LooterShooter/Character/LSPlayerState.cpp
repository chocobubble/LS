// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerState.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/GameMode/LSSaveGame.h"
#include "Kismet/GameplayStatics.h"

ALSPlayerState::ALSPlayerState()
{
    CharacterLevel = 1;
    CurrentExp = 0;
    SaveSlotName = TEXT("Player");
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
    CurrentExp = LSSaveGame->Exp;

    SavePlayerData();
}

void ALSPlayerState::SavePlayerData()
{
    ULSSaveGame* NewPlayerData = NewObject<ULSSaveGame>();
    NewPlayerData->PlayerName = GetPlayerName();
    NewPlayerData->Level = CharacterLevel;
    NewPlayerData->Exp = CurrentExp;

    if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
    {
        LSLOG_S(Error);
    }
}


int32 ALSPlayerState::GetCurrentExp() const
{
    return CurrentExp;
}
int32 ALSPlayerState::GetNextExp() const
{
    LSCHECK(CurrentStatData != nullptr, -1);
    return CurrentStatData->NextExp;
}

float ALSPlayerState::GetExpRatio() const
{
    LSCHECK(nullptr != CurrentStatData, 0.0f);

    if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
    {
        return 0.0f;
    }

    float Result = (float) CurrentExp / (float)CurrentStatData->NextExp;
    LSLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, CurrentExp, CurrentStatData->NextExp);
    return Result;
}

bool ALSPlayerState::AddExp(int32 IncomeExp)
{
    if (CurrentStatData->NextExp == -1)
        return false;

    bool DidLevelUp = false;
    CurrentExp = CurrentExp + IncomeExp;
    if (CurrentExp >= CurrentStatData->NextExp)
    {
        CurrentExp -= CurrentStatData->NextExp;
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
    if (CurrentStatData == nullptr)
    {
        LSLOG(Warning, TEXT("CurrentStatData nullptr"));
    }
    else
    {
        LSLOG(Warning, TEXT("CurrentStatData->Level : %d"), CurrentStatData->Level);
    }
    CharacterLevel = NewCharacterLevel;
}
