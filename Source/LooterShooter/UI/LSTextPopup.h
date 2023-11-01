// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
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

	void SetPopupText(int32 PopupText);

	void SetTextRotation(const FVector& FromVector, const FVector& ToVector);

	FTimerHandle DisappearTimerHandle = { };

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	float DisappearTimer = 1.0f;
};
