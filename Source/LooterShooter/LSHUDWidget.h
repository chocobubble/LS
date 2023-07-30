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
class ULSDefenseComponent;
class ULSEquipmentComponent;

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
	void BindResourceManageComponent(ULSResourceManageComponent* ResourceManager);
	void BindEquipmentComponent(ULSEquipmentComponent* EquipmentComponent);
	// void BindDefenseComponent(ULSDefenseComponent* DefenseManager);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

	void UpdateRoundsRemaining(int32 CurrentWeaponIndex);
	void UpdateCurrentAmmo();

private:
	TWeakObjectPtr<ULSCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<ALSPlayerState> CurrentPlayerState;
	TWeakObjectPtr<ULSEquipmentComponent> CurrentEquipmentComponent;
	
	TWeakObjectPtr<ULSResourceManageComponent> CurrentResourceManager;
	// TWeakObjectPtr<ULSDefenseComponent> DefenseManager;

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
	UTextBlock* FirstWeaponCurrentAmmo;

	UPROPERTY()
	UTextBlock* FirstWeaponRoundsRemaining;

	UPROPERTY()
	UTextBlock* SecondWeaponCurrentAmmo;

	UPROPERTY()
	UTextBlock* SecondWeaponRoundsRemaining;

	UPROPERTY()
	UTextBlock* ThirdWeaponCurrentAmmo;

	UPROPERTY()
	UTextBlock* ThirdWeaponRoundsRemaining;


	UPROPERTY()
	UProgressBar* ShieldBar;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	TArray<UTextBlock*> RoundsRemainingTextList;
};
