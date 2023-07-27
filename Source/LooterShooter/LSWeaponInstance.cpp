// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LSWeaponAbilityComponent.h"

// later delete
#include "LSCharacter.h"

// Sets default values
ALSWeaponInstance::ALSWeaponInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RifleWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RIFLEWEAPON"));
	RootComponent = RifleWeapon;
	WeaponAbilityComponent = CreateDefaultSubobject<ULSWeaponAbilityComponent>(TEXT("WEAPONABILITY"));
	// root?

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

	//Owner = GetOwner<ALSCharacter>();
	//LSCHECK(nullptr != Owner);
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
	WeaponAbilityComponent->EnhanceWeaponStat(this);
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

void ALSWeaponInstance::SetBulletDamage(float Value)
{
	BulletDamage = Value;
}


// Called every frame
void ALSWeaponInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

/*
	if(GetOwner() != nullptr && GetOwner<ALSCharacter>() != nullptr && GetOwner<ALSCharacter>()->Camera != nullptr)
	{
		CalculateRecoil(FRotationMatrix(GetOwner<ALSCharacter>()->Camera->GetComponentRotation()).GetUnitAxis(EAxis::X), CurrentSpreadAngle);
	}
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
		//return FinalDirectionQuat.Rotator();
	}
	else
	{
		return AimDir.GetSafeNormal();
		//return FQuat::Identity;
		//return FRotator::ZeroRotator;
	}


}

