// Fill out your copyright notice in the Description page of Project Settings.


#include "LSItemBox.h"

// Sets default values
ALSItemBox::ALSItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent
}

// Called when the game starts or when spawned
void ALSItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

