// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "LSInventoryItemButton.generated.h"

class ULSInventoryWidget;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSInventoryItemButton : public UButton
{
	GENERATED_BODY()

	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Selected();

	void Init(ULSInventoryWidget* Widget);

private:
	UPROPERTY(VisibleAnywhere, Category = "Button")
	bool bIsSelected;

	UPROPERTY(VisibleAnywhere)
	UButton* DefaultSelectedButton;
/*
	UPROPERTY(VisibleAnywhere)
	ULSInventoryWidget* InventoryWidget;
*/
};
