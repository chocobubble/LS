// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/SaveGame.h"
#include "LooterShooter/Types/WeaponType.h"
#include "LooterShooter/Types/AmmoType.h"
#include "LSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	ULSSaveGame();

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 Exp = 0;

	UPROPERTY(VisibleAnywhere, Category = "State")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 Gold = 1000;

	// 무기 레벨, 무기 강화
	//UPROPERTY()
	TArray<TPair<int32, int32>> OwnedWeapons;

	//UPROPERTY(VisibleAnywhere, Category = "State")
	TMap<EAmmoType, int32> AmmoMap;

public:
	int32 GetSavedCharacterLevel() const
	{
		return Level;
	}

	int32 GetSavedCharacterExp() const
	{
		return Exp;
	}

	FString GetSavedPlayerName() const
	{
		return PlayerName;
	}

	int32 GetSavedGold() const
	{
		return Gold;
	}

	TArray<TPair<int32, int32>>& GetSavedOwnedWeapons()
	{
		return OwnedWeapons;
	}

	TMap<EAmmoType, int32> GetSavedAmmoMap() const
	{
		return AmmoMap;
	}

	void SaveCharacterLevel(int32 CurrentLevel)
	{
		Level = CurrentLevel;
	}

	void SaveCharacterExp(int32 CurrentExp)
	{
		Exp = CurrentExp;
	}

	void SavePlayerName(FString Name)
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

	void SaveOwnedWeapons(TArray<TPair<int32, int32>>& CurrentOwnedWeapons)
	{
		OwnedWeapons = CurrentOwnedWeapons;
	}
};
