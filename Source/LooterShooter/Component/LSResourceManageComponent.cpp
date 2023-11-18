// Fill out your copyright notice in the Description page of Project Settings.


#include "LSResourceManageComponent.h"

ULSResourceManageComponent::ULSResourceManageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	OnResourceChanged.AddUObject(this, &ULSResourceManageComponent::TestFunc);
}

void ULSResourceManageComponent::UpdateResources()
{
	OnResourceChanged.Broadcast();
}

void ULSResourceManageComponent::BeginPlay()
{
	Super::BeginPlay();

	OnResourceChanged.Broadcast();
}

void ULSResourceManageComponent::SetCurrentAmmo(EAmmoType AmmoType, int32 Amount)
{
	int MaxAmmo = GetMaxAmmo(AmmoType);
	switch (AmmoType)
	{
		case EAmmoType::EAT_Rifle:
		{
			CurrentRifleAmmo = FMath::Clamp(Amount, 0, MaxAmmo);
			break;
		}
		case EAmmoType::EAT_Pistol:
		{
			CurrentPistolAmmo = FMath::Clamp(Amount, 0, MaxAmmo);;
			break;
		}
		case EAmmoType::EAT_Shotgun:
		{
			CurrentShotgunAmmo = FMath::Clamp(Amount, 0, MaxAmmo);;
			break;
		}
	}	
	OnResourceChanged.Broadcast();
}

void ULSResourceManageComponent::SetCurrentAmmo(const TMap<EAmmoType, int32>& CurrentAmmoMap)
{
	for (auto& Elem : CurrentAmmoMap)
	{
		SetCurrentAmmo(Elem.Key, Elem.Value);
	}
	OnResourceChanged.Broadcast();
}

int32 ULSResourceManageComponent::GetCurrentAmmo(EAmmoType AmmoType) const
{
	switch (AmmoType)
	{
		case EAmmoType::EAT_Rifle:
		{
			return CurrentRifleAmmo;
		}
		case EAmmoType::EAT_Pistol:
		{
			return CurrentPistolAmmo;
		}
		case EAmmoType::EAT_Shotgun:
		{
			return CurrentShotgunAmmo;
		}
	}
	return -1;
}

int32 ULSResourceManageComponent::GetMaxAmmo(EAmmoType AmmoType) const
{
	switch (AmmoType)
	{
		case EAmmoType::EAT_Rifle:
			return MaxRifleAmmo;
		
		case EAmmoType::EAT_Pistol:
			return MaxPistolAmmo;
		
		case EAmmoType::EAT_Shotgun:
			return MaxShotgunAmmo;
		
	}
	return -1;
}

void ULSResourceManageComponent::SetGoldAmount(int32 Amount)
{
	GoldAmount = Amount;
	OnResourceChanged.Broadcast();
}

void ULSResourceManageComponent::ConsumeAmmo(EAmmoType AmmoType, int32 Amount)
{

}

void ULSResourceManageComponent::TestFunc()
{
}
