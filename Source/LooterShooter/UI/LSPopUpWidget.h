// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSPopUpWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSPopUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FTimerHandle DestroyTimerHandle = { };

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	UTextBlock* PopUpText;

	UPROPERTY()
	float DisappearTimer = 1.0f;
	
public:
	UTextBlock* GetPopUpTextBlock()
	{
		return PopUpText;
	}
};
