// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSGameInstance.h"
#include "LSWeaponInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FTest, FVector);

class ALSCharacter;
class ULSWeaponAbilityComponent;
//struct FLSWeaponData;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	RIFLE,
	PISTOL,
	SHOTGUN
};

UCLASS()
class LOOTERSHOOTER_API ALSWeaponInstance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSWeaponInstance();

	void SetWeaponData(EWeaponType WeaponType, int32 ItemLevel);
	void SetWeaponStats();

	float GetMaxRange() const
	{
		return MaxRange;
	}
	float GetBulletDamage() const
	{
		return BulletDamage;
	}
	float GetReloadTime() const
	{
		return ReloadTime;
	}
	float GetMagazineCapacity() const
	{
		return MagazineCapacity;
	}
	float GetCurrentSpreadAngle() const
	{
		return CurrentSpreadAngle;
	}

	float GetFinalDamage() const;

	void SetBulletDamage(float Value);

	FVector CalculateRecoil(FVector AimDir, const float HalfAngle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* RifleWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = Ability)
	ULSWeaponAbilityComponent* WeaponAbilityComponent;

/*
	UPROPERTY(VisibleAnywhere, Category = Ability)
	ALSCharacter* Owner;
*/	
	virtual void Tick(float DeltaTime) override;

	FTest OnAimDirChange;

private:
	FLSWeaponData* WeaponBaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	EWeaponType GunType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float FireRate;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float BulletDamage;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float CriticalHitChance;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float CriticalHitMultiplier;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float DamageReduceDistance;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float ReloadTime;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 BulletsPerCatridge;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MaxRange;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MaxSpreadAngle = 1.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MinSpreadAngle = 0.f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float HeatPerShot = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float CurrentSpreadAngle = 0.1f;

};
