#pragma once

#include "Engine/DataTable.h"

#include "MonsterBaseData.generated.h"

USTRUCT(BlueprintType)
struct FLSMonsterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Data")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	float MaxHP = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	float MaxShield = 50.0f;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	float Defense = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	float ShieldRechargeRate = 0.1f;

	UPROPERTY(VisibleAnywhere, Category = "Data")
	float ShieldRechargeDelay = 3.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Data")
	int32 DropExp = 5;
};
