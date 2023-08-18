// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Blueprint/UserWidget.h"
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

	void OnResumeClicked();


	UPROPERTY()
	UImage* GunImage1;

	UPROPERTY()
	UImage* GunImage2;

	UPROPERTY()
	UImage* GunImage3;

	UPROPERTY()
	UButton* ItempButton1;

	UPROPERTY()
	UButton* ResumeButton;

};
