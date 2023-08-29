// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSInventoryItemSlot.generated.h"

class UBorder;
class UButton;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void TurnOn();
	void Print();
	void Init();

private:
	UPROPERTY()
	UBorder* SlotBorder;

	UPROPERTY()
	UButton* SlotButton;
};
