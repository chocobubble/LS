// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LSRoundProgressbar.generated.h"

class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSRoundProgressbar : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
////////Test////////
	UPROPERTY(EditAnywhere)
	float RoundPBPercent;

	UFUNCTION(BlueprintCallable)
	void SetPercentPB(float Percent) { RoundPBPercent = Percent; }

	UPROPERTY()
	UMaterialInstanceDynamic* RoundPBInst;
};
