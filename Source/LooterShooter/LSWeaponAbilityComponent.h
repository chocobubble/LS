// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSWeaponAbilityComponent.generated.h"

class ALSWeaponInstance;
/*
USTRUCT(BlueprintType)
struct FWeaponAbility
{
	GENERATED_BODY()
public:
	FWeaponAbility(float Stat) : AbilityStat(Stat) {}
	//FWeaponAbility(FString Name, float Stat) : AbilityName(Name), AbilityStat(Stat) {}
	virtual ~FWeaponAbility() = default;
	virtual void ApplyAbility(ALSWeaponInstance* WeaponInstance) {}
	virtual FString GetAbilityText() {return FString();}
protected:
	UPROPERTY()
	FString AbilityName;
	UPROPERTY()
	float AbilityStat;
};

USTRUCT(BlueprintType)
struct FBulletDamageAbility : public FWeaponAbility
{
	GENERATED_BODY()

	FBulletDamageAbility(float Stat) : FWeaponAbility(Stat) {}

	virtual void ApplyAbility(ALSWeaponInstance* WeaponInstance) override;
	virtual FString GetAbilityText() override;
};
*/

UCLASS()
class UWeaponAbility : public UObject
{
	GENERATED_BODY()
public:
	// UWeaponAbility(){}
	// UWeaponAbility(float Stat) : AbilityStat(Stat) {}
	//FWeaponAbility(FString Name, float Stat) : AbilityName(Name), AbilityStat(Stat) {}
	//virtual ~UWeaponAbility() = default;
	virtual void ApplyAbility(ALSWeaponInstance* WeaponInstance) {}
	virtual void SetAbilityStat(float Stat);
	// virtual FString GetAbilityText() {return FString();}
protected:
/*
	UPROPERTY()
	FString AbilityName;
*/	
	UPROPERTY()
	float AbilityStat;
};

UCLASS()
class UBulletDamageAbility : public UWeaponAbility
{
	GENERATED_BODY()
public:
	// UBulletDamageAbility() {}
	// UBulletDamageAbility(float Stat) : UWeaponAbility(Stat) {}

	virtual void ApplyAbility(ALSWeaponInstance* WeaponInstance) override;
	// virtual FString GetAbilityText() override;
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

private:
	UPROPERTY()
	TArray<UWeaponAbility*> AbilityList;

public:	

	void EnhanceWeaponStat(ALSWeaponInstance* WeaponInstance);


	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
