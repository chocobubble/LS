// Fill out your copyright notice in the Description page of Project Settings.


#include "LSEnhanceItem.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "Components/BoxComponent.h"

ALSEnhanceItem::ALSEnhanceItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALSEnhanceItem::BeginPlay()
{
	Super::BeginPlay();

}

void ALSEnhanceItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ALSEnhanceItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappedCharacter = Cast<ALSPlayer>(OtherActor);
	if (OverlappedCharacter)
	{
		OverlappedCharacter->SetIsNearInteractableObject(true);
	}
}

void ALSEnhanceItem::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
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
