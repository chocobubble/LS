// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSkill.h"

void ULSSkill::Tick(float DeltaTime)
{
	if (CurrentSkillState == ESkillState::COOL)
	{
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= SkillCoolTime)
		{
			SetSkillReady();
			OnSkillCool.Broadcast(0.0f);
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
	return CurrentSkillState == ESkillState::READY;
}

bool ULSSkill::IsCool()
{
	return CurrentSkillState == ESkillState::COOL;
}

void ULSSkill::SetSkillReady()
{
	CurrentSkillState = ESkillState::READY;
	ElapsedTime = 0.0f;
}

bool ULSSkill::CastSkill()
{
	if (CurrentSkillState != ESkillState::READY)
	{
		return false;
	}

	CurrentSkillState = ESkillState::COOL;

	return true;
}
