// Fill out your copyright notice in the Description page of Project Settings.


#include "LSEquipmentComponent.h"
#include "LSWeapon.h"
#include "LSWeaponInstance.h"
#include "LSCharacter.h"

// Sets default values for this component's properties
ULSEquipmentComponent::ULSEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	WeaponClass = ALSWeapon::StaticClass();
	//
	WeaponInstanceClass = ALSWeaponInstance::StaticClass();
	// ...
}


// Called when the game starts
void ULSEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

/*
	for(int32 index = 0; index < 3; ++index)
	{
		ALSWeapon* NewWeapon = GetWorld()->SpawnActor<ALSWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		NewWeapon->SetActorHiddenInGame(true);
		// NewWeapon->SetOwner(GetOwner<ALSCharacter>());
		WeaponList.Emplace(NewWeapon);
		//WeaponList.Emplace(GetWorld()->SpawnActor<ALSWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator));
	}
*/

	for(int32 index = 0; index < 3; ++index)
	{
		ALSWeaponInstance* NewWeapon = GetWorld()->SpawnActor<ALSWeaponInstance>(WeaponInstanceClass, FVector::ZeroVector, FRotator::ZeroRotator);
		NewWeapon->SetWeaponData(EWeaponType::RIFLE, 1);
		NewWeapon->SetActorHiddenInGame(true);
		NewWeapon->SetOwner(GetOwner());
		// LSLOG(Warning, TEXT("%s is owner"), *GetOwner<ALSCharacter>()->GetDebugName(GetOwner<ALSCharacter>()));
		WeaponInstanceList.Emplace(NewWeapon);
		//WeaponList.Emplace(GetWorld()->SpawnActor<ALSWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator));
	}

/*
	ALSWeaponInstance* NewWeapon = GetWorld()->SpawnActor<ALSWeaponInstance>(WeaponInstanceClass, FVector::ZeroVector, FRotator::ZeroRotator);
	NewWeapon->SetWeaponData(EWeaponType::RIFLE, 1);
	NewWeapon->SetActorHiddenInGame(true);
	NewWeapon->SetOwner(this);//GetOwner<ALSCharacter>());
	WeaponInstanceList.Emplace(NewWeapon);
	CurrentWeaponIndex = 0;
	// ...
	*/

	CurrentWeaponIndex = 0;
	CurrentWeaponInstance = WeaponInstanceList[CurrentWeaponIndex];
}

void ULSEquipmentComponent::EquipWeapon(ALSWeapon* Weapon)
{
	if(WeaponList.Num() < 3)
	{
		WeaponList.Emplace(Weapon);
		CurrentWeapon = Weapon;
		OnEquipmentChanged.Broadcast();
	}
	else
	{
		LSLOG(Warning, TEXT("Weapon list is full"));
	}
}

void ULSEquipmentComponent::EquipWeapon(ALSWeapon* Weapon, int8 index)
{

}

ALSWeapon* ULSEquipmentComponent::GetCurrentWeapon() 
{
	return GetWeapon(CurrentWeaponIndex);
}

ALSWeapon* ULSEquipmentComponent::GetWeapon(int32 Index) const
{
	if(WeaponList[Index] != nullptr)
	{
		return WeaponList[Index];
	}
	else
	{
		LSLOG(Error, TEXT("%d error"), Index);
		return nullptr;
	}
} 

void ULSEquipmentComponent::SetCurrentWeaponIndex(int32 Index)
{
	CurrentWeaponIndex = Index;
	CurrentWeaponInstance = WeaponInstanceList[Index];
}

void ULSEquipmentComponent::EquipWeapon(ALSWeaponInstance* Weapon)
{
	if(WeaponInstanceList.Num() < 3)
	{
		WeaponInstanceList.Emplace(Weapon);
		CurrentWeaponInstance = Weapon;
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

/*
// Called every frame
void ULSEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

