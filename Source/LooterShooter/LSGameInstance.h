// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"

#include "LSGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FLSCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FLSCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
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
	FLSCharacterData* GetLSCharacterData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* LSCharacterTable;
};
