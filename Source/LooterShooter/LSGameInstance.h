// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"

#include "LSGameInstance.generated.h"

// class UDataTable;

USTRUCT(BlueprintType)
struct FLSPlayerData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLSPlayerData() : 
		Level(1), MaxHP(100.0f), MaxShield(50.f), MaxMP(1.f), Defense(1.f),
		ShieldRechargeRate(0.1f), ShieldRechargeDelay(3.f), NextExp(5), MasteryExp(1) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeDelay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MasteryExp;
};

USTRUCT(BlueprintType)
struct FLSMonsterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLSMonsterData() : 
		Level(1), MaxHP(100.0f), MaxShield(50.f), Defense(1.f),
		ShieldRechargeRate(0.1f), ShieldRechargeDelay(3.f), DropExp(5) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ShieldRechargeDelay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;
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

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
	UDataTable* LSPlayerTable;
	
	UPROPERTY()
	UDataTable* LSMonsterTable;

};
