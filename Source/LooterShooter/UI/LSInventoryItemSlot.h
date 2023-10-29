// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
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
	virtual void NativeConstruct() override;
	UFUNCTION()
	void TurnOn();
	UFUNCTION()
	void Print();
	void Init(ULSWeaponDefinition* WeaponDefinition);

private:
	UPROPERTY()
	UBorder* SlotBorder;

	UPROPERTY()
	UButton* SlotButton;

	UPROPERTY()
	UImage* GunImage;

	UPROPERTY()
	bool bIsTurnedOn = false;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UMaterialInstance* MI_Rifle;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UMaterialInstance* MI_Shotgun;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UMaterialInstance* MI_Pistol;
};
