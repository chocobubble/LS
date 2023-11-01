// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "LSInventoryWidget.generated.h"


class UImage;
class UButton;
class ULSInventoryComponent;
class ULSInventoryItemButton;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(ULSInventoryComponent* InventoryComponent);

	UFUNCTION()
	void OnInventoryItemClicked();

	UFUNCTION()
	void OnResumeClicked();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TArray<UImage*> GunImages;

	UPROPERTY()
	TArray<UImage*> EquippedGunImages;

	UPROPERTY()
	TArray<UButton*> EquippedGunButtons;

	UPROPERTY()
	TArray<UButton*> InventoryItemButtons;

	UPROPERTY()
	TArray<ULSInventoryItemButton*> LSInventoryItemButtons;

	UPROPERTY()
	UImage* GunImage1;

	UPROPERTY()
	UImage* GunImage2;

	UPROPERTY()
	UImage* GunImage3;

	UPROPERTY()
	UButton* ItemClickedButton;

	UPROPERTY()
	UButton* ResumeButton;

	UPROPERTY()
	ULSInventoryComponent* Inventory;
};
