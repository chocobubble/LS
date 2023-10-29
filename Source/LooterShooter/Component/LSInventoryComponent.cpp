// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryComponent.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"
#include "LSEquipmentComponent.h"
#include "LooterShooter/GameMode/LSGameState.h"
// #include "LSPlayerAnimInstance.h"

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
	EquipItem(TempNum);
	++CurrentInventoryCapacity;
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
}

int32 ULSInventoryComponent::GetEmptyIndex()
{
	for (int32 ItemIndex = 0; ItemIndex < MaxInventoryCapacity; ++ItemIndex)
	{
		if (WeaponList[ItemIndex] == nullptr)
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
	if (IsInventoryFull())
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
	ALSWeaponInstance* WeaponInstance = WeaponList[ItemIndex]->InstantiateWeapon();
	EquipmentManager->EquipWeapon(WeaponInstance);
	//ULSPlayerAnimInstance* LSPlayerAnim = Cast<ULSPlayerAnimInstance>(Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance());
	//LSPlayerAnim->SetWeaponType(WeaponList[ItemIndex]->GetWeaponType());
}

TObjectPtr<ULSWeaponDefinition> ULSInventoryComponent::GetWeaponDefinitionInList(int32 Index) const
{
	return WeaponList[Index];
}