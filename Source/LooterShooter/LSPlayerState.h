// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/PlayerState.h"
#include "LSPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ALSPlayerState();

	int32 GetCharacterLevel() const;
	FString SaveSlotName;

	int32 GetCurrentExp() const;
	int32 GetNextExp() const;
	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);

	void InitPlayerData();
	void SavePlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	UPROPERTY(Transient)
	int32 CurrentExp;

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FLSPlayerData* CurrentStatData;
};
