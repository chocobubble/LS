// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerState.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/GameMode/LSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "LooterShooter/Component/LSInventoryComponent.h"
#include "LooterShooter/Character/LSPlayerController.h"

ALSPlayerState::ALSPlayerState()
{
    SaveSlotName = TEXT("Player");
	CurrentAmmoMap.Add(EAmmoType::RIFLE, 0);
}

void ALSPlayerState::InitPlayerData()
{
    ULSSaveGame* LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    if (LSSaveGame == nullptr)
    {
        LSSaveGame = GetMutableDefault<ULSSaveGame>();
    }
    SetPlayerName(LSSaveGame->GetSavedPlayerName());
    SetCharacterLevel(LSSaveGame->GetSavedCharacterLevel());
    CurrentExp = LSSaveGame->GetSavedCharacterExp();
	CurrentGold = LSSaveGame->GetSavedGold();
	CurrentWeaponLevel = LSSaveGame->GetSavedWeaponLevel();
	CurrentWeaponEnhancementLevel = LSSaveGame->GetWeaponEnhancementLevel();
	CurrentAmmoMap[EAmmoType::RIFLE] = LSSaveGame->GetWeaponAmmoMap()[EAmmoType::RIFLE];

	UPORPERTY(VisibleAnywhere)
	ALSPlayerController* LSPlayerController;

	UPORPERTY(VisibleAnywhere)
	ULSInventoryComponent* LSInventory;

    SavePlayerData();
}

void ALSPlayerState::SavePlayerData()
{
    ULSSaveGame* NewPlayerData = NewObject<ULSSaveGame>();
    NewPlayerData->SavePlayerName(GetPlayerName());
    NewPlayerData->SaveCharacterLevel(CharacterLevel);
    NewPlayerData->SaveCharacterExp(CurrentExp);
	NewPlayerData->SaveGold(CurrentGold);
	NewPlayerData->SaveWeaponLevel(CurrentWeaponLevel);
	NewPlayerData->SaveWeaponEnhancementLevel(CurrentWeaponEnhancementLevel);
	NewPlayerData->SaveAmmoMap(CurrentAmmoMap);

    if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
    {
        LSLOG_S(Error);
    }
}

int32 ALSPlayerState::GetNextExp() 
{
	LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
	if (LSGameInstance)
	{
		PlayerStatData = LSGameInstance->GetLSPlayerData(CharacterLevel);
		if (PlayerStatData)
		{
			return PlayerStatData->NextExp;
		}
	}
	return -1;
}

float ALSPlayerState::GetExpRatio() 
{
    LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
	if (LSGameInstance)
	{
		PlayerStatData = LSGameInstance->GetLSPlayerData(CharacterLevel);
		if (PlayerStatData)
		{
			// 0 나눗셈 에러 방지
    		if (PlayerStatData->NextExp <= KINDA_SMALL_NUMBER)
   		 	{
   	    	 	return 0.0f;
	    	}
			return (float)CurrentExp / PlayerStatData->NextExp;
		}
	}
    return 0.0f;
}

bool ALSPlayerState::AddExp(int32 IncomeExp)
{
	LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
	if (LSGameInstance == nullptr)
	{
		return false;
	}
	PlayerStatData = LSGameInstance->GetLSPlayerData(CharacterLevel);
	if (PlayerStatData == nullptr || PlayerStatData->NextExp == -1)
	{
		return false;
	}

    bool bDidLevelUp = false;
    CurrentExp += IncomeExp;
    if (CurrentExp >= PlayerStatData->NextExp)
    {
        CurrentExp -= PlayerStatData->NextExp;
        SetCharacterLevel(CharacterLevel + 1);
        bDidLevelUp = true;
    }

    OnPlayerStateChanged.Broadcast();

    SavePlayerData();

    return bDidLevelUp;
}

void ALSPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
    LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
    if (LSGameInstance)
	{
		PlayerStatData = LSGameInstance->GetLSPlayerData(NewCharacterLevel);
	}
	CharacterLevel = NewCharacterLevel;
}

void ALSPlayerState::SetCurrentAmmo(EAmmoType AmmoType, int32 Amount)
{
	CurrentAmmoMap[AmmoType] = Amount;
}
