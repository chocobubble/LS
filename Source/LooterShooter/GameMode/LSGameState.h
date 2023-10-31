// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/GameStateBase.h"
#include "LSGameState.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ALSGameState();

public:
	int32 GetTotalGameScore() const;

	void AddGameScore();

	void SetGameCleared();

	bool IsGameCleared() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	int32 TotalGameScore;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool bGameCleared;
};
