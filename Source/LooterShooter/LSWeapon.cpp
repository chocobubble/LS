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

	AttackRange = 150.0f;
	AttackDamageMax = 10.0f;
	AttackDamageMin = -2.5f;
	AttackModifierMax = 1.25f;
	AttackModifierMin = 0.85f;
}

float ALSWeapon::GetAttackRange() const
{
	return AttackRange;
}

float ALSWeapon::GetAttackDamage() const
{
	return AttackDamage;
}

float ALSWeapon::GetAttackModifier() const
{
	return AttackModifier;
}

void ALSWeapon::BeginPlay()
{
	Super::BeginPlay();

	AttackDamage = FMath::RandRange(AttackDamageMin, AttackDamageMax);
	AttackModifier = FMath::RandRange(AttackModifierMin, AttackModifierMax);
	LSLOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), AttackDamage, AttackModifier);
}

