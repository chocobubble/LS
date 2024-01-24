// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/Types/AmmoType.h"
#include "LooterShooter/Data/WeaponSaveData.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "LSPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

class ALSPlayerController;
class ULSInventoryComponent;
class ULSGameInstance;
class ULSResourceManageComponent;
class ULSWeaponDefinition;
class AHttpActor;
class ULSSaveGame;
struct FLSPlayerData;
struct FServerSaveData;
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

	void SaveSessionId();

	void CreateNewSaveData();

	void InitPlayerData();

	void SavePlayerData();

	void BindWithResourceManager(ULSResourceManageComponent* Target);

	UFUNCTION()
	void UpdateResourceData();

	void UpdateOwnedWeaponData();

	UFUNCTION()
	void SaveDataToServer();//(const FString& SlotName, const int32 UserIndex, bool Value);


	UFUNCTION()
	void DataLoadRequestToServer();

	UFUNCTION()
	void LoadDataFromServer(const FServerSaveData& LoadData);

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	virtual void BeginPlay();

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CharacterLevel = 1;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CurrentExp = 0;

	UPROPERTY(VisibleAnywhere, Category = "State")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CurrentGold = 1000;

	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ULSGameInstance* LSGameInstance;

	UPROPERTY(VisibleAnywhere)
	ALSPlayerController* LSPlayerController;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	ULSInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	ULSResourceManageComponent* ResourceManger;

	TMap<EAmmoType, int32> CurrentAmmoMap;

	TArray<FWeaponSaveData> CurrentOwnedWeapons;

	FLSPlayerData* PlayerStatData;

	FAsyncSaveGameToSlotDelegate SavedDelegate;

	UPROPERTY()
	AHttpActor* HttpActor;

	UPROPERTY(VisibleAnywhere, Category = "Network")
	FString SessionId = "Default";

	UPROPERTY(VisibleAnywhere, Category = "Network")
	bool IsLogin = true;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	ULSSaveGame* LSSaveGame;

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

	TArray<FWeaponSaveData>& GetOwnedWeapons()
	{
		return CurrentOwnedWeapons;
	}

	const FString& GetSessionId() const
	{
		return SessionId;
	}

	float GetExpRatio();

	void SetCharacterLevel(int32 NewCharacterLevel);

	void SetCurrentAmmo(const TMap<EAmmoType, int32>& AmmoMap);

	AHttpActor* GetHttpActor()
	{
		return HttpActor;
	}
};
