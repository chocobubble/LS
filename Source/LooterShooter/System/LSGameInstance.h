// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "LooterShooter/Interaction/LSAutoLootItem.h"
#include "LooterShooter/Data/WeaponBaseData.h"
#include "LooterShooter/Data/PlayerBaseData.h"
#include "LooterShooter/Data/MonsterBaseData.h"
#include "LooterShooter/Types/WeaponType.h"
#include "LSGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULSGameInstance();

	void SpawnAutoLootItem(FVector SpawnLocation, ELootItemType LootedItemType, int32 Amount);

	FStreamableManager StreamableManager;

protected:
	virtual void Init() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UStaticMesh* HPMesh;

	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UStaticMesh* MPMesh;

	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UStaticMesh* GoldMesh;

	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UStaticMesh* RifleAmmoMesh;

	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UStaticMesh* ShotgunAmmoMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UStaticMesh* PistolAmmoMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UMaterialInstance* MI_Rifle;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UMaterialInstance* MI_Shotgun;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UMaterialInstance* MI_Pistol;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	UDataTable* LSPlayerTable;
	
	UPROPERTY(VisibleAnywhere, Category = "Data")
	UDataTable* LSMonsterTable;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	UDataTable* LSRifleDataTable;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	UDataTable* LSShotgunDataTable;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	UDataTable* LSPistolDataTable;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMesh* RifleWeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMesh* ShotgunWeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMesh* PistolWeaponMesh;

public:
	FLSPlayerData* GetLSPlayerData(int32 Level);

	FLSMonsterData* GetLSMonsterData(int32 Level);

	FLSWeaponBaseData* GetWeaponData(EWeaponType WeaponType, int32 ItemLevel);

	USkeletalMesh* GetRifleMesh() const
	{
		return RifleWeaponMesh;
	}

	USkeletalMesh* GetShotgunMesh() const
	{
		return ShotgunWeaponMesh;
	}

	USkeletalMesh* GetPistolMesh() const
	{
		return PistolWeaponMesh;
	}

	UMaterialInstance* GetMIRifle() const
	{
		return MI_Rifle;
	}
};
