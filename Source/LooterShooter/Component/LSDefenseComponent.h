// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSDefenseComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnShieldChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMPChangedDelegate);

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
	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float MaxHP = 1000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float CurrentHP = 1000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float MaxMP = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float CurrentMP = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float MaxShield = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float CurrentShield = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float ShieldRechargeRate = 0.01f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float ShieldRechargeDelay = 2.0f;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	float LastHitTime = 0.0f;

public:
	void SetMaxHP(float NewMaxHP);

	void SetMaxShield(float NewMaxShield);

	void SetMaxMP(float NewMaxMP);

	void SetDamage(float NewDamage);

	void SetHP(float NewHP);

	void SetShield(float NewShield);

	void SetMP(float NewMP);

	float GetHPRatio() const
	{
		return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP);
	}

	float GetShieldRatio() const
	{
		return (MaxShield < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentShield / MaxShield);
	}

	float GetMPRatio() const
	{
		return (MaxMP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentMP / MaxMP);
	}

	float GetCurrentHP() const
	{
		return CurrentHP;
	}

	float GetCurrentMP() const
	{
		return CurrentMP;
	}
	
	FOnHPIsZeroDelegate OnHPIsZero;

	FOnHPChangedDelegate OnHPChanged;

	FOnShieldChangedDelegate OnShieldChanged;

	FOnMPChangedDelegate OnMPChanged;
};
