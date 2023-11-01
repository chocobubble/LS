// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "LSInventoryItemButton.generated.h"

class ULSInventoryWidget;
class ULSWeaponDefinition;
struct FButtonStyle;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSInventoryItemButton : public UButton
{
	GENERATED_BODY()

public:
	ULSInventoryItemButton();

	UFUNCTION()
	void Selected();

	void Init(const ULSInventoryWidget* Widget, ULSWeaponDefinition* WeaponDefinition);

private:
	UPROPERTY()
	bool bIsSelected = true;

	UPROPERTY()
	UButton* DefaultSelectedButton;
	
	UPROPERTY()
	ULSInventoryWidget* InventoryWidget;

	UPROPERTY()
	ULSWeaponDefinition* Weapon;
};
