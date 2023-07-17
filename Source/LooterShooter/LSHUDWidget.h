// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSHUDWidget.generated.h"

class ULSCharacterStatComponent;
class ALSPlayerState;
class UProgressBar;
class UTextBlock;

class ULSResourceManageComponent;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(ULSCharacterStatComponent* CharacterStat);
	void BindPlayerState(ALSPlayerState* PlayerState);
	void BindResourceManageComponent(ULSResourceManageComponent* ResourceManageComponent);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

	void UpdateResource();

private:
	TWeakObjectPtr<ULSCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<ALSPlayerState> CurrentPlayerState;

	
	TWeakObjectPtr<ULSResourceManageComponent> CurrentResourceManageComponent;

	UPROPERTY()
	UProgressBar* HPBar;

	UPROPERTY()
	UProgressBar* ExpBar;

	UPROPERTY()
	UTextBlock* PlayerName;

	UPROPERTY()
	UTextBlock* PlayerLevel;

	UPROPERTY()
	UTextBlock* CurrentScore;

	UPROPERTY()
	UTextBlock* HighScore;


	UPROPERTY()
	UTextBlock* CurrentAmmo;

	UPROPERTY()
	UTextBlock* MaxAmmo;
};
