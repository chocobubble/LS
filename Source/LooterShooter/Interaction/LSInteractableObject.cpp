// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInteractableObject.h"
#include "Components/BoxComponent.h"

ALSInteractableObject::ALSInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = Trigger;
	Trigger->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	Trigger->SetCollisionProfileName(TEXT("LootItem"));
}

void ALSInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

void ALSInteractableObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSInteractableObject::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALSInteractableObject::OnCharacterEndOverlap);
}
