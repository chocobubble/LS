// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "UObject/NoExportTypes.h"
#include "LSWeaponInstance.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/GameMode/LSGameState.h"
#include "LooterShooter/Types/WeaponType.h"
#include "LSWeaponDefinition.generated.h"

class ULSWeaponAbilityComponent;

/** 강화 등에 의해 무기 스탯 변경 시 */
DECLARE_MULTICAST_DELEGATE(FOnWeaponStatChangedDelegate);

/**
 * 무기가 구현되었을 때 해당 무기의 데이터를 보관하는 클래스
 * 인벤토리에 이 형태로 무기가 보관되어 있다.
 */
UCLASS()
class LOOTERSHOOTER_API ULSWeaponDefinition : public UObject
{
	GENERATED_BODY()

private:
	/** 
	 * 아이템 레벨에 따른 기본 스탯을 담은 데이터 테이블 포인터 
	 * ALSGameState 에서 확인 가능
	 */
	FLSWeaponBaseData* WeaponBaseData;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 WeaponItemLevel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 EnhancementLevel = 0;

	/** 
	 * 총의 발사 속도
	 * @TODO: 단위를 구체적으로 정하기
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float FireRate = 500.f;

	/** 무기 장착시 캐릭터의 이동 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 510.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float BulletDamage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float CriticalHitChance = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float CriticalHitMultiplier = 1.5f;

	/** 무기의 데미지가 감소하기 시작하는 거리 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float DamageReduceDistance = 1000.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float ReloadTime = 2.f;

	/** 탄약 내 들어 있는 총알의 수 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	int32 BulletsPerCatridge = 1;

	/** 총알이 도달하는 최대 거리 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MaxRange = 10000.f;

	/** 탄착군의 최대 크기 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MaxSpreadAngle  = 1.f;

	/** 탄착군의 최소 크기 */
	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float MinSpreadAngle = 1.f;

	/** 매 사격당 탄착군이 커지는 정도 */
	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float HeatPerShot = 0.1f;

public:
	UPROPERTY(VisibleAnywhere, Category = Ability)
	ULSWeaponAbilityComponent* WeaponAbilityComponent;

	UPROPERTY(EditInstanceOnly, Category = Weapon)
	TSubclassOf<ALSWeaponInstance> WeaponInstanceClass;

public:
	ULSWeaponDefinition();

	/** 무기 장착 시 액터 객체 생성 */
	ALSWeaponInstance* InstantiateWeapon();
	/** 아이템 레벨, 무기 타입에 따라 기본 스탯 설정 */
	void SetWeaponDefinitionData(EWeaponType WeaponTypeParam, int32 WeaponLevel, int32 WeaponEnhancementLevel);
	/** 랜덤성을 부여하기 위해 랜덤으로 스탯 수치 수정 */
	void SetWeaponDefinitionStats();
	bool TryEnhanceWeapon();
	void SetWeaponDefaultStats();
	void EnhanceWeapon();
	
	int32 GetWeaponItemLevel() const
	{
		return WeaponItemLevel;
	}

	EWeaponType GetWeaponType() const
	{
		return WeaponType;
	}
	int32 GetEnhancementLevel() const
	{
		return EnhancementLevel;
	}
	float GetMagazineCapacity() const
	{
		return MagazineCapacity;
	}
	float GetFireRate() const
	{
		return FireRate;
	}
	float GetMovementSpeed() const
	{
		return MovementSpeed;
	}
	float GetBulletDamage() const
	{
		return BulletDamage;
	}
	float GetCriticalHitChance() const
	{
		return CriticalHitChance;
	}
	float GetCriticalHitMultiplier() const
	{
		return CriticalHitMultiplier;
	}
	float GetDamageReduceDistance() const
	{
		return DamageReduceDistance;
	}
	float GetReloadTime() const
	{
		return ReloadTime;
	}
	int32 GetBulletsPerCatridge() const
	{
		return BulletsPerCatridge;
	}
	float GetMaxRange() const
	{
		return MaxRange;
	}
	float GetMaxSpreadAngle() const
	{
		return MaxSpreadAngle;
	}
	float GetMinSpreadAngle() const
	{
		return MinSpreadAngle;
	}
	float GetHeatPerShot() const
	{
		return HeatPerShot;
	}
	void SetBulletDamage(float Value)
	{
		BulletDamage = Value;
	}

	FOnWeaponStatChangedDelegate OnWeaponStatChanged; 
};
