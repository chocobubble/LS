// Fill out your copyright notice in the Description page of Project Settings.

#include "LSDefenseComponent.h"
#include "Engine/World.h"
// Sets default values for this component's properties
ULSDefenseComponent::ULSDefenseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULSDefenseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void ULSDefenseComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
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

// Called every frame
void ULSDefenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentShield == MaxShield || (GetWorld()->GetTimeSeconds() - LastHitTime) < ShieldRechargeDelay)
	{	
		return;
	}
	else
	{
		SetShield((CurrentShield + ShieldRechargeRate));
		// LSLOG(Warning, TEXT("Shield Recharging"));
	}
}