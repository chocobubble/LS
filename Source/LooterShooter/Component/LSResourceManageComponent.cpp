// Fill out your copyright notice in the Description page of Project Settings.


#include "LSResourceManageComponent.h"

ULSResourceManageComponent::ULSResourceManageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	OnResourceChanged.AddUObject(this, &ULSResourceManageComponent::TestFunc);
}

void ULSResourceManageComponent::BeginPlay()
{
	Super::BeginPlay();

	OnResourceChanged.Broadcast();
}

void ULSResourceManageComponent::SetCurrentAmmo(EAmmoType AmmoType, int32 Amount)
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
			CurrentRifleAmmo = Amount;
			break;
		
		case EAmmoType::PISTOL:
			CurrentPistolAmmo = Amount;
			break;
		
		case EAmmoType::SHOTGUN:
			CurrentShotgunAmmo = Amount;
			break;
		
	}	
	OnResourceChanged.Broadcast();
}

int32 ULSResourceManageComponent::GetCurrentAmmo(EAmmoType AmmoType) const
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
			return CurrentRifleAmmo;
		
		case EAmmoType::PISTOL:
			return CurrentPistolAmmo;
		
		case EAmmoType::SHOTGUN:
			return CurrentShotgunAmmo;
		
	}
	return -1;
}

int32 ULSResourceManageComponent::GetMaxAmmo(EAmmoType AmmoType) const
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
			return MaxRifleAmmo;
		
		case EAmmoType::PISTOL:
			return MaxPistolAmmo;
		
		case EAmmoType::SHOTGUN:
			return MaxShotgunAmmo;
		
	}
	return -1;
}


void ULSResourceManageComponent::ConsumeAmmo(EAmmoType AmmoType, int32 Amount)
{

}
