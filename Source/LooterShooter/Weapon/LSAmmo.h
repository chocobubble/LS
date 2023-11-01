// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSAmmo.generated.h"

class UProjectileMovementComponent;

UCLASS()
class LOOTERSHOOTER_API ALSAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSAmmo();

	void Fire(const FVector& Dir);

	FTimerHandle OnLifeTimerHandle = {};

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector FireDir = FVector::ZeroVector;
};
