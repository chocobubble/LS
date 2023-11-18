// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSection.h"
#include "Components/BoxComponent.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Interaction/LSItemBox.h"
#include "LooterShooter/GameMode/LSGameMode.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Interaction/LSSectionStarter.h"

ALSSection::ALSSection()
{
 	PrimaryActorTick.bCanEverTick = false; 

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ITEM(TEXT("/Game/Bazaar_Meshingun/Environment/Assets/Mesh/Architecture/SM_GoldPoint_01a.SM_GoldPoint_01a"));
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

	if (GetWorld() && SectionStarter == nullptr)
	{
		//FActorSpawnParameters SpawnParameters;
		//SpawnParameters.Owner = this;
		SectionStarter = GetWorld()->SpawnActor<ALSSectionStarter>(
			ALSSectionStarter::StaticClass(),
			GetActorLocation() + FVector(0.0f, 90.0f, 0.0f),
			GetActorRotation()
			//SpawnParameters
		);

		if (SectionStarter)
		{
			SectionStarter->SetOwner(this);
			SectionStarter->SetActorTransform(GetActorTransform());
			BindInteractableObject();
			SectionStarter->Init(this);
		}
	}
}

void ALSSection::SetState(ESectionState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	switch (NewState)
	{
		case ESectionState::ESS_Ready:
		{
			Trigger->SetCollisionProfileName(TEXT("LSTrigger"));
			CurrentState = NewState;
			break;
		}
		case ESectionState::ESS_Battle:
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			CurrentState = NewState;
			//BattleStart();
			break;
		}
		case ESectionState::ESS_Complete:
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			CurrentState = NewState;
			SectionClear();
			break;
		}
	}
}

void ALSSection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(bNoBattle ? ESectionState::ESS_Complete : ESectionState::ESS_Ready);
}

void ALSSection::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (CurrentState == ESectionState::ESS_Ready)
	{
		//SetState(ESectionState::ESS_Battle);
	}
	
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer)
	{
		LSPlayerController = Cast<ALSPlayerController>(LSPlayer->GetController());
		MonsterLevel = LSPlayer->GetPlayerLevel();
	}
}

void ALSSection::OnKeyNPCDestroyed(AActor* DestroyedActor)
{
}

void ALSSection::BindInteractableObject()
{
	LSLOG(Warning, TEXT("Bind Interactable Object"));
	if (SectionStarter)
	{
		LSLOG(Warning, TEXT("Bind Interactable Object"));
		SectionStarter->OnCompleteInteraction.BindUObject(this, &ALSSection::BattleStart);
	}
}

void ALSSection::BattleStart()
{
	LSLOG(Warning, TEXT("%s , before start battle"), *GetName());
	if (CurrentState == ESectionState::ESS_Ready)
	{
		LSLOG(Warning, TEXT("start battle"));
		SetState(ESectionState::ESS_Battle);
	}
}

void ALSSection::SectionClear() {}


