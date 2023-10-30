// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "LSPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

class ULSGameInstance;
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

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 GameScore = 0;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CharacterLevel = 1;

	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 CurrentExp = 0;

	//UPROPERTY(VisibleAnywhere, Category = "State")
	FLSPlayerData* PlayerStatData;

	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ULSGameInstance* LSGameInstance;

	UPROPERTY()
	FString SaveSlotName;

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

	float GetExpRatio();

	void SetCharacterLevel(int32 NewCharacterLevel);
};
