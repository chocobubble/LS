// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeapon.h"
#include "Kismet/GameplayStatics.h"


ALSWeapon::ALSWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	RifleWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RIFLEWEAPON"));
	RootComponent = RifleWeapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_RIFLE(TEXT("/Game/Weapons/Rifle/Mesh/SK_Rifle.SK_Rifle"));
	if (SK_RIFLE.Succeeded())
	{
		RifleWeapon->SetSkeletalMesh(SK_RIFLE.Object);
	}

	RifleWeapon->SetCollisionProfileName(TEXT("NoCollision"));
}

float ALSWeapon::GetMaxRange() const
{
	return CurrentWeaponData->MaxRange;
}

float ALSWeapon::GetBulletDamage() const
{
	return CurrentWeaponData->BulletDamage;
}

float ALSWeapon::GetFinalDamage() const
{
	float FinalDamage = CurrentWeaponData->BulletDamage;
	float DamageMultiplier = (FMath::RandRange(0.0f, 1.0f) <= CurrentWeaponData->CriticalHitChance) ? CurrentWeaponData->CriticalHitMultiplier : 1.0f;
	FinalDamage *= DamageMultiplier;
	return FinalDamage;
}

float ALSWeapon::GetReloadTime() const
{
	return CurrentWeaponData->ReloadTime;
}

float ALSWeapon::GetMagazineCapacity() const
{
	return CurrentWeaponData->MagazineCapacity;
}
 
void ALSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

