// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSWeaponAbilityComponent.generated.h"

class ALSWeaponInstance;

UPROPERTY(BlueprintType)
struct WeaponAbility
{
public:
	WeaponAbility(FString Name, float Stat) : AbilityName(Name), AbilityStat(Stat) {}
	virtual void ApplyAbility(ALSWeaponInstance WeaponInstance);
	FString* GetAbilityText() const;
private:
	FString AbilityName;
	float AbilityStat;
};

class BulletDamageAbility : public WeaponAbility
{
	virtual void ApplyAbility() override;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSWeaponAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULSWeaponAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
