// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSkillComponent.h"
#include "LooterShooter/Skill/LSSkill.h"
#include "LooterShooter/Skill/ThrowGrenade.h"
#include "LooterShooter/Skill/GrapplingHook.h"
#include "LooterShooter/Component/LSDefenseComponent.h"
#include "LooterShooter/UI/LSHUDWidget.h"

ULSSkillComponent::ULSSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void ULSSkillComponent::CastGrapplingHook()
{
	if (SkillList.Num() >= 1)
	{
		LSLOG(Warning, TEXT("Cast Grappling Hook"));
		ULSSkill* FirstSkill = SkillList[0];
		if (FirstSkill)
		{
			if (FirstSkill->CastSkill())
			{
				LSLOG(Warning, TEXT("Cast Grappling Hook Success"));
			}
		}
	}
}

void ULSSkillComponent::CastFirstSkill()
{
	if (SkillList.Num() >= 2)
	{
		LSLOG(Warning, TEXT("Cast First SKill"));
		if (DefenseManager == nullptr)
		{
			return;
		}

		float CurrentMP = DefenseManager->GetCurrentMP();
		ULSSkill* FirstSkill = SkillList[1];
		if (FirstSkill && CurrentMP >= FirstSkill->GetMPCost())
		{
			if (FirstSkill->CastSkill())
			{
				LSLOG(Warning, TEXT("Cast First SKill Success"));
				CurrentMP -= FirstSkill->GetMPCost();
				DefenseManager->SetMP(CurrentMP);
			}
		}
	}
}

void ULSSkillComponent::AddSkill(ULSSkill* Skill)
{
	int32 CurrentSkillNum = SkillList.Num();
	if (CurrentSkillNum < 4)
	{
		SkillList.Add(Skill);
	}
}

void ULSSkillComponent::Init(ULSDefenseComponent* DefenseComponent)
{
	DefenseManager = DefenseComponent;
}

void ULSSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	ULSSkill* SkillGrapplingHook = NewObject<UGrapplingHook>(this, UGrapplingHook::StaticClass());
	SkillGrapplingHook->Init(Cast<APawn>(GetOwner()));
	AddSkill(SkillGrapplingHook);

	ULSSkill* SkillThrowGrenade = NewObject<UThrowGrenade>(this, UThrowGrenade::StaticClass());
	SkillThrowGrenade->Init(Cast<APawn>(GetOwner()));
	AddSkill(SkillThrowGrenade);
}

void ULSSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SkillList.Num() > 0)
	{
		for (ULSSkill* Skill : SkillList)
		{
			if (Skill)
			{
				Skill->Tick(DeltaTime);
			}
		}
	}
}

