// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSWeapon.generated.h"

enum class GunType
{
	RIFLE,
	PISTOL,
	SHOTGUN
};

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float MaxRange = 10000.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float BulletDamage = 50.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float FireRate = 500.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float CriticalHitChance = 0.03f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float CriticalHitMultiplier = 1.5f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float DamageReduceDistance = 1000.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float ReloadTime = 5.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	int32 BulletsPerCatridge = 1;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	int32 MagazineCapacity = 20;


/*
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float MaxSpreadAngle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float MinSpreadAngle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float HeatPerShot;
*/





/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDamageMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDamageMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackModifierMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackModifierMax;


	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float AttackModifier;
*/
};
