// Fill out your copyright notice in the Description page of Project Settings.

#include "LSEquipmentComponent.h"
#include "LooterShooter/Weapon/LSWeapon.h"
#include "LooterShooter/Weapon/LSWeaponInstance.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"

ULSEquipmentComponent::ULSEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WeaponInstanceClass = ALSWeaponInstance::StaticClass();
}

void ULSEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
}

void ULSEquipmentComponent::EquipWeapon(ALSWeaponInstance* WeaponInstance)
{
	if (WeaponInstance == nullptr)
	{
		return;
	}
	
	if (WeaponInstanceList.Num() < 3)
	{
		WeaponInstanceList.Emplace(WeaponInstance);
		CurrentWeaponInstance = WeaponInstance;
		OnEquipmentChanged.Broadcast();
	}
}

void ULSEquipmentComponent::EquipWeapon(ALSWeaponInstance* Weapon, int8 index)
{

}

ALSWeaponInstance* ULSEquipmentComponent::GetWeaponInstance(int32 Index)
{
	if (Index >= WeaponInstanceList.Num())
	{
		return nullptr;
	}
	return WeaponInstanceList[Index];
} 

void ULSEquipmentComponent::SetRoundsRemaining(int32 NewRoundsRemaining)
{
	if (CurrentWeaponInstance == nullptr)
	{
		return;
	}
	CurrentWeaponInstance->SetRoundsRemaining(NewRoundsRemaining);
	OnRoundsRemainingChanged.Broadcast(CurrentWeaponIndex);
}

int32 ULSEquipmentComponent::GetRoundsRemaining() const
{
	if (CurrentWeaponInstance == nullptr)
	{
		return 0;
	}
	return CurrentWeaponInstance->GetRoundsRemaining();
}

int32 ULSEquipmentComponent::DecreaseRoundsRemaining()
{
	if (CurrentWeaponInstance == nullptr)
	{
		return 0;
	}
	// 탄약을 1보다 많이 소모하는 속성 넣는 경우 여기 수정하기
	int32 NewRoundsRemaining = CurrentWeaponInstance->GetRoundsRemaining() - 1;
	SetRoundsRemaining(NewRoundsRemaining);
	return NewRoundsRemaining;
}

