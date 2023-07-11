// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/GameModeBase.h"

#include "LSGameMode.generated.h"

class ALSPlayerController;
class ALSGameState;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALSGameMode();

	//int32 GetScore() const;

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void AddScore(ALSPlayerController* ScoredPlayer);
	int32 GetScore() const;
private:
	UPROPERTY()
	ALSGameState* LSGameState;
};
