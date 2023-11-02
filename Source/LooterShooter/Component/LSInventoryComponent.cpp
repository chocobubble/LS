// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryComponent.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"
#include "LSEquipmentComponent.h"
#include "LooterShooter/GameMode/LSGameState.h"
#include "LooterShooter/Character/LSPlayerState.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework\Controller.h"


ULSInventoryComponent::ULSInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULSInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	WeaponList.Init(nullptr, MaxInventoryCapacity);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		AController* Controller = Cast<AController>(OwnerPawn->GetController());
		if (Controller)
		{
			LSPlayerState = Cast<ALSPlayerState>(Controller->GetPlayerState<ALSPlayerState>());
		}
	}

	if (LSPlayerState == nullptr || LSPlayerState->GetOwnedWeapons().Num() == 0)
	{
		SetDefaultWeapon();
	}
	else
	{
		for (auto& Elem : LSPlayerState->GetOwnedWeapons())
		{
			int32 TempNum = GetEmptyIndex();
			WeaponList[TempNum] = NewObject<ULSWeaponDefinition>(this);
			WeaponList[TempNum]->SetWeaponDefinitionData(EWeaponType::RIFLE, Elem.Key, Elem.Value);
			EquipItem(TempNum);
			++CurrentInventoryCapacity;
			WeaponList[TempNum]->OnWeaponStatChanged.AddUObject(this, &ULSInventoryComponent::UpdateWeaponDefinition);
		}
	}
}

void ULSInventoryComponent::SetDefaultWeapon()
{
	int32 DefaultWeaponLevel = 2;
	int32 DefaultWeaponEnhancementLevel = 1;
	int32 TempNum = GetEmptyIndex();
	WeaponList[TempNum] = NewObject<ULSWeaponDefinition>(this);
	WeaponList[TempNum]->SetWeaponDefinitionData(EWeaponType::RIFLE, DefaultWeaponLevel, DefaultWeaponEnhancementLevel);
	EquipItem(TempNum);
	++CurrentInventoryCapacity;
	WeaponList[TempNum]->OnWeaponStatChanged.AddUObject(this, &ULSInventoryComponent::UpdateWeaponDefinition);
	
	// 무기 상태 업데이트
	LSPlayerState->UpdateOwnedWeaponData(0, DefaultWeaponLevel, DefaultWeaponEnhancementLevel);
}

int32 ULSInventoryComponent::GetEmptyIndex()
{
	for (int32 ItemIndex = 0; ItemIndex < MaxInventoryCapacity; ++ItemIndex)
	{
		if (WeaponList[ItemIndex] == nullptr)
		{
			return ItemIndex;
		}
	}
	LSLOG_S(Error)
	return 0;
}

void ULSInventoryComponent::AddWeaponToInventory(TObjectPtr<ULSWeaponDefinition> WeaponDefinition)
{
	if (WeaponDefinition == nullptr || IsInventoryFull())
	{
		return;
	}
	int32 EmptyIndex = GetEmptyIndex();
	WeaponList[EmptyIndex] = WeaponDefinition;
	++CurrentInventoryCapacity;
}

void ULSInventoryComponent::EquipItem(int32 ItemIndex)
{
	if (EquipmentManager == nullptr)
	{
		return;
	}
	ALSWeaponInstance* WeaponInstance = WeaponList[ItemIndex]->InstantiateWeapon();
	if (WeaponInstance)
	{
		EquipmentManager->EquipWeapon(WeaponInstance);
	}
}


void ULSInventoryComponent::UpdateWeaponDefinition()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		AController* Controller = Cast<AController>(OwnerPawn->GetController());
		if (Controller)
		{
			LSPlayerState = Cast<ALSPlayerState>(Controller->GetPlayerState<ALSPlayerState>());
			if (LSPlayerState)
			{
				LSPlayerState->UpdateOwnedWeaponData(0, WeaponList[0]->GetWeaponItemLevel(), WeaponList[0]->GetEnhancementLevel());
			}
		}
	}
}