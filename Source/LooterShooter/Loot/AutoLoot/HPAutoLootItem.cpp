// Fill out your copyright notice in the Description page of Project Settings.


#include "HPAutoLootItem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Component/LSDefenseComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


AHPAutoLootItem::AHPAutoLootItem()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_HP(TEXT("/Game/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_3.NS_Pickup_3"));
	if (NS_HP.Succeeded())
	{
		EffectComponent->SetAsset(NS_HP.Object);
	}

	DropAmount = 200;
}

void AHPAutoLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer && LSPlayer->GetDefenseManager())
	{
		float CurrentPlayerHP = LSPlayer->GetDefenseManager()->GetCurrentHP();
		LSPlayer->GetDefenseManager()->SetHP(CurrentPlayerHP + DropAmount);
		LSLOG(Warning, TEXT("HP Gain"));
	}
	Destroy();
}