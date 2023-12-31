// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "UI_Inventory.generated.h"

class UImage;
class UButton;
class UInventoryComponent;

/**
 * 인벤토리 UI 클래스
 */
UCLASS()
class LOOTERSHOOTER_API UUI_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


	UPROPERTY()
	UImage* GunImage1;

	UPROPERTY()
	UImage* GunImage2;

	UPROPERTY()
	UImage* GunImage3;

	UPROPERTY()
	UButton* ItempButton1;

};
