// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Character.h"
#include "LSMonster.generated.h"

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
	// Sets default values for this character's properties
	ALSMonster();

	/** 
	 * 캐릭터의 상태를 NewState로 설정한다.
	 * 상태는 PREINIT->LOADING->READY->DEAD 로 변한다.
	*/
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;
	void SetCharacterStateDead();
	/** 몬스터 사망 시 아이템 드롭 */
	void DropItem();
	/** 몬스터 죽일 시 얻는 경험치 리턴*/
	int32 GetExp() const
	{
		return Exp;
	}

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);
	/** 에셋 로드 완료 시 호출되는 메서드 */
	void OnAssetLoadCompleted();
	void ShowDebugLine(FVector Dir); // 디버깅 용도
	/** 무기 장착 */
	void SetWeapon(ALSWeapon* NewWeapon);

// Attack
	/** Behavior Tree Blackboard의 AttackTarget을 TargetPawn으로 설정 */
	void SetAttackTarget(APawn* TargetPawn);
	/** AttackTarget 공격 */
	void Attack();
	/** 명중률에 따른 탄착군 형성 */
	FVector CalculateRecoil(FVector AimDir, const float SpreadAngle);
///////
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

	UPROPERTY(VisibleAnywhere)
	ALSAIController* LSAIController;

	/** 캐릭터가 죽고 나서 애니메이션 재생 및 아이템 드랍 까지의 타이머*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float DeadTimer = 1.f;

	UPROPERTY(EditAnywhere, Category = Animation)
	ULSAnimInstance* LSMonsterAnim;

	FTimerHandle DeadTimerHandle = { };
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Defense)
	ULSDefenseComponent* DefenseManager;

	UPROPERTY(VisibleAnywhere, Category = UI)
	UWidgetComponent* HPBarWidget;

	UPROPERTY()
	ULSGameInstance* LSGameInstance;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	ULSCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	ALSWeapon* CurrentWeapon;

private:
	UPROPERTY(VisibleAnywhere, Category = Attack)
	APawn* AttackTarget;

	/** 탄착군을 형성하는 각도 */
	UPROPERTY(VisibleAnywhere, Category = Attack)
	float BulletSpreadAngle = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = Attack)
	float AttackRange = 600.0f;

	UPROPERTY(VisibleAnywhere, Category = Attack)
	float AttackDamage = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	int32 Exp = 5;
};
