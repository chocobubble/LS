// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LooterShooter/Component/LSWeaponAbilityComponent.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/Weapon/LSBullet.h"
#include "LSWeaponDefinition.h"
#include "Engine/SkeletalMeshSocket.h"

ALSWeaponInstance::ALSWeaponInstance()
{
 	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPONMESH"));
	RootComponent = WeaponSkeletalMesh;

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AA_FIRE(TEXT("/Game/MilitaryWeapSilver/Weapons/Animations/Fire_Rifle_W.Fire_Rifle_W"));
	if (AA_FIRE.Succeeded())
	{
		ShootingAnim = AA_FIRE.Object;
	}

	LSBulletClass = ALSBullet::StaticClass();
}

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
	if (BaseWeaponDefinition)
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
}

void ALSWeaponInstance::SetWeaponSkeletalMesh()
{
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (LSGameInstance == nullptr || WeaponSkeletalMesh == nullptr)
	{
		return;
	}
	switch(GunType) 
	{
		case EWeaponType::EWT_Rifle:
		{
			if (LSGameInstance->GetRifleMesh()) 
			{
				WeaponSkeletalMesh->SetSkeletalMesh(LSGameInstance->GetRifleMesh());
				WeaponSkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));
			}
			break;
		}
		case EWeaponType::EWT_Shotgun:
		{
			if (LSGameInstance->GetShotgunMesh()) 
			{	
				WeaponSkeletalMesh->SetSkeletalMesh(LSGameInstance->GetShotgunMesh());
				WeaponSkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));
			}
			break;
		}
		case EWeaponType::EWT_Pistol:
		{
			if (LSGameInstance->GetPistolMesh()) 
			{
				WeaponSkeletalMesh->SetSkeletalMesh(LSGameInstance->GetPistolMesh());
				WeaponSkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));
			}
			break;
		}
	}
}

void ALSWeaponInstance::Shoot(const FVector& TargetPos)
{
	if (WeaponSkeletalMesh == nullptr)
	{
		return;
	}

	if (ShootingAnim)
	{
		LSLOG(Warning, TEXT("Play SHoot Amin"));
		WeaponSkeletalMesh->PlayAnimation(ShootingAnim, false);
	}

	if (LSBulletClass)
	{
		EjectSocket = WeaponSkeletalMesh->GetSocketByName(FName("AmmoEject"));
	}

	const FTransform EjectSocketTransform = EjectSocket->GetSocketTransform(WeaponSkeletalMesh);
	const FVector EjectSocketPos = EjectSocketTransform.GetLocation();

	// 총알 생성 후 발사
	if (GetWorld())
	{
		Bullet = GetWorld()->SpawnActor<ALSBullet>(
			LSBulletClass,
			EjectSocketPos,
			//EjectSocketTransform.GetRotation().Rotator()
			(TargetPos - EjectSocketPos).Rotation()
		);
		if (Bullet)
		{
			Bullet->Fire();
		}
	}
}

float ALSWeaponInstance::GetFinalDamage() const
{
	float FinalDamage = BulletDamage;
	float DamageMultiplier = (FMath::RandRange(0.0f, 1.0f) <= CriticalHitChance) ? CriticalHitMultiplier : 1.0f;
	FinalDamage *= DamageMultiplier;
	return FinalDamage;
}

void ALSWeaponInstance::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);
	
	/** 
	 * @TODO:
	 * 1. 사격 후 시간 경과에 따른 탄착군 크기 감소 구현
	 * 2. 
	*/
}

FVector ALSWeaponInstance::CalculateRecoil(const FVector& AimDir, const float HalfAngle)
{
	if (HalfAngle > 0.0f)
	{
		const float AngleAround = FMath::FRandRange(0.0f, 1.0f) * 360.0f;

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

// TODO: AMMOTYPE 나중에 바꾸기
EAmmoType ALSWeaponInstance::GetAmmoType()
{
	switch(GunType)
	{
		case EWeaponType::EWT_Rifle:
		{
			return EAmmoType::EAT_Rifle;
		}
		case EWeaponType::EWT_Shotgun:
		{
			return EAmmoType::EAT_Shotgun;
		}
		case EWeaponType::EWT_Pistol:
		{
			return EAmmoType::EAT_Pistol; 
		}
	}
	return EAmmoType::EAT_Rifle;
}