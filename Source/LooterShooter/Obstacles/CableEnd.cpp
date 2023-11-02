// Fill out your copyright notice in the Description page of Project Settings.


#include "CableEnd.h"

ACableEnd::ACableEnd()
{
 	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
}

void ACableEnd::DestoryCableEnd()
{
	Destroy();
}

void ACableEnd::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			DestoryTimerHandle,
			this,
			&ACableEnd::DestoryCableEnd,
			DestoryTime
		);
	}
}

