// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "LSResourceManageComponent.h"

#include "LSAnimInstance.h"

//#include "LSWeapon.h"


#include "LSCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);


class ALSAIController;
class ALSPlayerController;
class ULSHUDWidget;
class UInputMappingContext;
class UInputAction;
class UWidgetComponent;
class ULSResourceManageComponent;
class ULSDefenseComponent;
class ULSEquipmentComponent;
class ULSPopUpWidget;
class ALSWeaponInstance;
class ULSGameInstance;
class ULSInventoryComponent;

UCLASS()
class LOOTERSHOOTER_API ALSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALSCharacter();

	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

	int32 GetExp() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
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

	UPROPERTY()
	ULSAnimInstance* LSAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Interact, meta = (AllowPrivateAccess = "true"))
	float InteractRange = 800.0f;
/*
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> PopUpWidgetClass;

	UPROPERTY()
	ULSPopUpWidget* PopUpWidget;
*/

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* RifleWeapon;

	// #include "GameFramework/SpringArmComponent.h"
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	// #include "Camera/CameraComponent.h"
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Resource)
	ULSResourceManageComponent* ResourceManager;

	UPROPERTY(VisibleAnywhere, Category = Defense)
	ULSDefenseComponent* DefenseManager;

	UPROPERTY(VisibleAnywhere, Category = UI)
	UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere, Category = Equipment)
	ULSEquipmentComponent* EquipmentManager;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	ULSInventoryComponent* InventoryManager;

	UPROPERTY()
	ULSGameInstance* LSGameInstance;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	bool CanSetWeapon();
	void SetWeapon(ALSWeaponInstance* NewWeapon);

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	ALSWeaponInstance* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class ULSCharacterStatComponent* CharacterStat;

	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


	bool CanShoot(EAmmoType AmmoType);

	FOnAttackEndDelegate OnAttackEnd;

	float GetFinalAttackRange() const;
	float GetFinalAttackDamage() const;
	float GetFinalInteractRange() const;

private:
	void JumpAct(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void MeleeAttack(const FInputActionValue& Value);
	// void AutoRun(const FInputActionValue& Value);
	void OnRunning(const FInputActionValue& Value);
	void EndRunning(const FInputActionValue& Value);
	void OnAiming(const FInputActionValue& Value);
	void EndAiming(const FInputActionValue& Value);
	void GrapplingHook(const FInputActionValue& Value);
	void Reload(const FInputActionValue& Value);
	void EquipFirstWeapon(const FInputActionValue& Value);
	void EquipSecondWeapon(const FInputActionValue& Value);
	void EquipThirdWeapon(const FInputActionValue& Value);
	
	void Interact(const FInputActionValue& Value);

	void AttackCheck();

	void InteractCheck();

	void OnAssetLoadCompleted();

	void DropItem();

	void SetCharacterStateDead();

	// debug line
	void ShowDebugLine(FVector Dir);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bIsPlayer;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bIsReloading = false;


	UPROPERTY()
	ALSAIController* LSAIController;

	UPROPERTY()
	ALSPlayerController* LSPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float DeadTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float TestTimer = 0.1f;

	

	FTimerHandle DeadTimerHandle = { };
	FTimerHandle ReloadTimerHandle = { };

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthTo = 0.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthOnAiming = 200.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthOnIdle = 450.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float ArmLengthChangingSpeed = 3.0f;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	FVector ToAimDirection;

	
};

