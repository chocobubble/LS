// Fill out your copyright notice in the Description page of Project Settings.


#include "LSEnhanceItem.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "Components/BoxComponent.h"

ALSEnhanceItem::ALSEnhanceItem()
{
	PrimaryActorTick.bCanEverTick = false;
/*
	// #include "Components/BoxComponent.h"
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	
	RootComponent = Trigger;
	
	Trigger->SetBoxExtent(FVector(80.0f, 80.0f, 30.0f));
	Trigger->SetCollisionProfileName(TEXT("Interact"));
*/
}

void ALSEnhanceItem::BeginPlay()
{
	Super::BeginPlay();

}

void ALSEnhanceItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSEnhanceItem::OnCharacterOverlap);
	//Trigger->OnComponentEndOverlap.AddDynamic(this, &ALSEnhanceItem::OnCharacterEndOverlap);
}

void ALSEnhanceItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	LSLOG_S(Warning);

	OverlappedCharacter = Cast<ALSPlayer>(OtherActor);
	if (OverlappedCharacter)
	{
		OverlappedCharacter->SetIsNearInteractableObject(true);
	}
}

void ALSEnhanceItem::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	LSLOG_S(Warning);

	OverlappedCharacter = Cast<ALSPlayer>(OtherActor);
	if (OverlappedCharacter)
	{
		OverlappedCharacter->SetIsNearInteractableObject(false);
	}
	OverlappedCharacter = nullptr;
}

void ALSEnhanceItem::OpenEnhanceUI()
{
	SetActorEnableCollision(false);

	if (OverlappedCharacter)
	{
		ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(OverlappedCharacter->GetController());
		if (LSPlayerController)
		{
			LSPlayerController->OnEnhanceUIOpen();
		}
	}
}
