// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LooterShooter/Data/WeaponBaseData.h"
#include "LSWeapon.generated.h"

class UAnimationAsset;
class ALSBullet;

/**
 * 몬스터 용 무기
 * 플레이어 무기는 LSWeaponDefinition, LSWeaponInstance 사용
 */

UCLASS()
class LOOTERSHOOTER_API ALSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSWeapon();

	void FireBullet();

protected:
	virtual void BeginPlay() override;

private:
	FLSWeaponBaseData* CurrentWeaponData;

	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 WeaponLevel = 1;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UAnimationAsset* ShootingAnim;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TSubclassOf<ALSBullet> LSBulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	ALSBullet* Bullet;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	const USkeletalMeshSocket* EjectSocket;
};
