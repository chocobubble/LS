// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Character.h"
#include "LooterShooter/Types/AmmoType.h"
#include "LooterShooter/Data/PlayerBaseData.h"

//////// recoil
#include "Curves/CurveVector.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
//////// end recoil

#include "LSPlayer.generated.h"

class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class ULSPlayerAnimInstance;
class ULSDefenseComponent;
class ULSEquipmentComponent;
class ULSPopUpWidget;
class ULSGameInstance;
class ULSInventoryComponent;
class ULSWeaponDefinition;
class UCameraComponent;
class UWidgetComponent;
class ULSCharacterStatComponent;
class ALSPlayerController;
class ALSWeaponInstance;
class UInputTriggerPulse;
class ALSInteractableObject;
class ULSResourceManageComponent;
class UCableComponent;
class ULSSkillComponent;
struct FInputActionValue;
struct FInputActionInstance;
struct FStreamableHandle;
struct FLSPlayerData;

/** 공격 종료 후 호출 델리게이트 */
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
/** 상호작용 progress */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractProgressDelegate, float);
/** 상호작용 물체와 오버랩 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnableToInteractDelegate, bool);
/** 재장전 progress */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnReloadProgressDelegate, float);


/**
 * 플레이어 캐릭터 정의 클래스
*/
UCLASS()
class LOOTERSHOOTER_API ALSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ALSPlayer();

	// debug line
	void ShowDebugLine(FVector Dir);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/** @TODO: modify to melee attack */
	void Attack();

	void AttackCheck();

	void InteractCheck();

	void GrappleBegin();

	void OnAssetLoadCompleted();

	void OnReloadComplete();

	void InteractWithObject();
	
	void CheckHit();

	void PlayThrowGrenadeMontage();

	void PlayRifleShootMontage();

	void InitPlayerData();

	TSharedPtr<FStreamableHandle> AssetStreamingHandle;

	FTimerHandle FireTimer = { };
	FTimerHandle RecoveryTimer = { };
	FTimerHandle DeadTimerHandle = { };
	FTimerHandle ReloadTimerHandle = { };

	FOnAttackEndDelegate OnAttackEnd;
	FOnInteractProgressDelegate OnInteractProgress;
	FOnEnableToInteractDelegate OnEnableToInteract;
	FOnReloadProgressDelegate OnReloadProgress;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override; 

private:
///// Input 관련 메서드들 ////////////////////////////
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	void MeleeAttack(const FInputActionValue& Value);

	void OnRunning(const FInputActionValue& Value);

	void EndRunning(const FInputActionValue& Value);

	void OnAiming(const FInputActionValue& Value);

	void EndAiming(const FInputActionValue& Value);

	void GrapplingHook(const FInputActionValue& Value);

	void Reload(const FInputActionValue& Value);

	void EquipFirstWeapon();

	void EquipSecondWeapon(const FInputActionValue& Value);

	void EquipThirdWeapon(const FInputActionValue& Value);

	void OnInteractButtonDown(const FInputActionInstance& ActionInstance);

	void OnInteractButtonPressed(const FInputActionValue& Value);

	void UseFirstSkill();

	/** enhanced input 시스템 테스트 용 */
	void TestAct(const FInputActionValue& Value);
////////////////////////////////////////////////////////

private:
	/// @brief Enhanced Input ///
	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* ShootAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* MeleeAttackAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* AutoRunAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* AimAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* GrapplingHookAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* ReloadAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* EquipFirstWeaponAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* EquipSecondWeaponAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* EquipThirdWeaponAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* InteractAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* FirstSkillAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* TestAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputTriggerPulse* ShootInputTriggerPulse;
////////////////////////////////

