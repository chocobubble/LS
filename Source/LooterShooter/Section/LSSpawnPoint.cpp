// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSpawnPoint.h"
#include "Components/BoxComponent.h"

ALSSpawnPoint::ALSSpawnPoint()
{
 	PrimaryActorTick.bCanEverTick = false;

	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = SpawnPoint;

}

void ALSSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}


