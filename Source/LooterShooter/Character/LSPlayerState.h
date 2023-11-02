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
class ULSResourceManageComponent;
class ULSWeaponDefinition;
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

	void BindWithResourceManager(ULSResourceManageComponent* Target);

	UFUNCTION()
	void UpdateResourceData();

	void UpdateOwnedWeaponData(int32 Idx, int32 WeaponLevel, int32 WeaponEnhancementLevel);

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

	// 무기 레벨, 무기 강화
	TArray<TPair<int32, int32>> CurrentOwnedWeapons;

	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ULSGameInstance* LSGameInstance;

	UPROPERTY(VisibleAnywhere)
	ALSPlayerController* LSPlayerController;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	ULSInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	ULSResourceManageComponent* ResourceManger;

	TMap<EAmmoType, int32> CurrentAmmoMap;

	FLSPlayerData* PlayerStatData;

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

	int32 GetCurrentGold() const
	{
		return CurrentGold;
	}

	TMap<EAmmoType, int32>& GetAmmoMap()
	{
		return CurrentAmmoMap;
	}

	TArray<TPair<int32, int32>>& GetOwnedWeapons()
	{
		return CurrentOwnedWeapons;
	}

	float GetExpRatio();

	void SetCharacterLevel(int32 NewCharacterLevel);

	void SetCurrentAmmo(EAmmoType AmmoType, int32 Amount);

};
