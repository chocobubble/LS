// Fill out your copyright notice in the Description page of Project Settings.


#include "LSEquipmentComponent.h"
#include "LSWeapon.h"
#include "LSWeaponInstance.h"
#include "LSWeaponDefinition.h"

#include "LSCharacter.h"

// Sets default values for this component's properties
ULSEquipmentComponent::ULSEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	WeaponInstanceClass = ALSWeaponInstance::StaticClass();
	// ...
}


// Called when the game starts
void ULSEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentWeaponIndex = 0;
}

void ULSEquipmentComponent::SetCurrentWeaponIndex(int32 Index)
{
	CurrentWeaponIndex = Index;
	CurrentWeaponInstance = WeaponInstanceList[Index];
}

void ULSEquipmentComponent::EquipWeapon(ALSWeaponInstance* WeaponInstance)
{
	if(WeaponInstanceList.Num() < 3)
	{
		WeaponInstanceList.Emplace(WeaponInstance);
		CurrentWeaponInstance = WeaponInstance;
		OnEquipmentChanged.Broadcast();
	}
	else
	{
		LSLOG(Warning, TEXT("Weapon list is full"));
	}
}

void ULSEquipmentComponent::EquipWeapon(ALSWeaponInstance* Weapon, int8 index)
{

}

ALSWeaponInstance* ULSEquipmentComponent::GetCurrentWeaponInstance() 
{
	return GetWeaponInstance(CurrentWeaponIndex);
}

ALSWeaponInstance* ULSEquipmentComponent::GetWeaponInstance(int32 Index)
{
	LSCHECK(Index < WeaponInstanceList.Num() , nullptr);
	if(WeaponInstanceList[Index] != nullptr)
	{
		return WeaponInstanceList[Index];
	}
	else
	{
		LSLOG(Error, TEXT("%d error"), Index);
		return nullptr;
	}
} 

void ULSEquipmentComponent::SetRoundsRemaining(int32 NewRoundsRemaining)
{
	LSCHECK(CurrentWeaponInstance != nullptr);
	CurrentWeaponInstance->SetRoundsRemaining(NewRoundsRemaining);
	OnRoundsRemainingChanged.Broadcast(CurrentWeaponIndex);
}

int32 ULSEquipmentComponent::GetRoundsRemaining() const
{
	LSCHECK(CurrentWeaponInstance != nullptr, -1);
	return CurrentWeaponInstance->GetRoundsRemaining();
}

void ULSEquipmentComponent::DecreaseRoundsRemaining()
{
	int32 NewRoundsRemaining = CurrentWeaponInstance->GetRoundsRemaining() - 1;
	SetRoundsRemaining(NewRoundsRemaining);
}

