// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSectionStarter.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Section/LSSection.h"

ALSSectionStarter::ALSSectionStarter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALSSectionStarter::Init(ALSSection* Section)
{
	StartBattleSection = Section;
}

void ALSSectionStarter::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
/*
	OverlappedCharacter = Cast<ALSPlayer>(OtherActor);
	if (OverlappedCharacter)
	{
		OverlappedCharacter->SetInteractingObject(this);
		OverlappedCharacter->SetIsNearInteractableObject(true);
	}
*/
}

void ALSSectionStarter::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCharacterEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);	
}

void ALSSectionStarter::Interact()
{
	LSLOG(Warning, TEXT("Interact"));
	if (StartBattleSection && bIsSectionReady)
	{
		LSLOG(Warning, TEXT("Start Battle"));
		OnCompleteInteraction.Execute();
		//StartBattleSection->BattleStart();
		bIsSectionReady = false;
	}
}