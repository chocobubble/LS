// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "LooterShooter/Weapon/LSBullet.h"

ALSWeapon::ALSWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPONMesh"));
	RootComponent = WeaponMesh;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_RIFLE(TEXT("/Game/Weapons/Rifle/Mesh/SK_Rifle.SK_Rifle"));
	if (SK_RIFLE.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(SK_RIFLE.Object);
	}

	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));

	LSBulletClass = ALSBullet::StaticClass();

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AA_FIRE(TEXT("/Game/MilitaryWeapSilver/Weapons/Animations/Fire_Rifle_W.Fire_Rifle_W"));
	if (AA_FIRE.Succeeded())
	{
		ShootingAnim = AA_FIRE.Object;
	}
}

void ALSWeapon::FireBullet(const FVector& TargetPos)
{
	if (WeaponMesh == nullptr)
	{
		return;
	}

	if (ShootingAnim)
	{
		WeaponMesh->PlayAnimation(ShootingAnim, false);
	}

	if (LSBulletClass)
	{
		EjectSocket = WeaponMesh->GetSocketByName(FName("AmmoEject"));
	}

	if (EjectSocket) {
		const FTransform EjectSocketTransform = EjectSocket->GetSocketTransform(WeaponMesh);
		const FVector EjectSocketPos = EjectSocketTransform.GetLocation();

		// 총알 생성 후 발사
		if (GetWorld())
		{
			Bullet = GetWorld()->SpawnActor<ALSBullet>(
				LSBulletClass,
				EjectSocketPos,
				(TargetPos - EjectSocketPos).Rotation()
			);
			if (Bullet)
			{
				Bullet->Fire();
			}
		}
	}
}

void ALSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

