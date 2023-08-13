// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Animation/AnimInstance.h"
#include "LSGameInstance.h"

#include "LSPlayerAnimInstance.generated.h"
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	ULSPlayerAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void SetDeadAnim() { bIsDead = true; }

	void SetAimAnim(bool IsAiming);
	
	void SetReloadAnim(bool IsReloading);

	void SetWeaponType(EWeaponType WeaponType);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = "true"))
	float CurrentPawnSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool IsInAir = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bIsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	EWeaponType EquippedWeaponType;
	
};
