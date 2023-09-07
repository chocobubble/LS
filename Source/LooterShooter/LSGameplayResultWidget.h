// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "LSGameplayWidget.h"
#include "LSGameplayResultWidget.generated.h"

class ALSGameState;
class ULSEnhanceWidget;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSGameplayResultWidget : public ULSGameplayWidget
{
	GENERATED_BODY()


public:
	void BindGameState(ALSGameState* GameState);
	void ShowEnhanceUI();

	UFUNCTION()
	void OnEnhanceClicked();

protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<ALSGameState> CurrentGameState;

	UPROPERTY()
	TSubclassOf<ULSEnhanceWidget> EnhanceWidgetClass;

	UPROPERTY()
	ULSEnhanceWidget* EnhanceWidget;

	UPROPERTY()
	UButton* EnhanceButton;
};
