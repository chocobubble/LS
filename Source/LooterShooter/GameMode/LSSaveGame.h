// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/SaveGame.h"
#include "LooterShooter/Data/WeaponSaveData.h"
#include "LooterShooter/Types/AmmoType.h"
#include "LSSaveGame.generated.h"
/**
USTRUCT(BlueprintType)
struct FWeaponSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	EWeaponType WeaponType;

	UPROPERTY()
	int32 WeaponLevel;

	UPROPERTY()
	int32 EnhancementLevel;
};


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
	//TArray<TPair<int32, int32>> OwnedWeapons;

	UPROPERTY()
	FWeaponSaveData FirstWeaponData;

	UPROPERTY()
	int32 RifleAmmo = 150;

	TMap<EAmmoType, int32> AmmoMap;

	TArray<FWeaponSaveData*> SavedWeapons;

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

	TArray<FWeaponSaveData*>& GetSavedOwnedWeapons()
	//TArray<TSharedPtr<FWeaponSaveData>>& GetSavedOwnedWeapons()
	{
		return SavedWeapons;
		//return OwnedWeapons;
	}

	TMap<EAmmoType, int32>& GetSavedAmmoMap();

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

	void SaveAmmoMap(TMap<EAmmoType, int32>& CurrentAmmoMap);

	//void SaveOwnedWeapons(TArray<TPair<int32, int32>>& CurrentOwnedWeapons)
	//void SaveOwnedWeapons(const TArray<TSharedPtr<FWeaponSaveData>>* CurrentOwnedWeapons)
	//{
		/*
		for (int32 Index = 0; Index < OwnedWeapons.Num(); ++Index)
		{
			OwnedWeapons[Index]->SetWeaponLevel(CurrentOwnedWeapons[Index]->GetWeaponLevel());
			OwnedWeapons[Index]->SetEnhancementLevel(*CurrentOwnedWeapons[Index]->GetEnhancementLevel());
		}*/
	//}
	void SaveOwnedWeapons(TArray<FWeaponSaveData*>& CurrentOwnedWeapons);
};
