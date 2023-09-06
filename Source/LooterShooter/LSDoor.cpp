// Fill out your copyright notice in the Description page of Project Settings.


#include "LSDoor.h"

// Sets default values
ALSDoor::ALSDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void ALSDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

