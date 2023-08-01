// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSGameInstance.h"
#include "LSGameState.h"


#include "LSWeapon.generated.h"


/*
enum class GunType
{
	RIFLE,
	PISTOL,
	SHOTGUN
};
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

/*
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	int32 MagazineCapacity = 20;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	float FireRate = 500.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	float MovementSpeed = 510.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	float BulletDamage = 50.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	float CriticalHitChance = 0.03f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	float CriticalHitMultiplier = 1.5f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	float DamageReduceDistance = 1000.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	float ReloadTime = 2.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon)
	int32 BulletsPerCatridge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MaxRange = 10000.f;
*/
	

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
