// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeapon.h"

// Sets default values
ALSWeapon::ALSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RifleWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RIFLEWEAPON"));
	RootComponent = RifleWeapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_RIFLE(TEXT("/Game/Weapons/Rifle/Mesh/SK_Rifle.SK_Rifle"));
	if( SK_RIFLE.Succeeded() )
	{
		RifleWeapon->SetSkeletalMesh(SK_RIFLE.Object);
	}
	else
	{
		LSLOG_S(Warning);
	}

	RifleWeapon->SetCollisionProfileName(TEXT("NoCollision"));
/*
	AttackRange = 150.0f;
	AttackDamageMax = 10.0f;
	AttackDamageMin = -2.5f;
	AttackModifierMax = 1.25f;
	AttackModifierMin = 0.85f;
*/
}

float ALSWeapon::GetMaxRange() const
{
	return MaxRange;
}

float ALSWeapon::GetBulletDamage() const
{
	return BulletDamage;
}

float ALSWeapon::GetFinalDamage() const
{
	float FinalDamage = BulletDamage;
	float DamageMultiplier = (FMath::RandRange(0.f, 1.f) <= CriticalHitChance) ? CriticalHitMultiplier : 1.f;
	FinalDamage *= DamageMultiplier;
	return FinalDamage;
}

float ALSWeapon::GetReloadTime() const
{
	return ReloadTime;
}

float ALSWeapon::GetMagazineCapacity() const
{
	return MagazineCapacity;
}
 
void ALSWeapon::BeginPlay()
{
	Super::BeginPlay();

/*
	AttackDamage = FMath::RandRange(AttackDamageMin, AttackDamageMax);
	AttackModifier = FMath::RandRange(AttackModifierMin, AttackModifierMax);
	LSLOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), AttackDamage, AttackModifier);
*/
}

