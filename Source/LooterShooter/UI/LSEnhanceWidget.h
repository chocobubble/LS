// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSEnhanceWidget.generated.h"

class ULSWeaponDefinition;
class UButton;
class UTextBlock;
class ULSRoundProgressbar;
class UProgressBar;
class ULSResourceManageComponent;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSEnhanceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(ULSWeaponDefinition* WeaponDefinition, ULSResourceManageComponent* ResourceManager);
	
	UFUNCTION()
	void OnWeaponStatUpdated();

	UFUNCTION()
	void OnEnhanceButtonClicked();

	UFUNCTION()
	void Enhance();

	UFUNCTION()
	void OnResumeClicked();

	FTimerHandle EnhancementTimerHandle = {};

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;
	
private:
	UPROPERTY()
	UButton* EnhancementButton;

	UPROPERTY()
	UButton* BackButton;

	UPROPERTY()
	UTextBlock* GoldText;

	UPROPERTY()
	UTextBlock* EnhancementCountText;

	UPROPERTY()
	UTextBlock* WeaponTypeText;

	UPROPERTY()
	UTextBlock* DamageText;

	UPROPERTY()
	UTextBlock* CriticalHitChanceText;

	UPROPERTY()
	UTextBlock* CriticalHitMultiplierText;

	UPROPERTY()
	UTextBlock* EnhancementSuccessText;

	UPROPERTY()
	ULSWeaponDefinition* Weapon;

	UPROPERTY()
	ULSRoundProgressbar* LSEnhancePB;

	UPROPERTY()
	UProgressBar* EnhanceProgressBar;

	UPROPERTY()
	ULSResourceManageComponent* Resource;

	UPROPERTY()
	float ElapsedTime = 0.0f;

	UPROPERTY()
	float EnhancementTime = 2.0f;

	UPROPERTY()
	bool bIsEnhancing = false;

	UPROPERTY()
	bool bIsEnhanced = false;
};
