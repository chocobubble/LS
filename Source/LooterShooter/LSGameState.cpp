// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameState.h"

ALSGameState::ALSGameState()
{
    TotalGameScore = 0;
    
    bGameCleared = false;


    FString WeaponDataPath = TEXT("/Script/Engine.DataTable'/Game/LS/GameData/RifleBaseData.RifleBaseData'");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSWEAPON(*WeaponDataPath);
    // static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSCHARACTER(TEXT("/Script/Engine.DataTable'/Game/LS/GameData/LSCD.LSCD'"));
    LSCHECK(DT_LSWEAPON.Succeeded());
    LSWeaponDataTable = DT_LSWEAPON.Object;
    LSCHECK(LSWeaponDataTable->GetRowMap().Num() > 0);
}

int32 ALSGameState::GetTotalGameScore() const
{
    return TotalGameScore;
}

void ALSGameState::AddGameScore()
{
    TotalGameScore++;
}

void ALSGameState::SetGameCleared()
{
    bGameCleared = true;
}

bool ALSGameState::IsGameCleared() const
{
    return bGameCleared;
}


FLSWeaponBaseData* ALSGameState::GetLSWeaponData(int32 Level)
{
    if (LSWeaponDataTable == nullptr)
    {
        LSLOG_S(Warning);
        return nullptr;
    }
    return LSWeaponDataTable->FindRow<FLSWeaponBaseData>(*FString::FromInt(Level), TEXT(""));
}
