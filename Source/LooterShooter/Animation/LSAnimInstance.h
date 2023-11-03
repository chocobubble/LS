// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "LSAnimInstance.generated.h"


/**
 * 애니메이션 블루프린트를 다루는 클래스
 * 애님 그래프로 데이터를 전달한다
 */
UCLASS()
class LOOTERSHOOTER_API ULSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	ULSAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = "true"))
	float CurrentPawnSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool IsInAir = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool bIsReloading = false;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

public:
	void PlayAttackMontage();

	void SetAimAnim(bool IsAiming);
	
	void SetReloadAnim(bool IsReloading);

	void SetDeadAnim()
	{
		bIsDead = true;
	}
};
