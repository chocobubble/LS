// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "LSGameplayWidget.h"
#include "LSGameplayResultWidget.generated.h"

class ALSGameState;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSGameplayResultWidget : public ULSGameplayWidget
{
	GENERATED_BODY()


public:
	void BindGameState(ALSGameState* GameState);

protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<ALSGameState> CurrentGameState;
};
