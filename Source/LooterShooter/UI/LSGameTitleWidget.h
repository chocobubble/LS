// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LSGameTitleWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSGameTitleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnCreateAccountClicked();

	UFUNCTION()
	void OnLoginClicked();

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnSaveClicked();

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	UButton* NewGameButton;

	UPROPERTY()
	UButton* CreateAccountButton;

	UPROPERTY()
	UButton* LoginButton;

	UPROPERTY()
	UButton* SaveButton;

	UPROPERTY()
	UButton* LoadButton;
};
