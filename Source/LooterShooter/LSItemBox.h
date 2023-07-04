// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSItemBox.generated.h"

UCLASS()
class LOOTERSHOOTER_API ALSItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Catgory = Box)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Catgory = Box)
	UStaticMeshComponent* Box;
};
