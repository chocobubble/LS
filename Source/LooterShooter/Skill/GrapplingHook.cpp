// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplingHook.h"
#include "LooterShooter/Character/LSPlayer.h"

UGrapplingHook::UGrapplingHook()
{
	SkillCoolTime = 5.0f;
	RemainingHookCount = 2;
	CurrentSkillState = ESkillState::ESS_Ready;
}

bool UGrapplingHook::CastSkill()
{
	if (RemainingHookCount <= 0)
	{
		return false;
	}

	if (LSPlayer == nullptr)
	{
		return false;
	}

	--RemainingHookCount;
	LSPlayer->ThrowHook();

	return true;
}

void UGrapplingHook::Init(APawn* Player)
{
	Super::Init(Player);

	if (Player)
	{
		LSPlayer = Cast<ALSPlayer>(Player);
	}
}

void UGrapplingHook::Tick(float DeltaTime)
{
	if (RemainingHookCount < 2)
	{
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= SkillCoolTime)
		{
			++RemainingHookCount;
			OnSkillCoolTwoParam.Broadcast(0.0f, RemainingHookCount);
			
			if (RemainingHookCount >= 1)
			{
				SetSkillReady();
			}
			return;
		}
		float CoolTimeRate = (SkillCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (ElapsedTime / SkillCoolTime);
		OnSkillCoolTwoParam.Broadcast(1.0f - CoolTimeRate, RemainingHookCount);
	}
}
