// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Character.h"
#include "LSMonster.generated.h"

class UInputComponent;
class ULSCharacterStatComponent;
class ALSAIController;
class ULSDefenseComponent;
class UWidgetComponent;
class ULSGameInstance;
class ULSAnimInstance;
class ALSWeapon;
struct FStreamableHandle;

UCLASS()
class LOOTERSHOOTER_API ALSMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ALSMonster();

	/** 에셋 로드 완료 시 호출되는 메서드 */
	void OnAssetLoadCompleted();

	void ShowDebugLine(FVector const& Dir); // 디버깅 용도

	/** 무기 장착 */
	void EquipWeapon();

    // Attack
	/** Behavior Tree Blackboard의 AttackTarget을 TargetPawn으로 설정 */
	void SetAttackTarget(APawn* TargetPawn);

	/** AttackTarget 공격 */
	void Attack();

	/** 명중률에 따른 탄착군 형성 */
	FVector CalculateRecoil(FVector const& AimDir, const float SpreadAngle);
	
	void Init(int32 Level);

	/** 몬스터 사망 시 아이템 드롭 */
	void DropItem();

///////
protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	
private:
	//FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	ALSAIController* LSAIController;

	/** 캐릭터가 죽고 나서 애니메이션 재생 및 아이템 드랍 까지의 시간*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float DeadTimer = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	ULSAnimInstance* LSMonsterAnim;

	UPROPERTY(VisibleAnywhere, Category = "Defense")
	ULSDefenseComponent* DefenseManager;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ULSGameInstance* LSGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	ULSCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ALSWeapon* MonsterWeapon;

	UPROPERTY(EditInstanceOnly, Category = "Weapon")
	TSubclassOf<ALSWeapon> LSWeaponInstanceClass;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	APawn* AttackTarget;

	/** 탄착군을 형성하는 각도 */
	UPROPERTY(VisibleAnywhere, Category = "Attack")
	float BulletSpreadAngle = 3.0f;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	float AttackRange = 3000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	float AttackDamage = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int32 Exp = 5;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int32 MonsterLevel = 2;

	FTimerHandle DeadTimerHandle = { };

public:
	/** 
	 * 캐릭터의 상태를 NewState로 설정한다.
	 * 상태는 PREINIT->LOADING->READY->DEAD 로 변한다.
	*/
	void SetCharacterState(ECharacterState NewState);

	ECharacterState GetCharacterState() const
	{
		return CurrentState;
	}


	void SetCharacterStateDead();

	/** 몬스터 죽일 시 얻는 경험치 리턴*/
	int32 GetExp() const
	{
		return Exp;
	}

	void SetMonsterLevel(int32 Value)
	{
		MonsterLevel = Value;
	}
};
