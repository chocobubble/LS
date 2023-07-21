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


void ULSResourceManageComponent::SetCurrentAmmo(EAmmoType AmmoType, int32 Amount)
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
		{
			//ResourceData->CurrentRifleAmmo += Amount;
			SetCurrentRifleAmmo(Amount);
			break;
		}
		/*
		case EAmmoType::PISTOL:
		{
			//ResourceData->CurrentPistolAmmo += Amount;
			SetCurrentRifleAmmo -= Amount
			break;
		}
		case EAmmoType::SHOTGUN:
		{
			ResourceData->CurrentShotgunAmmo += Amount;
			break;
		}
		*/
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
			return GetCurrentRifleAmmo();
		}
		/*
		case EAmmoType::PISTOL:
		{
			return ResourceData->CurrentPistolAmmo;
		}
		case EAmmoType::SHOTGUN:
		{
			return ResourceData->CurrentShotgunAmmo;
		}
		*/
	}
	LSLOG(Warning, TEXT("No Matching Ammo Type"));
	return -1;
}

void ULSResourceManageComponent::SetRoundsRemaining(EAmmoType AmmoType, int32 Amount)
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
		{
			RoundsRemaining = FMath::Clamp(RoundsRemaining + Amount, 0, CurrentRifleAmmo);
			break;
		}
		/*
		case EAmmoType::PISTOL:
		{
			//ResourceData->CurrentPistolAmmo += Amount;
			SetCurrentRifleAmmo -= Amount
			break;
		}
		case EAmmoType::SHOTGUN:
		{
			ResourceData->CurrentShotgunAmmo += Amount;
			break;
		}
		*/
	}	
	LSLOG_S(Warning);
	OnResourceChanged.Broadcast();
}

int32 ULSResourceManageComponent::GetMaxAmmo(EAmmoType AmmoType) const
{
	switch (AmmoType)
	{
		case EAmmoType::RIFLE:
		{
			return GetMaxRifleAmmo();
		}
		/*
		case EAmmoType::PISTOL:
		{
			return ResourceData->MaxPistolAmmo;
		}
		case EAmmoType::SHOTGUN:
		{
			return ResourceData->MaxShotgunAmmo;
		}
		*/
	}
	LSLOG(Warning, TEXT("No Matching Ammo Type"));
	return -1;
}


void ULSResourceManageComponent::ConsumeAmmo(EAmmoType AmmoType, int32 Amount)
{
	/*
	SetRoundsRemaining(AmmoType, Amount);
	SetCurrentAmmo(AmmoType, Amount);
	*/
}