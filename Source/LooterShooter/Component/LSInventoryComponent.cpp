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
	SetDefaultWeapon();
}

void ULSInventoryComponent::SetDefaultWeapon()
{
	int32 DefaultWeaponLevel = 1;
	int32 DefaultWeaponEnhancementLevel = 0;
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		AController* Controller = Cast<AController>(OwnerPawn->GetController());
		if (Controller)
		{
			ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(Controller->GetPlayerState<ALSPlayerState>());
			if (LSPlayerState)
			{
				DefaultWeaponLevel = LSPlayerState->GetCurrentWeaponLevel();
				DefaultWeaponEnhancementLevel = LSPlayerState->GetCurrentWeaponEnhancenmentLevel();
			}
		}
	}
	int32 TempNum;
	TempNum = GetEmptyIndex();
	WeaponList[TempNum] = NewObject<ULSWeaponDefinition>(this);
	WeaponList[TempNum]->SetWeaponDefinitionData(EWeaponType::RIFLE, DefaultWeaponLevel, DefaultWeaponEnhancementLevel);
	EquipItem(TempNum);
	++CurrentInventoryCapacity;
	WeaponList[TempNum]->OnWeaponStatChanged.AddUObject(this, &ULSInventoryComponent::UpdateWeaponDefinition);

	// TODO: 무기 칸 세개까지 늘리기
/*  
	TempNum = GetEmptyIndex();
	WeaponList[TempNum] = NewObject<ULSWeaponDefinition>(this);
	WeaponList[TempNum]-> SetWeaponDefinitionData(EWeaponType::SHOTGUN, 3);
	EquipItem(TempNum);
	++CurrentInventoryCapacity;
	TempNum = GetEmptyIndex();
	WeaponList[TempNum] = NewObject<ULSWeaponDefinition>(this);
	WeaponList[TempNum]-> SetWeaponDefinitionData(EWeaponType::PISTOL, 3);
	EquipItem(TempNum);
	++CurrentInventoryCapacity;
*/
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
			ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(Controller->GetPlayerState<ALSPlayerState>());
			if (LSPlayerState)
			{
				// TODO : list
				LSPlayerState->SetCurrentWeaponLevel(WeaponList[0]->GetWeaponItemLevel());
				LSPlayerState->SetCurrentWeaponEnhancementLevel(WeaponList[0]->GetEnhancement());
			}
		}
	}
}