// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSDefenseComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnShieldChangedDelegate);

/**
 * 캐릭터의 HP, Shield, MP, Defense 관리 컴포넌트
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSDefenseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULSDefenseComponent();

	void Init(int32 Level);
	
protected:
	virtual void BeginPlay() override;
	/** 
	 * 마지막 데미지 입은 시점으로 부터 ShieldRechargeDelay만큼의 시간이 지나면
	 * Shield가 충전되기 시작
	*/
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float MaxHP = 1000.f;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float CurrentHP = 1000.f;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float MaxMP;

	UPROPERTY(Transient, EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float CurrentMP = 0.f;

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
	void SetMaxHP(float NewMaxHP);
	void SetMaxShield(float NewMaxShield);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	void SetShield(float NewShield);
	float GetHPRatio() const;
	float GetShieldRatio() const;
	float GetCurrentHP() const;
	
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
	FOnShieldChangedDelegate OnShieldChanged;
};
