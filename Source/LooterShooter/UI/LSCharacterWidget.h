// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSCharacterWidget.generated.h"

class ULSDefenseComponent;
class UProgressBar;
class UTextBlock;

/**
 * 캐릭터의 Health Bar 구현 클래스
 */
UCLASS()
class LOOTERSHOOTER_API ULSCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindDefenseComponent(ULSDefenseComponent* DefenseManager);

	void UpdateHPWidget();

	void UpdateShieldWidget();

	void SetMonsterLevel(int32 Level);

protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<ULSDefenseComponent> CurrentDefenseManager;

	UPROPERTY()
	UProgressBar* HPProgressBar;

	UPROPERTY()
	UProgressBar* ShieldProgressBar;

	UPROPERTY()
	UTextBlock* LevelText;

	UPROPERTY()
	int32 MonsterLevel;
};
