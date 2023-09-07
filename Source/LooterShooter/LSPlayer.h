// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Character.h"
#include "LSResourceManageComponent.h"

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
class ALSAmmo;
struct FInputActionValue;
struct FInputActionInstance;

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

	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	// not override?
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override; 
	bool CanSetWeapon();
	void SetWeapon(ALSWeaponInstance* NewWeapon);

	// 탄약이 탄창 내 있거나, 장전 중이 아닌 등 사격 가능한 지 여부 리턴
	bool CanShoot(EAmmoType AmmoType);

	// debug line
	void ShowDebugLine(FVector Dir);

	float GetFinalAttackRange() const;
	float GetFinalAttackDamage() const;
	float GetFinalInteractRange() const;
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
	void SetCharacterStateDead();

public:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	FOnAttackEndDelegate OnAttackEnd;
	FOnInteractProgressDelegate OnInteractProgress;
	FOnEnableToInteractDelegate OnEnableToInteract;
	FOnReloadProgressDelegate OnReloadProgress;
private:
	void JumpAct(const FInputActionValue& Value);
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
	void EquipFirstWeapon(const FInputActionValue& Value);
	void EquipSecondWeapon(const FInputActionValue& Value);
	void EquipThirdWeapon(const FInputActionValue& Value);
	void InteractProgress(const FInputActionInstance& ActionInstance);
	void Interact(const FInputActionValue& Value);
	void InteractEnd(const FInputActionValue& Value);

	/** enhanced input 시스템 테스트 용 */
	void TestAct(const FInputActionValue& Value);

	/** @TODO: modify to melee attack */
	void Attack();
	void AttackCheck();
	void InteractCheck();
	void GrappleBegin();
	void SetInteractionElapsedTime(float ElapsedTime);
	float GetInteractionElapsedRatio() const
	{
		return  InteractionElapsedTime / InteractionCompleteTime;
	}
	void OnAssetLoadCompleted();

	/** For Test */
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<ULSWeaponDefinition> WeaponDefinition;

private:
	/// @brief Enhanced Input ///
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MeleeAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AutoRunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* GrapplingHookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipFirstWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipSecondWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipThirdWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* TestAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputTriggerPulse* ShootInputTriggerPulse;
////////////////////////////////

///////////////////
/** components */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	/** 탄환 수, 골드량 등의 자원 관리  */
	UPROPERTY(VisibleAnywhere, Category = Resource)
	ULSResourceManageComponent* ResourceManager;

	/** HP, Shield, MP, 방어력 등 관리 */
	UPROPERTY(VisibleAnywhere, Category = Defense)
	ULSDefenseComponent* DefenseManager;

	/** 장착한 장비 아이템 관리 */
	UPROPERTY(VisibleAnywhere, Category = Equipment)
	ULSEquipmentComponent* EquipmentManager;

	/** 인벤토리 내 아이템 관리 */
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	ULSInventoryComponent* InventoryManager;

	/** 캐릭터의 레벨, 경험치 등 저장되어야 하는 스탯 관리 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = Stat)
	ULSCharacterStatComponent* CharacterStat;
/////////////////////

    UPROPERTY()
	ALSPlayerController* LSPlayerController;

	UPROPERTY()
	ULSGameInstance* LSGameInstance;

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	ALSWeaponInstance* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	ALSAmmo* Ammo;

	UPROPERTY(VisibleAnywhere, Category=Animation)
	ULSPlayerAnimInstance* LSPlayerAnim;
	
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

private:
	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);

	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bIsMeleeAttacking = false;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bIsReloading = false;

	/** 그래플링 훅 도달 지점으로 이동 중 여부 */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = Grapple, meta = (AllowPrivateAccess = "true"))
	bool bIsGrappling = false;

	/** 그래플링 훅 발동 캐스팅 중인지 여부 */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = Grapple, meta = (AllowPrivateAccess = "true"))
	bool bIsGrapplingCasting = false;

	/** Interact 가능한 물체와 overlap 하고 있는 지 */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bIsNearInteractableObject = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float DeadTimer = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float TestTimer = 0.1f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthTo = 0.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthOnAiming = 200.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthOnIdle = 450.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthChangingSpeed = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interact, meta = (AllowPrivateAccess = "true"))
	float InteractRange = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float JumpHeight = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float DefaultWalkSpeed = 510.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float WalkSpeedOnAiming = 240.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float InteractionElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float InteractionCompleteTime = 1.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	FVector ToAimDirection;

	FTimerHandle DeadTimerHandle = { };
	FTimerHandle ReloadTimerHandle = { };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test, meta = (AllowPrivateAccess = "true"))
	float CurrentRecoilTest = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test, meta = (AllowPrivateAccess = "true"))
	float RecoilTest = -2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test, meta = (AllowPrivateAccess = "true"))
	float InterpolateTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test, meta = (AllowPrivateAccess = "true"))
	float CurrentRemainElapsedTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test, meta = (AllowPrivateAccess = "true"))
	float RemainElapsedTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test, meta = (AllowPrivateAccess = "true"))
	float Acceleration = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test, meta = (AllowPrivateAccess = "true"))
	float InterpolateSpeed = 5.f;
	
