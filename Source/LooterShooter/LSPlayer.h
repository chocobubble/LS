// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Character.h"
#include "LSPlayer.generated.h"

class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class ULSAnimInstance;
class ULSDefenseComponent;
class ULSEquipmentComponent;
class ULSPopUpWidget;
class ULSGameInstance;
class ULSInventoryComponent;
class ULSWeaponDefinition;
class UCameraComponent;
class ULSResourceManageComponent;
class UWidgetComponent;


UCLASS()
class LOOTERSHOOTER_API ALSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ALSPlayer();
/*
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;
*/
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	// virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	// virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);


private:
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

	UPROPERTY()
	ULSAnimInstance* LSAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Interact, meta = (AllowPrivateAccess = "true"))
	float InteractRange = 800.0f;

private:
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
};
