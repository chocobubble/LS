// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Engine/TextRenderActor.h"
#include "LSTextPopup.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSTextPopup : public ATextRenderActor
{
	GENERATED_BODY()

public:
	ALSTextPopup();	

	virtual void BeginPlay() override;

	void SetPopupText(int32 PopupText);

	void SetTextRotation(FVector FromVector, FVector ToVector);

	FTimerHandle DisappearTimerHandle = { };

private:
	UPROPERTY(EditAnywhere, Category = Popup)
	float DisappearTimer = 1.f;
};
