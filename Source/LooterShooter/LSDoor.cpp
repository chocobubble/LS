// Fill out your copyright notice in the Description page of Project Settings.

#include "LSDoor.h"

ALSDoor::ALSDoor()
{
 	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/LS/Meshes/SM_Door.SM_Door");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DOOR(*AssetPath);
	if (SM_DOOR.Succeeded())
	{
		Mesh->SetStaticMesh(SM_DOOR.Object);
	}
	else 
	{
		LSLOG_S(Warning);
	}
}

void ALSDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

