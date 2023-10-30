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

	LSCHECK(nullptr != LSGameInstance);
	CurrentStatData = LSGameInstance->GetLSPlayerData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;
		LSLOG(Warning, TEXT("Player Data Set New Level"));
		//SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		LSLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void ULSCharacterStatComponent::SetDamage(float NewDamage)
{
	LSCHECK(nullptr != CurrentStatData);
	
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);
	if ( CurrentHP <= 0.0f )
	{
		OnHPIsZero.Broadcast();
	}
	

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

float ULSCharacterStatComponent::GetAttack()
{
	LSCHECK(nullptr != CurrentStatData, 0.0f);
	// return CurrentStatData->Attack;
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
	LSCHECK(nullptr != CurrentStatData, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

/*
int32 ULSCharacterStatComponent::GetDropExp() const
{
	return CurrentStatData->DropExp;
}
*/
