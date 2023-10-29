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

	ULSInventoryItemButton();
public:

	UFUNCTION()
	void Selected();

	void Init(const ULSInventoryWidget* Widget, ULSWeaponDefinition* WeaponDefinition);

private:
	UPROPERTY(VisibleAnywhere, Category = "Button")
	bool bIsSelected = true;

	UPROPERTY(VisibleAnywhere)
	UButton* DefaultSelectedButton = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	const ULSInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere)
	ULSWeaponDefinition* Weapon;
	//UPROPERTY(VisibleAnywhere)
	//FButtonStyle SelectedButtonStyle;

	/*
	UPROPERTY(VisibleAnywhere)
	ULSInventoryWidget* InventoryWidget;
*/
};
