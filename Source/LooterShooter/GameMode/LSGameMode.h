// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/GameModeBase.h"

#include "LSGameMode.generated.h"

class ALSPlayerController;
class ALSGameState;
class ALSPlayerState;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALSGameMode();

protected:
	virtual void PostInitializeComponents() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ALSGameState* LSGameState;

	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ALSPlayerState* LSPlayerState;
};
