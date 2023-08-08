// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryComponent.h"
#include "LSWeaponDefinition.h"
#include "LSEquipmentComponent.h"
#include "LSGameState.h"

// Sets default values for this component's properties
ULSInventoryComponent::ULSInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULSInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	WeaponList.Init(nullptr, MaxInventoryCapacity);


// later delete
	LSLOG(Warning, TEXT("Construct default weapon in begin play"));
	SetDefaultWeapon();



	// ...
}

void ULSInventoryComponent::SetDefaultWeapon()
{
	int32 TempNum;
	TempNum = GetEmptyIndex();
	WeaponList[TempNum] = NewObject<ULSWeaponDefinition>(this);
	WeaponList[TempNum]-> SetWeaponDefinitionData(EWeaponType::RIFLE, 3);
	++CurrentInventoryCapacity;
	EquipItem(0);

/*
	TObjectPtr<ULSWeaponDefinition> WeaponDefinition1 = NewObject<ULSWeaponDefinition>(this);
	WeaponDefinition1->SetWeaponDefinitionData(EWeaponType::RIFLE, 3);
	ALSWeaponInstance* WeaponInstance1 = WeaponDefinition1->InstantiateWeapon();
	LSCHECK(EquipmentManager != nullptr);
	EquipmentManager->EquipWeapon(WeaponInstance1);
	AddWeaponToInventory(WeaponDefinition1);
*/
	// WeaponList.Add(WeaponDefinition1); 
}

/*
// Called every frame
void ULSInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/
int32 ULSInventoryComponent::GetEmptyIndex()
{
	for(int32 ItemIndex = 0; ItemIndex < MaxInventoryCapacity; ++ItemIndex)
	{
		if(WeaponList[ItemIndex] == nullptr)
		{
			LSLOG(Warning, TEXT("%d'th inventory is empty"), ItemIndex);
			return ItemIndex;
		}
	}
	LSLOG_S(Error)
	return 0;
}


void ULSInventoryComponent::AddWeaponToInventory(TObjectPtr<ULSWeaponDefinition> WeaponDefinition)
{
	LSCHECK(WeaponDefinition != nullptr);
	if(IsInventoryFull())
	{
		return;
	}
	int32 EmptyIndex = GetEmptyIndex();
	WeaponList[EmptyIndex] = WeaponDefinition;
	CurrentInventoryCapacity += 1;
}

void ULSInventoryComponent::EquipItem(int32 ItemIndex)
{
	LSCHECK(EquipmentManager != nullptr);
	ALSWeaponInstance* WeaponInstance1 = WeaponList[ItemIndex]->InstantiateWeapon();
	EquipmentManager->EquipWeapon(WeaponInstance1);
}
