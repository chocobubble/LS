// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Animation/AnimInstance.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/Types/WeaponType.h"
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

	void PlayAttackMontage();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = "true"))
	float CurrentPawnSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = "true"))
	float AOPitch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool IsInAir = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool bIsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	EWeaponType EquippedWeaponType;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FTransform LHandTF;

public:
	void SetAimAnim(bool IsAiming)
	{
    	bIsAiming = IsAiming;
	}
	
	void SetReloadAnim(bool IsReloading)
	{
    	bIsReloading = IsReloading;
	}

	void SetWeaponType(EWeaponType WeaponType)
	{
    	EquippedWeaponType = WeaponType;
	}

	void SetDeadAnim() 
	{
		bIsDead = true;
	}

	void SetAOPitch(float AimOffsetPitch)
	{
		AOPitch = FMath::Clamp(AimOffsetPitch * 3.0f, -90.0f, 90.0f);
	}

	void SetLeftHandTransform(FTransform& LeftHandTransform)
	{
		LHandTF = LeftHandTransform;
	}
};
