#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#include "LooterShooter/Types/WeaponType.h"
#include "WeaponSaveData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FWeaponSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	EWeaponType WeaponType = EWeaponType::EWT_Rifle;

	UPROPERTY()
	int32 WeaponLevel = 2;

	UPROPERTY()
	int32 EnhancementLevel = 2;

public:
	EWeaponType GetWeaponType() const
	{
		return WeaponType;
	}

	int32 GetWeaponLevel() const
	{
		return WeaponLevel;
	}

	int32 GetEnhancementLevel() const
	{
		return EnhancementLevel;
	}

	void SetWeaponLevel(int32 Level)
	{
		WeaponLevel = Level;
	}

	void SetEnhancementLevel(int32 Level)
	{
		EnhancementLevel = Level;
	}
};
