// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSBullet.generated.h"

class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;

UCLASS()
class LOOTERSHOOTER_API ALSBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSBullet();

	void Fire();

	FTimerHandle OnLifeTimerHandle = {};

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystem* BulletTracer;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystemComponent* BulletTracerComponent;

public:
	UStaticMeshComponent* GetBulletMesh()
	{
		return Mesh;
	}
};
