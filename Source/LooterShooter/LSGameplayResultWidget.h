// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "LSGameplayWidget.h"
#include "LSGameplayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSGameplayResultWidget : public ULSGameplayWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
};
