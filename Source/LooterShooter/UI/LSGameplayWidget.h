// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSGameplayWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnReturnToTitleClicked();
	
	UFUNCTION()
	void OnRetryGameClicked();

protected:
	UPROPERTY()
	UButton* ResumeButton;

	UPROPERTY()
	UButton* ReturnToTitleButton;

	UPROPERTY()
	UButton* RetryGameButton;
};
