// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSSkillComponent.generated.h"

class ULSSkill;
class ULSDefenseComponent;
class ULSHUDWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULSSkillComponent();

	void CastGrapplingHook();

	void CastFirstSkill();

	void AddSkill(ULSSkill* Skill);

	void Init(ULSDefenseComponent* DefenseComponent);

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	TArray<ULSSkill*> SkillList;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 MaxSkillNum = 4;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	ULSDefenseComponent* DefenseManager;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	ULSHUDWidget* HUD;

public:
	ULSSkill* GetGrapplingHookSkill()
	{
		return SkillList.Num() > 0 ? SkillList[0] : nullptr;
	}

	ULSSkill* GetFirstSkill()
	{
		return SkillList.Num() > 1 ? SkillList[1] : nullptr;
	}
};
