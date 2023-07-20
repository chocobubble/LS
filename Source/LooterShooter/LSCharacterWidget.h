// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSCharacterWidget.generated.h"

class ULSDefenseComponent;
class UProgressBar
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindCharacterStat(class ULSCharacterStatComponent* NewCharacterStat);
	void BindDefenseComonent(ULSDefenseComponent* DefenseManager);

private:
	TWeakObjectPtr<class ULSCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<ULSDefenseComponent> CurrentDefenseManager;

	UPROPERTY()
	UProgressBar* HPProgressBar;

	UPROPERTY()
	UProgressBar* ShieldProgressBar;

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
	void UpdateShieldWidget();
};
