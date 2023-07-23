// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALSWeaponInstance::ALSWeaponInstance()
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
		LSLOG_S(Error);
	}

	RifleWeapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ALSWeaponInstance::BeginPlay()
{
	Super::BeginPlay();

}

void ALSWeaponInstance::SetWeaponData(EWeaponType WeaponType, int32 ItemLevel)
{
	this->GunType = WeaponType;
	Level = ItemLevel;
	
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	// later switch by weapon type
	WeaponBaseData = LSGameInstance->GetLSWeaponData(Level);
	LSCHECK(WeaponBaseData);
	SetWeaponStats();
}

void ALSWeaponInstance::SetWeaponStats()
{
	// bIsSet 추가?
	MagazineCapacity = WeaponBaseData->MagazineCapacity + FMath::FRandRange(-10.f, 10.f);
	FireRate = WeaponBaseData->FireRate + FMath::FRandRange(-200.f, 200.f);
	MovementSpeed = WeaponBaseData->MovementSpeed;
	BulletDamage = WeaponBaseData->BulletDamage + FMath::FRandRange(-10.f, 10.f);
	CriticalHitChance = WeaponBaseData->CriticalHitChance + FMath::FRandRange(-0.01f, 0.05f);
	CriticalHitMultiplier = WeaponBaseData->CriticalHitMultiplier + FMath::FRandRange(-0.3f, 0.5f);
	DamageReduceDistance = WeaponBaseData->DamageReduceDistance;
	ReloadTime = WeaponBaseData->ReloadTime + FMath::FRandRange(-0.5f, 0.5f);
	BulletsPerCatridge = WeaponBaseData->BulletsPerCatridge;
	MaxRange = WeaponBaseData->MaxRange;

}

float ALSWeaponInstance::GetFinalDamage() const
{
	float FinalDamage = BulletDamage;
	float DamageMultiplier = (FMath::RandRange(0.f, 1.f) <= CriticalHitChance) ? CriticalHitMultiplier : 1.f;
	FinalDamage *= DamageMultiplier;
	return FinalDamage;
}

/*
// Called every frame
void ALSWeaponInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

