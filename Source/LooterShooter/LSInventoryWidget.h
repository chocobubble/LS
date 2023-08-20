// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "LSInventoryWidget.generated.h"


class UImage;
class UButton;
class UInventoryComponent;


/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnInventoryItemClicked();

	UFUNCTION()
	void OnResumeClicked();

	UPROPERTY(VisibleAnywhere)
	TArray<UImage*> GunImages;

	UPROPERTY(VisibleAnywhere)
	TArray<UImage*> EquippedGunImages;

	UPROPERTY(VisibleAnywhere)
	TArray<UButton*> EquippedGunButtons;

	UPROPERTY(VisibleAnywhere)
	TArray<UButton*> InventoryItemButtons;

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

/*
	struct FSlateColor* Yel;
    struct FSlateBrush tempBrush;
*/
};
