// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
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
class ULSSkillComponent;
class UImage;

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

	void BindSkillComponent(ULSSkillComponent* SkillComponent);

	void BindPlayer(ALSPlayer* LSPlayer);
	
	void UpdateCharacterStat();

	void UpdateCurrentHP();

	void UpdateCurrentShield();

	void UpdateCurrentMP();

	void UpdatePlayerState();

	void UpdateFirstSkillCool(float CoolRate);

	void UpdateRoundsRemaining(int32 CurrentWeaponIndex);

	void UpdateCurrentAmmo();

	void UpdateInteractProgress(float ElapsedRatio);

	void ShowOrHideInteractPopup(bool Value);

	void ShowReloadProgressbar(float ReloadTime);

	void DrawCrosshairs();

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	TWeakObjectPtr<ULSCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	TWeakObjectPtr<ULSDefenseComponent> CurrentDefenseManager;

	UPROPERTY()
	TWeakObjectPtr<ALSPlayerState> CurrentPlayerState;

	UPROPERTY()
	TWeakObjectPtr<ULSEquipmentComponent> CurrentEquipmentComponent;

	UPROPERTY()
	TWeakObjectPtr<ALSPlayer> CurrentLSPlayer;

	UPROPERTY()
	TWeakObjectPtr<ULSResourceManageComponent> CurrentResourceManager;

	UPROPERTY()
	TWeakObjectPtr<ULSSkillComponent> CurrentSkillComponent;

	UPROPERTY()
	UProgressBar* HPBar;

	UPROPERTY()
	UProgressBar* ExpBar;

	UPROPERTY()
	UProgressBar* ShieldBar;

	UPROPERTY()
	UProgressBar* MPBar;

	UPROPERTY()
	UProgressBar* InteractionProgressBar;

	UPROPERTY()
	UProgressBar* FirstSkillProgressBar;

	UPROPERTY()
	ULSRoundProgressbar* ReloadProgressbar;

	UPROPERTY()
	UVerticalBox* InteractBox;

	UPROPERTY()
	USizeBox* ReloadBox;

	UPROPERTY()
	UTextBlock* PlayerNameText;

	UPROPERTY()
	UTextBlock* PlayerLevelText;

	UPROPERTY()
	UTextBlock* CurrentExpText;

	UPROPERTY()
	UTextBlock* NextExpText;

	UPROPERTY()
	UTextBlock* FirstWeaponCurrentAmmoText;

	UPROPERTY()
	UTextBlock* FirstWeaponRoundsRemainingText;

	UPROPERTY()
	UTextBlock* SecondWeaponCurrentAmmoText;

	UPROPERTY()
	UTextBlock* SecondWeaponRoundsRemainingText;

	UPROPERTY()
	UTextBlock* ThirdWeaponCurrentAmmoText;

	UPROPERTY()
	UTextBlock* ThirdWeaponRoundsRemainingText;

	UPROPERTY()
	ULSInventoryItemSlot* ItemSlot;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TArray<UTextBlock*> RoundsRemainingTextList;

	UPROPERTY()
	UImage* CrosshairCenter;

	UPROPERTY()
	UImage* CrosshairLeft;

	UPROPERTY()
	UImage* CrosshairRight;

	UPROPERTY()
	UImage* CrosshairTop;

	UPROPERTY()
	UImage* CrosshairBottom;
};
