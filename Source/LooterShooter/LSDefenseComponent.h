// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LSDefenseComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);


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
	void SetNewLevel(int32 NewLevel);

	void SetDamage(float NewDamage);
	float GetAttack();


	void SetHP(float NewHP);
	float GetHPRatio();

	int32 GetDropExp() const;
	
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;

	

private:
	struct FLSCharacterData* CurrentStatData = nullptr;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHP = 1000;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentHP = 1000;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxMP;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentMP;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxShield = 100;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentShield = 100;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float ShieldRechargeRate = 5.0f;

	UPROPERTY(Transient, EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float ShieldRechargeDelay = 2.0f;

	/*
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/**/
};
