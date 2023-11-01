// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSInventoryItemSlot.generated.h"

class UBorder;
class UButton;
class ULSWeaponDefinition;
class UImage;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void TurnOn();

	UFUNCTION()
	void Print();

	void Init(ULSWeaponDefinition* WeaponDefinition);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	UBorder* SlotBorder;

	UPROPERTY()
	UButton* SlotButton;

	UPROPERTY()
	UImage* GunImage;

	UPROPERTY()
	bool bIsTurnedOn = false;

	UPROPERTY()
	UMaterialInstance* MI_Rifle;

	UPROPERTY()
	UMaterialInstance* MI_Shotgun;

	UPROPERTY()
	UMaterialInstance* MI_Pistol;
};
