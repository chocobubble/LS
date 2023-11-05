// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSGrenade.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USoundCue;

UCLASS()
class LOOTERSHOOTER_API ALSGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSGrenade();

	void Throw();

	void Explode();

	void Init(APawn* Pawn);

	FTimerHandle OnLifeTimerHandle = {};

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* GrenadeMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* GrenadeMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	float ExplodeRange = 500.0f;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystem* ExplodeImpact;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	USoundCue* ExplodeSound;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystemComponent* ExplodeParticleComponent;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	APawn* Player;
};
