// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/GameMode/LSGameState.h"
#include "LSWeapon.generated.h"

/**
 * 이전 버전.
 * @deprecated 사용하지 않는 클래스
 * ULSWeaponDefinition 사용할 것
 */

UCLASS()
class LOOTERSHOOTER_API ALSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSWeapon();

	float GetMaxRange() const;
	float GetBulletDamage() const;
	float GetFinalDamage() const;
	float GetReloadTime() const;
	float GetMagazineCapacity() const;
	// float GetAttackModifier() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* RifleWeapon;

protected:

private:
	FLSWeaponBaseData* CurrentWeaponData;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 Level = 1;
};
