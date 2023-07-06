// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacterStatComponent.h"
#include "LSGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULSCharacterStatComponent::ULSCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; //true;

	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void ULSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

/*
// Called every frame
void ULSCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

*/

void ULSCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(Level);
}

void ULSCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	// #include "Kismet/GameplayStatics.h"
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	LSCHECK(nullptr != LSGameInstance);
	CurrentStatData = LSGameInstance->GetLSCharacterData(NewLevel);
	if(nullptr != CurrentStatData)
	{
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;

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
	return CurrentStatData->Attack;
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