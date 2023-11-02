// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowGrenade.h"
#include "LooterShooter/Character/LSPlayer.h"

UThrowGrenade::UThrowGrenade()
{
	SkillCoolTime = 5.0f;
	MPCost = 10.0f;
	CurrentSkillState = ESkillState::READY;
}

void UThrowGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UThrowGrenade::Init(APawn* Player)
{
	Super::Init(Player);
	if (Player == nullptr)
	{
		LSLOG(Warning, TEXT("Wrong"));
	}
	LSPlayer = Cast<ALSPlayer>(Player);
}

bool UThrowGrenade::CastSkill()
{
	Super::CastSkill();

	LSLOG(Warning, TEXT("Cast Skill"));

	if (LSPlayer)
	{
		LSPlayer->PlayThrowGrenadeMontage();
	}

	return true;
}
