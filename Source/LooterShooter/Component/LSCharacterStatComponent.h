// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULSCharacterStatComponent();

	/** 레벨에 따른 스탯 설정 */
	void SetNewLevel(int32 NewLevel);

	void SetDamage(float NewDamage);

	float GetAttackDamage() const;

	void SetHP(float NewHP);

	float GetHPRatio();

	float GetCurrentHP() const
	{
		return CurrentHP;
	}

	// int32 GetDropExp() const;
	
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;


protected:
	virtual void BeginPlay() override;
	
	virtual void InitializeComponent() override;	

private:
	struct FLSPlayerData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

/*
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
*/
		
};
