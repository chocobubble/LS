// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameInstance.h"

ULSGameInstance::ULSGameInstance()
{
    LSLOG_S(Warning);

    //FString PlayerDataPath = TEXT("/Game/LS/GameData/PlayerBaseData.PlayerBaseData");
    //static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSPLAYER(*PlayerDataPath);
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSPLAYER(TEXT("/Game/LS/GameData/PlayerBaseData.PlayerBaseData"));
    LSCHECK(DT_LSPLAYER.Succeeded());
    LSPlayerTable = DT_LSPLAYER.Object;
    LSCHECK(LSPlayerTable->GetRowMap().Num() > 0);
    
    FString MonsterDataPath = TEXT("/Game/LS/GameData/MonsterBaseData.MonsterBaseData");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSMONSTER(*MonsterDataPath);
    //static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSCHARACTER(TEXT("/Script/Engine.DataTable'/Game/LS/GameData/LSCD.LSCD'"));
    LSCHECK(DT_LSMONSTER.Succeeded());
    LSMonsterTable = DT_LSMONSTER.Object;
    LSCHECK(LSMonsterTable->GetRowMap().Num() > 0);
    



}

void ULSGameInstance::Init()
{
    Super::Init();
    
}

FLSPlayerData* ULSGameInstance::GetLSPlayerData(int32 Level)
{
    if(LSPlayerTable == nullptr) 
    {
        LSLOG_S(Warning);
        return nullptr;
    }
    return LSPlayerTable->FindRow<FLSPlayerData>(*FString::FromInt(Level), TEXT(""));
}

FLSMonsterData* ULSGameInstance::GetLSMonsterData(int32 Level)
{
    if(LSMonsterTable == nullptr) 
    {
        LSLOG_S(Warning);
        return nullptr;
    }
    return LSMonsterTable->FindRow<FLSMonsterData>(*FString::FromInt(Level), TEXT(""));
}