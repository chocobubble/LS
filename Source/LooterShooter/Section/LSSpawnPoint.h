// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSSpawnPoint.generated.h"

class UBoxComponent;

UCLASS()
class LOOTERSHOOTER_API ALSSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSSpawnPoint();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	UBoxComponent* SpawnPoint;
};
