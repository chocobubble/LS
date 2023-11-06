// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowGrenade.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Skill/LSGrenade.h"

UThrowGrenade::UThrowGrenade()
{
	SkillCoolTime = 5.0f;
	MPCost = 10.0f;
	CurrentSkillState = ESkillState::ESS_Ready;

	LSGrenadeClass = ALSGrenade::StaticClass();
}

void UThrowGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UThrowGrenade::Init(APawn* Player)
{
	Super::Init(Player);

	if (Player)
	{
		LSPlayer = Cast<ALSPlayer>(Player);
	}
}

bool UThrowGrenade::CastSkill()
{
	Super::CastSkill();

	if (CurrentSkillState != ESkillState::ESS_Ready)
	{
		return false;
	}

	if (GetWorld() == nullptr || LSPlayer == nullptr || LSGrenadeClass == nullptr)
	{
		return false;
	}

	LSPlayer->PlayThrowGrenadeMontage();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			ThrowTimerHandle,
			FTimerDelegate::CreateLambda([this]() -> void {
				ThrowGrenade(); }),
				0.5f, // 던지는 시간
				false
				);
	}

	CurrentSkillState = ESkillState::ESS_Cool;

	return true;
}

void UThrowGrenade::ThrowGrenade()
{
	if (GetWorld() == nullptr || LSPlayer == nullptr || LSGrenadeClass == nullptr)
	{
		return;
	}

	FVector ThrowSocketPos = LSPlayer->GetThrowSocketPos();
	Grenade = GetWorld()->SpawnActor<ALSGrenade>(
		LSGrenadeClass,
		ThrowSocketPos,
		(LSPlayer->GetHitPos() - ThrowSocketPos).Rotation()
	);

	if (Grenade)
	{
		if (LSPlayer)
		{
			Grenade->Init(LSPlayer);
		}
		Grenade->Throw();
	}


}
