// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSDoor.generated.h"

UCLASS()
class LOOTERSHOOTER_API ALSDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSDoor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	UStaticMeshComponent* Mesh;
};
