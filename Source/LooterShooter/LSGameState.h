// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
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

private:
	UPROPERTY(Transient)
	int32 TotalGameScore;
};
