// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"
#include "LooterShooter/Interaction/LSAutoLootItem.h"

#include "LSGameInstance.generated.h"

// class UDataTable;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	RIFLE,
	PISTOL,
	SHOTGUN
};

USTRUCT(BlueprintType)
struct FLSWeaponBaseData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MagazineCapacity = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FireRate = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MovementSpeed = 510.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float BulletDamage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float CriticalHitChance = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float CriticalHitMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float DamageReduceDistance = 1000.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon)
	float ReloadTime = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 BulletsPerCatridge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MaxRange = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float MaxSpreadAngle  = 1.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Attack)
	float MinSpreadAngle = 1.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Attack)
	float HeatPerShot = 0.1f;
};

USTRUCT(BlueprintType)
struct FLSPlayerData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxShield = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxMP = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Defense = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeDelay = 3.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MasteryExp = 5;
};

USTRUCT(BlueprintType)
struct FLSMonsterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxShield = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Defense = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeDelay = 3.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp = 5;
};

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULSGameInstance();

	virtual void Init() override;
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

	void SpawnAutoLootItem(FVector SpawnLocation, ELootItemType LootedItemType, int32 Amount);

	FStreamableManager StreamableManager;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMesh* HPMesh;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMesh* MPMesh;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMesh* GoldMesh;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMesh* RifleAmmoMesh;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMesh* ShotgunAmmoMesh;
	
	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMesh* PistolAmmoMesh;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UMaterialInstance* MI_Rifle;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UMaterialInstance* MI_Shotgun;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UMaterialInstance* MI_Pistol;

private:
	UPROPERTY()
	UDataTable* LSPlayerTable;
	
	UPROPERTY()
	UDataTable* LSMonsterTable;

	UPROPERTY()
	UDataTable* LSRifleDataTable;

	UPROPERTY()
	UDataTable* LSShotgunDataTable;

	UPROPERTY()
	UDataTable* LSPistolDataTable;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMesh* RifleWeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMesh* ShotgunWeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMesh* PistolWeaponMesh;

	
};
