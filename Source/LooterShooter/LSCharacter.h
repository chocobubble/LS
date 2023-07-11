// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"

#include "LSAnimInstance.h"

//#include "LSWeapon.h"


#include "LSCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);


class ALSAIController;
class ALSPlayerController;
class ULSHUDWidget;

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
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MeleeAction;

	UPROPERTY()
	class ULSAnimInstance* LSAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float AttackRange;


	

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

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	bool CanSetWeapon();
	void SetWeapon(class ALSWeapon* NewWeapon);

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	class ALSWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class ULSCharacterStatComponent* CharacterStat;

	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	FOnAttackEndDelegate OnAttackEnd;

	float GetFinalAttackRange() const;
	float GetFianlAttackDamage() const;

private:
	void JumpAct(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void Melee(const FInputActionValue& Value);

	void AttackCheck();

	void OnAssetLoadCompleted();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bIsPlayer;

	UPROPERTY()
	ALSAIController* LSAIController;

	UPROPERTY()
	ALSPlayerController* LSPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float DeadTimer;

	FTimerHandle DeadTimerHandle = { };
};
