// Fill out your copyright notice in the Description page of Project Settings.


#include "LSResourceManageComponent.h"

// Sets default values for this component's properties
ULSResourceManageComponent::ULSResourceManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	OnResourceChanged.AddUObject(this, &ULSResourceManageComponent::NoFunc);
}


// Called when the game starts
void ULSResourceManageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


/*
// Called every frame
void ULSResourceManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/


void ULSResourceManageComponent::UpdateAmmoResource(EAmmoType AmmoType, int32 Amount)
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
		{
			ResourceData->CurrentRifleAmmo += Amount;
			break;
		}
		case EAmmoType::PISTOL:
		{
			ResourceData->CurrentPistolAmmo += Amount;
			break;
		}
		case EAmmoType::SHOTGUN:
		{
			ResourceData->CurrentShotgunAmmo += Amount;
			break;
		}
	}	
	LSLOG_S(Warning);
	OnResourceChanged.Broadcast();
}
int32 ULSResourceManageComponent::GetCurrentAmmo(EAmmoType AmmoType) const
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
		{
			return ResourceData->CurrentRifleAmmo;
		}
		case EAmmoType::PISTOL:
		{
			return ResourceData->CurrentPistolAmmo;
		}
		case EAmmoType::SHOTGUN:
		{
			return ResourceData->CurrentShotgunAmmo;
		}
	}
	return -1;
}
int32 ULSResourceManageComponent::GetMaxAmmo(EAmmoType AmmoType) const
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
		{
			return ResourceData->MaxRifleAmmo;
		}
		case EAmmoType::PISTOL:
		{
			return ResourceData->MaxPistolAmmo;
		}
		case EAmmoType::SHOTGUN:
		{
			return ResourceData->MaxShotgunAmmo;
		}
	}
	return -1;
}