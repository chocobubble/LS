// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/PlayerController.h"
#include "LSUIPlayerController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSUIPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> UIWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UUserWidget* UIWidgetInstance;
};
