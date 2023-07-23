// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../LooterShooter.h"
#include "UObject/NoExportTypes.h"
#include "LSEquipmentFragment.generated.h"

class ALSWeaponInstance;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSEquipmentFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void EnhanceEquipment(ALSWeaponInstance* Weapon);
	virtual FString GetEnhancementText() const;
};
