// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSSkill.h"
#include "GrapplingHook.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API UGrapplingHook : public ULSSkill
{
	GENERATED_BODY()

public:
	UGrapplingHook();

	virtual bool CastSkill() override;

	virtual void Init(APawn* Player) override;

	FTimerHandle ThrowTimerHandle = {};

protected:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "GrapplingHook")
	int32 RemainingHookCount = 2;

	
};
