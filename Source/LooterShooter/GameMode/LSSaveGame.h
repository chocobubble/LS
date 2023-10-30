// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/SaveGame.h"
#include "LooterShooter/Types/WeaponType.h"
#include "LooterShooter/Types/AmooType.h"
#include "LSSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSSaveGame : public USaveGame
{
	GENERATED_BODY()

	ULSSaveGame();

private:
	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 Gold;

	UPROPERTY()
	TMap<EAmmoType, int32> AmmoMap;

	UPROPERTY()
	int32 WeaponLevel;

	UPORPERTY()
	int32 WeaponEnhancementLevel;

public:
	int32 GetSavedCharacterLevel const
	{
		return Level;
	}

	int32 GetSavedCharacterExp const
	{
		return Exp;
	}

	FString GetSavedPlayerName const
	{
		return PlayerName;
	}

	int32 GetSavedGold const
	{
		return Gold;
	}

	TMap<EAmmoType, int32> GetSavedAmmoMap const
	{
		return AmmoMap;
	}

	int32 GetSavedWeaponLevel const
	{
		return WeaponLevel;
	}

	int32 GetSavedWeaponEnhancementLevel const
	{
		return WeaponEnhancementLevel;
	}

	void SaveCharacterLevel(int32 CurrentLevel)
	{
		Level = CurrentLevel;
	}

	void SaveCharacterExp(int32 CurrentExp)
	{
		Exp = CurrentExp;
	}

	void SavePlayerName(FString& Name)
	{
		PlayerName = Name;
	}

	void SaveGold(int32 CurrentGold)
	{
		Gold = CurrentGold;
	}

	void SaveAmmoMap(TMap<EAmmoType, int32>& CurrentAmmoMap)
	{
		AmmoMap = CurrentAmmoMap;
	}

	void SaveWeaponLevel(int32 CurrentWeaponLevel)
	{
		WeaponLevel = CurrentWeaponLevel;
	}

	void SaveWeaponEnhancementLevel(int32 CurrentWeaponEnhancementLevel)
	{
		WeaponEnhancementLevel = CurrentWeaponEnhancementLevel;
	}
};
