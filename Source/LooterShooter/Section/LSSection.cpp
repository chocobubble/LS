// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSection.h"
#include "Components/BoxComponent.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Interaction/LSItemBox.h"
#include "LooterShooter/GameMode/LSGameMode.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayer.h"

ALSSection::ALSSection()
{
 	PrimaryActorTick.bCanEverTick = false; 

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ITEMTEXT("/Game/LS/Meshes/SM_floor.SM_floor");
	if (ITEM.Succeeded())
	{
		Mesh->SetStaticMesh(ITEM.Object);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetBoxExtent(FVector(200.0f, 100.0f, 25.0f));
	Trigger->SetCollisionProfileName(TEXT("LSTrigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSSection::OnTriggerBeginOverlap);
}

void ALSSection::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALSSection::SetState(ESectionState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	switch (NewState)
	{
		case ESectionState::READY:
			Trigger->SetCollisionProfileName(TEXT("LSTrigger"));
			break;
		
		case ESectionState::BATTLE:
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			BattleStart();
			break;
		
		case ESectionState::COMPLETE:
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			SectionClear();
			break;
		
	}
	CurrentState = NewState;
}

void ALSSection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void ALSSection::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentState == ESectionState::READY)
	{
		SetState(ESectionState::BATTLE);
	}
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer)
	{
		LSPlayerController = Cast<ALSPlayerController>(LSPlayer->GetController());
	}
}

void ALSSection::OnKeyNPCDestroyed(AActor* DestroyedActor)
{
//	ALSGameMode* LSGameMode = Cast<ALSGameMode>(GetWorld()->GetAuthGameMode());

}

void ALSSection::BattleStart() {}

void ALSSection::SectionClear() {}


