// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInteractableObejct.h"
#include "Components/BoxComponent.h"

ALSInteractableObejct::ALSInteractableObejct()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = Trigger;
	Trigger->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	Trigger->SetCollisionProfileName(TEXT("LootItem"));
}

void ALSInteractableObejct::BeginPlay()
{
	Super::BeginPlay();
}

void ALSInteractableObejct::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSInteractableObejct::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALSInteractableObejct::OnCharacterEndOverlap);
}
