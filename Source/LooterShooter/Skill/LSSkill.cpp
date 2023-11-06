// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSkill.h"

void ULSSkill::Tick(float DeltaTime)
{
	if (CurrentSkillState == ESkillState::ESS_Cool)
	{
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= SkillCoolTime)
		{
			SetSkillReady();
			OnSkillCool.Broadcast(0.0f);
			LSLOG(Warning, TEXT("SKill On"));
			return;
		}
		float CoolTimeRate = (SkillCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (ElapsedTime / SkillCoolTime);
		OnSkillCool.Broadcast(1.0f - CoolTimeRate);
	}
}

void ULSSkill::Init(APawn* Player)
{
}

bool ULSSkill::IsReady()
{
	return CurrentSkillState == ESkillState::ESS_Ready;
}

bool ULSSkill::IsCool()
{
	return CurrentSkillState == ESkillState::ESS_Cool;
}

void ULSSkill::SetSkillReady()
{
	CurrentSkillState = ESkillState::ESS_Ready;
	ElapsedTime = 0.0f;
}

bool ULSSkill::CastSkill()
{
	return false;
}
