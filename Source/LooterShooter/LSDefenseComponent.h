// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSDefenseComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnShieldChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSDefenseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULSDefenseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// void SetNewLevel(int32 NewLevel);

	void SetDamage(float NewDamage);
	
	//float GetAttack();


	void SetHP(float NewHP);
	void SetShield(float NewShield);
	float GetHPRatio() const;
	float GetShieldRatio() const;

	
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
	FOnShieldChangedDelegate OnShieldChanged;

	

private:
	// struct FLSCharacterData* CurrentStatData = nullptr;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float MaxHP = 1000;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float CurrentHP = 1000;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float MaxMP;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float CurrentMP;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float MaxShield = 100.0f;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float CurrentShield = 100.0f;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float ShieldRechargeRate = 0.01f;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float ShieldRechargeDelay = 2.0f;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float LastHitTime = 0.0f;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
