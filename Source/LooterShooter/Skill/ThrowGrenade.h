// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSSkill.h"
#include "ThrowGrenade.generated.h"

class ALSGrenade;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API UThrowGrenade : public ULSSkill
{
	GENERATED_BODY()

public:
	UThrowGrenade();

	virtual bool CastSkill() override;

	virtual void Init(APawn* Player) override;

protected:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Grenade")
	TSubclassOf<ALSGrenade> LSGrenadeClass;

	UPROPERTY(VisibleAnywhere, Category = "Grenade")
	ALSGrenade* Grenade;
};
