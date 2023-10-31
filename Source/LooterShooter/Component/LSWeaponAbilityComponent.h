// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSWeaponAbilityComponent.generated.h"

class ALSWeaponInstance;
class ULSWeaponDefinition;

/**
 * 무기의 부가 속성을 구현하는 클래스
 * @TODO: 
 * 1. 성능 향상을 위해, UObject 상속 빼고 기본 class 혹은 struct로 교체
 * 2. UI 표현을 위해 string 멤버 변수 구현
 * 3. 필요 시 Interface로 전환
*/
UCLASS()
class UWeaponAbility : public UObject
{
	GENERATED_BODY()

public:
	/** 
	 * @note: 자식 클래스에서 구현 해주어야 함 
	 * 무기가 액터 객체가 될 때 부가 속성 능력치 적용하는 함수
	*/
	virtual void ApplyAbility(ULSWeaponDefinition* WeaponDefinition) {}

	/** 부가 속성의 능력치 수치 설정 */
	virtual void SetAbilityStat(float Stat);

protected:
	/** 부가 속성의 능력치 */
	UPROPERTY()
	float AbilityStat;
};

/** 무기의 데미지를 증감하는 부가 속성 */
UCLASS()
class UBulletDamageAbility : public UWeaponAbility
{
	GENERATED_BODY()

public:
	virtual void ApplyAbility(ULSWeaponDefinition* WeaponDefinition) override;

};

/** 무기의 부가 속성들을 관리하는 컴포넌트 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSWeaponAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULSWeaponAbilityComponent();

	void EnhanceWeaponStat(ULSWeaponDefinition* WeaponDefinition);

	void AttachWeaponAbility(UWeaponAbility* WeaponAbility);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	TArray<UWeaponAbility*> AbilityList;
};
