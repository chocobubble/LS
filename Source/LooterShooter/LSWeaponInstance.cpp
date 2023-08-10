// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LSWeaponAbilityComponent.h"
#include "LSWeaponDefinition.h"

// later delete
#include "LSCharacter.h"

// Sets default values
ALSWeaponInstance::ALSWeaponInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPONMESH"));
	RootComponent = WeaponSkeletalMesh;
}

// Called when the game starts or when spawned
void ALSWeaponInstance::BeginPlay()
{
	Super::BeginPlay();
}

void ALSWeaponInstance::Init()
{
	SetWeaponStats();
	SetWeaponSkeletalMesh();
	RoundsRemaining = MagazineCapacity;
}

void ALSWeaponInstance::SetWeaponStats()
{
	GunType = BaseWeaponDefinition->GetWeaponType();
	MagazineCapacity = BaseWeaponDefinition->GetMagazineCapacity();
	FireRate = BaseWeaponDefinition->GetFireRate();
	MovementSpeed = BaseWeaponDefinition->GetMovementSpeed();
	BulletDamage = BaseWeaponDefinition->GetBulletDamage();
	CriticalHitChance = BaseWeaponDefinition->GetCriticalHitChance();
	CriticalHitMultiplier = BaseWeaponDefinition->GetCriticalHitMultiplier();
	DamageReduceDistance = BaseWeaponDefinition->GetDamageReduceDistance();
	ReloadTime = BaseWeaponDefinition->GetReloadTime();
	BulletsPerCatridge = BaseWeaponDefinition->GetBulletsPerCatridge();
	MaxRange = BaseWeaponDefinition->GetMaxRange();
}

void ALSWeaponInstance::SetWeaponSkeletalMesh()
{
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	LSCHECK(LSGameInstance->GetRifleMesh() != nullptr);
	WeaponSkeletalMesh->SetSkeletalMesh(LSGameInstance->GetRifleMesh());
	WeaponSkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));
}


float ALSWeaponInstance::GetFinalDamage() const
{
	float FinalDamage = BulletDamage;
	float DamageMultiplier = (FMath::RandRange(0.f, 1.f) <= CriticalHitChance) ? CriticalHitMultiplier : 1.f;
	FinalDamage *= DamageMultiplier;
	return FinalDamage;
}

void ALSWeaponInstance::SetBulletDamage(float Value)
{
	BulletDamage = Value;
}


// Called every frame
void ALSWeaponInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/** 
	 * @TODO:
	 * 1. 사격 후 시간 경과에 따른 탄착군 크기 감소 구현
	 * 2. 
	*/
}

FVector ALSWeaponInstance::CalculateRecoil(FVector AimDir, const float HalfAngle)
{
	if (HalfAngle > 0.f)
	{
		LSLOG(Warning, TEXT("CalculateRecoil"));
		const float AngleAround = FMath::FRandRange(0.f, 1.f) * 360.0f;

		FRotator Rot = AimDir.Rotation();
		FQuat DirQuat(Rot);
		FQuat FromCenterQuat(FRotator(0.0f, HalfAngle, 0.0f));
		FQuat AroundQuat(FRotator(0.0f, 0.0, AngleAround));
		FQuat FinalDirectionQuat = DirQuat * AroundQuat * FromCenterQuat;
		FinalDirectionQuat.Normalize();

		OnAimDirChange.Broadcast(FinalDirectionQuat.RotateVector(FVector::ForwardVector));
		return FinalDirectionQuat.RotateVector(FVector::ForwardVector);
	}
	else
	{
		return AimDir.GetSafeNormal();
	}
}

void ALSWeaponInstance::SetRoundsRemaining(int32 NewRoundsRemaining)
{
	RoundsRemaining = NewRoundsRemaining;
}


void ALSWeaponInstance::SetBaseWeaponDefinition(ULSWeaponDefinition* WeaponDefinition)
{
	LSCHECK(WeaponDefinition != nullptr);
	BaseWeaponDefinition = WeaponDefinition;
}