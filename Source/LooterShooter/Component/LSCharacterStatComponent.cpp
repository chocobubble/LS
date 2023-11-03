// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacterStatComponent.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "Kismet/GameplayStatics.h"

ULSCharacterStatComponent::ULSCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false; 

	bWantsInitializeComponent = true;
	Level = 1;
}

void ULSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetNewLevel(Level);
}

void ULSCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void ULSCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (LSGameInstance == nullptr)
	{
		return;
	}
	
	CurrentStatData = LSGameInstance->GetLSPlayerData(NewLevel);
	if (CurrentStatData)
	{
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;
	}
}

void ULSCharacterStatComponent::SetDamage(float NewDamage)
{
	if (CurrentStatData == nullptr)
	{
		return;
	}
	
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);
	if (CurrentHP <= 0.0f)
	{
		OnHPIsZero.Broadcast();
	}

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

float ULSCharacterStatComponent::GetAttackDamage() const
{
	// TODO: 
	return 50.0f;
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


float ULSCharacterStatComponent::GetHPRatio()
{
	if (CurrentStatData)
	{
		return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
	}
	else
	{
		return 0.0f;
	}
	
}
