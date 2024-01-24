// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/PlayerController.h"
#include "LSTitleController.generated.h"

class ULSGameTitleWidget;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSTitleController : public APlayerController
{
	GENERATED_BODY()

public:
	ALSTitleController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<ULSGameTitleWidget> TitleWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	ULSGameTitleWidget* GameTitleWidget;
public:
};
