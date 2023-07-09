// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LSGameMode.h"
#include "Animation/AnimInstance.h"
#include "LSAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	ULSAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void SetDeadAnim() { bIsDead = true; }

	void PlayAttackMontage();

	FOnAttackHitCheckDelegate OnAttackHitCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = "true"))
	float CurrentPawnSpeed = 0.0f;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	bool IsInAir = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
};
