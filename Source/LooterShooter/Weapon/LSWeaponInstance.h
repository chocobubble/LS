// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LooterShooter/Types/WeaponType.h"
#include "LooterShooter/Types/AmmoType.h"
#include "Curves/CurveVector.h"
#include "LSWeaponInstance.generated.h"

/** 테스트용 델리게이트 */
DECLARE_MULTICAST_DELEGATE_OneParam(FTest, FVector);

class ALSCharacter;
class ULSResourceManageComponent;
class ULSWeaponAbilityComponent;
class ULSWeaponDefinition;
class UAnimationAsset;
class ALSBullet;
class USkeletalMeshSocket;

/**
 * 장착한 무기의 액터 클래스
 * Inventory에서 무기를 장착하면 ULSWeaponDefiinition의 데이터를 받고,
 * 장착한 다른 아이템들에 의한 스탯 증감을 계산해 최종 무기 스탯을 결정한 뒤 무기 액터를 생성한다.
 * ULSEquipmentComponent에 의해 관리 된다.
 */
UCLASS()
class LOOTERSHOOTER_API ALSWeaponInstance : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSWeaponInstance();

	/** 무기 초기화 */
	void Init();

	/** 무기 최종 스탯 결정 */
	void SetWeaponStats();

	/** 무기 메시 설정 */
	void SetWeaponSkeletalMesh();

	/** 무기 초기화 */
	void Shoot(const FVector& TargetPos);

	/** 사격에 따른 탄착군 계산 */
	FVector CalculateRecoil(const FVector& AimDir, const float HalfAngle);
	
	// 테스트용 델리게이트
	FTest OnAimDirChange; 

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMeshComponent* WeaponSkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ULSWeaponDefinition* BaseWeaponDefinition;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 MagazineCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float FireRate;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MovementSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float BulletDamage;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float CriticalHitChance;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float CriticalHitMultiplier;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float DamageReduceDistance;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float ReloadTime;

	/** 
	 * 하나의 탄약에 들어있는 총알의 수 
	 * 보통의 총은 하나의 탄약에 하나의 총알이 들어가 있으나
	 * 샷건 같은 경우는 여러 총알이 들어 있음
	*/
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 BulletsPerCatridge = 1;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MaxRange = 10000.0f;

	/** 탄착군의 최대 크기 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MaxSpreadAngle = 1.0f;

	/** 탄착군의 최소 크기 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MinSpreadAngle = 0.0f;

	/** 매 사격당 탄착군이 커지는 정도 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float HeatPerShot = 0.1f;

///////////////////////////////////////////
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	EWeaponType GunType = EWeaponType::RIFLE;

	/** 현재 탄착군의 크기 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float CurrentSpreadAngle = 0.3f;

	/** 탄창내 남아 있는 탄약의 수 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 RoundsRemaining;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UAnimationAsset* ShootingAnim;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TSubclassOf<ALSBullet> LSBulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	ALSBullet* Bullet;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	const USkeletalMeshSocket* EjectSocket;

public:
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

	float GetFireRate() const
	{
		return FireRate;
	}

	/** 탄착군의 크기 */
	float GetCurrentSpreadAngle() const
	{
		return CurrentSpreadAngle;
	}

	float GetCriticalHitChance() const
	{
		return CriticalHitChance;
	}

	float GetCriticalHitMultiplier() const
	{
		return CriticalHitMultiplier;
	}
	
	/** 탄창 내 남아 있는 탄약 수 리턴 */
	int32 GetRoundsRemaining() const
	{
		return RoundsRemaining;
	}

	void SetBulletDamage(float Value)
	{
		BulletDamage = Value;
	}

	/** 장전, 소비 등으로 탄창 내 남아 있는 탄약 수 업데이트 */
	void SetRoundsRemaining(int32 NewRoundsRemaining)
	{
		RoundsRemaining = NewRoundsRemaining;
	}

	ULSWeaponDefinition* GetBaseWeaponDefinition() const
	{
		return BaseWeaponDefinition;
	}

	/** 인벤토리 내의 base WeaponDefinition을 연결 */
	void SetBaseWeaponDefinition(ULSWeaponDefinition* WeaponDefinition)
	{
		if (WeaponDefinition) 
		{
			BaseWeaponDefinition = WeaponDefinition;
		}
	}

	/** 사격 히트 시 최종 데미지 계산 */
	float GetFinalDamage() const;

	/** 무기의 ammo type 반환 */
	EAmmoType GetAmmoType();

	EWeaponType GetGunType() const
	{
		return GunType;
	}
};
