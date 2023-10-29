// Fill out your copyright notice in the Description page of Project Settings.

#include "LSDefenseComponent.h"
#include "Engine/World.h"

ULSDefenseComponent::ULSDefenseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULSDefenseComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULSDefenseComponent::Init(int32 Level)
{
	
}

void ULSDefenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentShield == MaxShield || (GetWorld()->GetTimeSeconds() - LastHitTime) < ShieldRechargeDelay)
	{	
		return;
	}
	else
	{
		SetShield((CurrentShield + ShieldRechargeRate));
	}
}

void ULSDefenseComponent::SetMaxHP(float NewMaxHP)
{
	MaxHP = NewMaxHP;
	CurrentHP = NewMaxHP;	
}

void ULSDefenseComponent::SetMaxShield(float NewMaxShield)
{
	MaxShield = NewMaxShield;
	CurrentShield = NewMaxShield;
}

void ULSDefenseComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	if (CurrentHP > MaxHP)
	{
		CurrentHP = MaxHP;
	}
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void ULSDefenseComponent::SetShield(float NewShield)
{
	CurrentShield = NewShield;
	OnShieldChanged.Broadcast();
	if (CurrentShield < KINDA_SMALL_NUMBER)
	{
		CurrentShield = 0.0f;
	}
}

float ULSDefenseComponent::GetHPRatio() const
{
	return (CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP);
}

float ULSDefenseComponent::GetShieldRatio() const
{
	return (CurrentShield < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentShield / MaxShield);
}

float ULSDefenseComponent::GetCurrentHP() const
{
	return CurrentHP;
}

void ULSDefenseComponent::SetDamage(float NewDamage)
{
	LastHitTime = GetWorld()->GetTimeSeconds();
	if (CurrentShield > 0)
	{
		CurrentShield = FMath::Clamp<float>(CurrentShield - NewDamage, 0, MaxShield);
		SetShield(CurrentShield);
	}
	else
	{
		CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0, MaxHP);
		if (CurrentHP <= 0)
		{
			OnHPIsZero.Broadcast();
		}
		SetHP(CurrentHP);
	}
}