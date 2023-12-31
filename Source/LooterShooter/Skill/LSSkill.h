// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "UObject/NoExportTypes.h"
#include "LSSkill.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSkillCoolDelegate, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSkillCoolTwoParamDelegate, float, int32);

enum class ESkillState : uint8
{
	ESS_Default,
	ESS_Cool,
	ESS_Ready
};

class ALSPlayer;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ULSSkill : public UObject
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime);

	virtual void Init(APawn* Player);

	virtual bool CastSkill();

	FOnSkillCoolDelegate OnSkillCool;

	FOnSkillCoolTwoParamDelegate OnSkillCoolTwoParam;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	ALSPlayer* LSPlayer;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float SkillCoolTime;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float ElapsedTime = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	float MPCost;

	ESkillState CurrentSkillState = ESkillState::ESS_Ready;

public:
	bool IsReady();

	bool IsCool();

	void SetSkillReady();

	float GetMPCost() const
	{
		return MPCost;
	}
};
