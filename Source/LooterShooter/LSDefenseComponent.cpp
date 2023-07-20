// Fill out your copyright notice in the Description page of Project Settings.


#include "LSDefenseComponent.h"

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


// Called every frame
void ULSDefenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULSCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void ULSCharacterStatComponent::SetShield(float NewShield)
{
	CurrentShield = NewShield;
	OnShieldChanged.Broadcast();
	if (CurrentShield < KINDA_SMALL_NUMBER)
	{
		CurrentShield = 0.0f;
		// OnShieldIsZero.Broadcast();
	}
}

float ULSCharacterStatComponent::GetHPRatio()
{
	// LSCHECK(nullptr != CurrentStatData, 0.0f);

	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP);
}


float ULSCharacterStatComponent::GetShieldRatio()
{
	// LSCHECK(nullptr != CurrentStatData, 0.0f);

	return (MaxShield < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentShield / MaxShield);
}


