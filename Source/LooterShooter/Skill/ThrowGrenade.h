// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSSkill.h"
#include "ThrowGrenade.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API UThrowGrenade : public ULSSkill
{
	GENERATED_BODY()

public:
	UThrowGrenade();

	virtual void Tick(float DeltaTime) override;

	virtual void Init(APawn* Player) override;

	virtual bool CastSkill() override;
};
