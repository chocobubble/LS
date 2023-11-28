// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "UObject/NoExportTypes.h"
#include "LooterShooter/Data/WeaponSaveData.h"
#include "LooterSHooter/Data/WeaponBaseData.h"
#include "LSWeaponDefinition.generated.h"

class ULSWeaponAbilityComponent;
class ALSWeaponInstance;
class ULSPLayerState;

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
public:
	ULSWeaponDefinition();

	/** 무기 장착 시 액터 객체 생성 */
	ALSWeaponInstance* InstantiateWeapon();

	/** 아이템 레벨, 무기 타입에 따라 기본 스탯 설정 */
	//void SetWeaponDefinitionData(const TSharedPtr<FWeaponSaveData>& WeaponSaveDataPtr);
	void SetWeaponDefinitionData(FWeaponSaveData* WeaponSaveDataPtr);

	/** 랜덤성을 부여하기 위해 랜덤으로 스탯 수치 수정 */
	void SetWeaponDefinitionStats();

	bool TryEnhanceWeapon();

	void SetWeaponDefaultStats();

	void EnhanceWeapon();

	FOnWeaponStatChangedDelegate OnWeaponStatChanged;

	//TWeakPtr<FWeaponSaveData> WeaponSaveData;
	FWeaponSaveData* WeaponSaveData;
	
private:
	/** 
	 * 아이템 레벨에 따른 기본 스탯을 담은 데이터 테이블 포인터 
	 * ALSGameState 에서 확인 가능
	 */
	FLSWeaponBaseData* WeaponBaseData;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	EWeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 MagazineCapacity = 0;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 WeaponItemLevel = 0;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 EnhancementLevel = 0;

	/** 
	 * 총의 발사 속도
	 * @TODO: 단위를 구체적으로 정하기
	*/
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float FireRate = 500.0f;

	/** 무기 장착시 캐릭터의 이동 속도 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MovementSpeed = 510.0f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float BulletDamage = 50.0f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float CriticalHitChance = 0.03f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float CriticalHitMultiplier = 1.5f;

	/** 무기의 데미지가 감소하기 시작하는 거리 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float DamageReduceDistance = 1000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float ReloadTime = 2.0f;

	/** 탄약 내 들어 있는 총알의 수 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 BulletsPerCatridge = 1;

	/** 총알이 도달하는 최대 거리 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MaxRange = 10000.0f;

	/** 탄착군의 최대 크기 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MaxSpreadAngle  = 1.0f;

	/** 탄착군의 최소 크기 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MinSpreadAngle = 1.0f;

	/** 매 사격당 탄착군이 커지는 정도 */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float HeatPerShot = 0.1f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ULSWeaponAbilityComponent* WeaponAbilityComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TSubclassOf<ALSWeaponInstance> WeaponInstanceClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ALSWeaponInstance* WeaponInstance;

public:
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
};
