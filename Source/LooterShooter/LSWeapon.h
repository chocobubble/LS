// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSWeapon.generated.h"

UCLASS()
class LOOTERSHOOTER_API ALSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSWeapon();

	float GetAttackRange() const;
	float GetAttackDamage() const;
	float GetAttackModifier() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* RifleWeapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDamageMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDamageMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackModifierMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackModifierMax;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float AttackDamage;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float AttackModifier;
};
