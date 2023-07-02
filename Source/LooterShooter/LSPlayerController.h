// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/PlayerController.h"
#include "LSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override; 
};
