// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSHUDWidget.generated.h"

class ULSCharacterStatComponent;
class ALSPlayerState;
class UProgressBar;
class UTextBlock;
class UVerticalBox;
class USizeBox;
class ULSResourceManageComponent;
class ULSDefenseComponent;
class ULSEquipmentComponent;
class ALSPlayer;
class ULSDefenseComponent;
class ULSRoundProgressbar;
class ULSInventoryItemSlot;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(ULSCharacterStatComponent* CharacterStat);
	void BindDefenseComponent(ULSDefenseComponent* DefenseManager);
	void BindPlayerState(ALSPlayerState* PlayerState);
	void BindResourceManageComponent(ULSResourceManageComponent* ResourceManager);
	void BindEquipmentComponent(ULSEquipmentComponent* EquipmentComponent);
	void BindPlayer(ALSPlayer* LSPlayer);
	// void BindDefenseComponent(ULSDefenseComponent* DefenseManager);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdateCurrentHP();
	void UpdateCurrentShield();
	void UpdatePlayerState();
	void UpdateRoundsRemaining(int32 CurrentWeaponIndex);
	void UpdateCurrentAmmo();
	void UpdateInteractProgress(float ElapsedRatio);
	void ShowOrHideInteractPopup(bool Value);
	void ShowReloadProgressbar(float ReloadTime);

private:
	TWeakObjectPtr<ULSCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<ULSDefenseComponent> CurrentDefenseManager;
	TWeakObjectPtr<ALSPlayerState> CurrentPlayerState;
	TWeakObjectPtr<ULSEquipmentComponent> CurrentEquipmentComponent;
	TWeakObjectPtr<ALSPlayer> CurrentLSPlayer;
	TWeakObjectPtr<ULSResourceManageComponent> CurrentResourceManager;
	// TWeakObjectPtr<ULSDefenseComponent> DefenseManager;

	UPROPERTY()
	UProgressBar* HPBar;

	UPROPERTY()
	UProgressBar* ExpBar;

	UPROPERTY()
	UProgressBar* ShieldBar;

	UPROPERTY()
	UProgressBar* InteractionProgressBar;

	UPROPERTY()
	ULSRoundProgressbar* ReloadProgressbar;

	UPROPERTY()
	UVerticalBox* InteractBox;

	UPROPERTY()
	USizeBox* ReloadBox;

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
	ULSInventoryItemSlot* ItemSlot;



public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	TArray<UTextBlock*> RoundsRemainingTextList;
};
