// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/Types/AmmoType.h"
#include "GameFramework/PlayerState.h"
#include "LSPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

class ALSPlayerController;
class ULSInventoryComponent;
class ULSGameInstance;
struct FLSPlayerData;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ALSPlayerState();

	bool AddExp(int32 IncomeExp);

	void InitPlayerData();

	void SavePlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CharacterLevel = 1;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CurrentExp = 0;

	UPROPERTY(VisibleAnywhere, Category = "State")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CurrentGold = 1000;

	UPROPERTY(VisibleAnywhere, Category = "State")
	TMap<EAmmoType, int32> CurrentAmmoMap;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CurrentWeaponLevel = 1;

	UPORPERTY(VisibleAnywhere, Category = "State")
	int32 CurrentWeaponEnhancementLevel = 0;

	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ULSGameInstance* LSGameInstance;

	FLSPlayerData* PlayerStatData;

	UPORPERTY(VisibleAnywhere)
	ALSPlayerController* LSPlayerController;

	UPORPERTY(VisibleAnywhere)
	ULSInventoryComponent* LSInventory;

public:
	int32 GetCharacterLevel() const
	{
	    return CharacterLevel;	
	}

	int32 GetCurrentExp() const
	{
    	return CurrentExp;
	}

	int32 GetNextExp();

	float GetExpRatio();

	void SetCharacterLevel(int32 NewCharacterLevel);

	void SetCurrentAmmo(EAmmoType AmmoType, int32 Amount);

	void SetCurrentWeaponLevel(int32 WeaponLevel)
	{
		CurrentWeaponLevel = WeaponLevel;
	}

	void SetCurrentWeaponEnhancementLevel(int32 EnhancementLevel)
	{
		CurrentWeaponEnhancementLevel = EnhancementLevel;
	}
};
