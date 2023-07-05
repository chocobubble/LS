// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameInstance.h"

ULSGameInstance::ULSGameInstance()
{
    FString CharacterDataPath = TEXT("/Script/Engine.DataTable'/Game/LS/GameData/LSCharacterData.LSCharacterData'");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSCHARACTER(*CharacterDataPath);
    //static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSCHARACTER(TEXT("/Script/Engine.DataTable'/Game/LS/GameData/LSCD.LSCD'"));
    LSCHECK(DT_LSCHARACTER.Succeeded());
    LSCharacterTable = DT_LSCHARACTER.Object;
    LSCHECK(LSCharacterTable->GetRowMap().Num() > 0);
}

void ULSGameInstance::Init()
{
    Super::Init();
    
}

FLSCharacterData* ULSGameInstance::GetLSCharacterData(int32 Level)
{
    if(LSCharacterTable == nullptr) 
    {
        LSLOG_S(Warning);
        return nullptr;
    }
    return LSCharacterTable->FindRow<FLSCharacterData>(*FString::FromInt(Level), TEXT(""));
}