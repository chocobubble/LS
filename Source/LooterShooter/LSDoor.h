// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSDoor.generated.h"

UCLASS()
class LOOTERSHOOTER_API ALSDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	UStaticMeshComponent* Mesh;

};
