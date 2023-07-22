// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
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


private:
	UPROPERTY()
	UTextBlock* PopUpText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float DisappearTimer = 1.f;
	
	FTimerHandle DestroyTimerHandle = { };

public:
	virtual void NativeConstruct() override;

	UTextBlock* GetPopUpTextBlock()
	{
		return PopUpText;
	}
};
