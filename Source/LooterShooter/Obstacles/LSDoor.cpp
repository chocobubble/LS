// Fill out your copyright notice in the Description page of Project Settings.

#include "LSDoor.h"

ALSDoor::ALSDoor()
{
 	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DOOR(TEXT("/Game/LS/Meshes/SM_Door.SM_Door"));
	if (SM_DOOR.Succeeded())
	{
		Mesh->SetStaticMesh(SM_DOOR.Object);
	}
}

void ALSDoor::BeginPlay()
{
	Super::BeginPlay();
}