/////////// 
	/** 그래플링 훅 관련 */

	/** @TODO: 그래플링 훅 로프 구현하기 */
/*
	UPROPERTY(VisibleAnywhere, Category = Grppling)
	UCableComponent* Cable;
*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grppling, meta = (AllowPrivateAccess = "true"))
	float GrapplingHookRange = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grppling, meta = (AllowPrivateAccess = "true"))
	float GrapplingStopRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grppling, meta = (AllowPrivateAccess = "true"))
	float GrapplingMovementSpeed = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grppling, meta = (AllowPrivateAccess = "true"))
	float GrapplingJumpHeight = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grppling, meta = (AllowPrivateAccess = "true"))
	float GrapplingHeightCorrection = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grppling, meta = (AllowPrivateAccess = "true"))
	float GrapplingCastingTime = 1.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = Grppling, meta = (AllowPrivateAccess = "true"))
	FVector GrappleToLocation;

	FTimerHandle GrapplingTimerHandle = { };
///////////////


///////////// recoil
public:
UPROPERTY(VisibleAnywhere, Category = "Recoil")
UCurveVector* RecoilCurve;

UPROPERTY(VisibleAnywhere, Category = "Recoil")
bool bIsFiring=false;

UPROPERTY(VisibleAnywhere, Category = "Recoil")
float FireRate=0.1f;

UPROPERTY(VisibleAnywhere, Category = "Recoil")
float Recoiltime;

UPROPERTY(VisibleAnywhere, Category = "Recoil")
bool bRecoil;

UPROPERTY(VisibleAnywhere, Category = "Recoil")
bool bRecoilRecovery;

UPROPERTY()
FTimerHandle FireTimer;

UPROPERTY()
FTimerHandle RecoveryTimer;

UPROPERTY(VisibleAnywhere, Category = "Recoil")
FRotator RecoilStartRot;
UPROPERTY(VisibleAnywhere, Category = "Recoil")
  FRotator RecoilDeltaRot;
UPROPERTY(VisibleAnywhere, Category = "Recoil")
  FRotator PlayerDeltaRot;
UPROPERTY(VisibleAnywhere, Category = "Recoil")
 FRotator Del;

UPROPERTY(BlueprintReadWrite)
float RecoveryTime = 1.0f;
UPROPERTY(BlueprintReadWrite)
float RecoverySpeed =10.0f;
 UFUNCTION(BlueprintCallable)
  void RecoilStart();
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
/*
 UPROPERTY(BlueprintReadWrite,Replicated)
  ACPP_MainGameWeapon* CPPWeaponRef;
*/
///////////// end recoil
};
