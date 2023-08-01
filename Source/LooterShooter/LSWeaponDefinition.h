// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "UObject/NoExportTypes.h"
#include "LSWeaponInstance.h"
#include "LSGameInstance.h"
#include "LSGameState.h"

#include "LSWeaponDefinition.generated.h"

class ULSWeaponAbilityComponent;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSWeaponDefinition : public UObject
{
	GENERATED_BODY()

private:
	FLSWeaponBaseData* WeaponBaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 WeaponItemLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float FireRate = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 510.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float BulletDamage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float CriticalHitChance = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float CriticalHitMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float DamageReduceDistance = 1000.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float ReloadTime = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 BulletsPerCatridge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MaxRange = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MaxSpreadAngle  = 1.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MinSpreadAngle = 1.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float HeatPerShot = 0.1f;

public:
	UPROPERTY(VisibleAnywhere, Category = Ability)
	ULSWeaponAbilityComponent* WeaponAbilityComponent;

	UPROPERTY(EditInstanceOnly, Category = Weapon)
	TSubclassOf<ALSWeaponInstance> WeaponInstanceClass;

public:
	ULSWeaponDefinition();

	ALSWeaponInstance* InstantiateWeapon();
	void SetWeaponDefinitionData(EWeaponType WeaponTypeParam, int32 ItemLevel);
	void SetWeaponDefinitionStats();
	
	EWeaponType GetWeaponType() const
	{
		return WeaponType;
	}
	float GetMagazineCapacity() const
	{
		return MagazineCapacity;
	}
	float GetFireRate() const
	{
		return FireRate;
	}
	float GetMovementSpeed() const
	{
		return MovementSpeed;
	}
	float GetBulletDamage() const
	{
		return BulletDamage;
	}
	float GetCriticalHitChance() const
	{
		return CriticalHitChance;
	}
	float GetCriticalHitMultiplier() const
	{
		return CriticalHitMultiplier;
	}
	float GetDamageReduceDistance() const
	{
		return DamageReduceDistance;
	}
	float GetReloadTime() const
	{
		return ReloadTime;
	}
	int32 GetBulletsPerCatridge() const
	{
		return BulletsPerCatridge;
	}
	float GetMaxRange() const
	{
		return MaxRange;
	}
	float GetMaxSpreadAngle() const
	{
		return MaxSpreadAngle;
	}
	float GetMinSpreadAngle() const
	{
		return MinSpreadAngle;
	}
	float GetHeatPerShot() const
	{
		return HeatPerShot;
	}


	void SetBulletDamage(float Value)
	{
		BulletDamage = Value;
	}

};