///////////////////
	/** components */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	/** 탄환 수, 골드량 등의 자원 관리  */
	UPROPERTY(VisibleAnywhere, Category = "Resource")
	ULSResourceManageComponent* ResourceManager;

	/** HP, Shield, MP, 방어력 등 관리 */
	UPROPERTY(VisibleAnywhere, Category = "Defense")
	ULSDefenseComponent* DefenseManager;

	/** 장착한 장비 아이템 관리 */
	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	ULSEquipmentComponent* EquipmentManager;

	/** 인벤토리 내 아이템 관리 */
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	ULSInventoryComponent* InventoryManager;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	ULSSkillComponent* SkillManager;

	/** 캐릭터의 레벨, 경험치 등 저장되어야 하는 스탯 관리 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	ULSCharacterStatComponent* CharacterStat;
/////////////////////

    UPROPERTY(VisibleAnywhere, Category = "Controller")
	ALSPlayerController* LSPlayerController;

	UPROPERTY(VisibleAnywhere, Category = "Mode")
	ULSGameInstance* LSGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ALSWeaponInstance* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	ULSPlayerAnimInstance* LSPlayerAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	UAnimMontage* ThrowGrenadeMontage;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	UAnimMontage* RifleShootMontage;
	
	UPROPERTY(VisibleAnywhere, Category = "State")
	ECharacterState CurrentState;

	UPROPERTY(VisibleAnywhere, Category = "Interact")
	ALSInteractableObject* InteractingObject;

	/** For Test */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<ULSWeaponDefinition> WeaponDefinition;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool bIsMeleeAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool bIsReloading = false;

	/** 그래플링 훅 도달 지점으로 이동 중 여부 */
	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	bool bIsGrappling = false;

	/** 그래플링 훅 발동 캐스팅 중인지 여부 */
	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	bool bIsGrapplingCasting = false;

	/** Interact 가능한 물체와 overlap 하고 있는 지 */
	UPROPERTY(VisibleAnywhere, Category = "State")
	bool bIsNearInteractableObject = false;

	UPROPERTY(EditAnywhere, Category = "State")
	float DeadTimer = 5.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float TestTimer = 0.1f;

	UPROPERTY(VisibleAnywhere, Category = "State")
	float ArmLengthTo = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "State")
	float ArmLengthOnAiming = 200.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "State")
	float ArmLengthOnIdle = 450.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "State")
	float ArmLengthChangingSpeed = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float DefaultAttackRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float InteractRange = 800.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float DefaultJumpHeight = 450.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float JumpHeight = 450.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float DefaultWalkSpeed = 510.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float WalkSpeedOnAiming = 240.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float DefaultRunningSpeed = 800.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float MaxCheckLength = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	FVector HitPos;

	UPROPERTY(EditAnywhere, Category = "State")
	float InteractionElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "State")
	float InteractionCompleteTime = 1.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "State")
	FVector ToAimDirection;

	FLSPlayerData* PlayerData;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float CurrentRecoilTest = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float RecoilTest = -2.0f;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float InterpolateTime = 3.0f;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float CurrentRemainElapsedTime = 0.5f;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float RemainElapsedTime = 0.5f;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float Acceleration = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float InterpolateSpeed = 5.0f;
	
/////////// 
	/** 그래플링 훅 관련 */
	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	float GrapplingHookRange = 5000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	float GrapplingStopRange = 500.0f;

	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	float GrapplingMovementSpeed = 3.0f;

	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	float GrapplingJumpHeight = 500.0f;

	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	float GrapplingHeightCorrection = 150.0f;

	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	float GrapplingCastingTime = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	float CurrentGrapplingCastingTime = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Grapple")
	FVector GrappleToLocation;

	FTimerHandle GrapplingTimerHandle = { };

	/** @TODO: 그래플링 훅 로프 구현하기 */

	UPROPERTY(VisibleAnywhere, Category = "Grapple")
	UCableComponent* Cable;

///////////// recoil
	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	UCurveVector* RecoilCurve;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	bool bIsFiring = false;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float FireRate = 0.1f;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	float Recoiltime;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	bool bRecoil;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	bool bRecoilRecovery;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	FRotator RecoilStartRot;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	FRotator RecoilDeltaRot;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	FRotator PlayerDeltaRot;

	UPROPERTY(VisibleAnywhere, Category = "Recoil")
	FRotator Del;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoveryTime = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoverySpeed = 10.0f;

	// 사격 시 호출되는 반동 시작 함수
	UFUNCTION(BlueprintCallable)
	void RecoilStart();

	// 사격 중단 시 호출되는 반동 종료 함수
	UFUNCTION(BlueprintCallable)
	void RecoilStop();

	UFUNCTION()
	void RecoveryStart();

	UFUNCTION()
	void RecoveryTimerFunction();

	UFUNCTION()
	void RecoilTimerFunction();

	UFUNCTION(BlueprintCallable)
	void RecoilTick(float DeltaTime);
///////////// end recoil

public:
	void SetCharacterState(ECharacterState NewState);
	// TODO: 위 아래 합치기
	void SetCharacterStateDead()
	{
		SetCharacterState(ECharacterState::ECS_Dead);
	}
	
	ECharacterState GetCharacterState() const
	{
		return CurrentState;
	}

	bool CanSetWeapon()
	{
		return true; 
	}

	void SetWeapon(ALSWeaponInstance* NewWeapon);

	// 탄약이 탄창 내 있거나, 장전 중이 아닌 등 사격 가능한 지 여부 리턴
	bool CanShoot(EAmmoType AmmoType);

	float GetFinalAttackRange() const;

	float GetFinalAttackDamage(bool bIsWeakPoint) const;
	
	float GetFinalInteractRange() const
	{
		return InteractRange;
	}

	ULSResourceManageComponent* GetResourceManager() const
	{
		return ResourceManager;
	}

	ULSEquipmentComponent* GetEquipmentManager() const
	{
		return EquipmentManager;
	}

	ULSInventoryComponent* GetInventoryManager() const
	{
		return InventoryManager;
	}

	ULSDefenseComponent* GetDefenseManager() const
	{
		return DefenseManager;
	}

	void SetShootInputInterval(float InputInterval);

	void SetIsNearInteractableObject(bool Value);

	void SetInteractionElapsedTime(float ElapsedTime);

	void SetInteractingObject(ALSInteractableObject* OverlappingObject)
	{
		InteractingObject = OverlappingObject;
	}

	float GetInteractionElapsedRatio() const
	{
		return InteractionElapsedTime / InteractionCompleteTime;
	}

	int32 GetPlayerLevel() const;

	FVector GetThrowSocketPos() const;

	FVector GetHitPos() const
	{
		return HitPos;
	}
};
