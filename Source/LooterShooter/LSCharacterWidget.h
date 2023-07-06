// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindCharacterStat(class ULSCharacterStatComponent* NewCharacterStat);

private:
	TWeakObjectPtr<class ULSCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

};
