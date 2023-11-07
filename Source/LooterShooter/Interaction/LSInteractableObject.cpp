// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInteractableObject.h"
#include "Components/BoxComponent.h"
#include "LooterShooter/Character/LSPlayer.h"

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

void ALSInteractableObject::Interact()
{
	//OnCompleteInteraction.Execute();
}

void ALSInteractableObject::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	LSLOG(Warning, TEXT("Overlap"));
	OverlappedCharacter = Cast<ALSPlayer>(OtherActor);
	if (OverlappedCharacter)
	{
		OverlappedCharacter->SetInteractingObject(this);
		OverlappedCharacter->SetIsNearInteractableObject(true);
		OverlappedCharacter->SetCanInteract(true);
	}

}