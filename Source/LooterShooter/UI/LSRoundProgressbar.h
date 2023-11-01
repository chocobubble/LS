// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Blueprint/UserWidget.h"
#include "LSRoundProgressbar.generated.h"

class UMaterialInstanceDynamic;
class UImage;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSRoundProgressbar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetPercentPB(float Percent);

	UFUNCTION()
	void StartReload(float GunReloadTime);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
////////Test////////
	UPROPERTY()
	float RoundPBPercent = 0.0f;

	UPROPERTY()
	float ReloadTime = 0.0f;

	UPROPERTY()
	float ElapsedTime = 0.0f;

	UPROPERTY()
	UImage* RoundPBImg;

	UPROPERTY()
	UMaterialInstanceDynamic* RoundPBInst;
};
