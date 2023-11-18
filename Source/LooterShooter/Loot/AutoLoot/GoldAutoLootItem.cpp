// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldAutoLootItem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
#include "LooterShooter/Character/LSPlayerState.h"

AGoldAutoLootItem::AGoldAutoLootItem()
{
	DropAmount = 500;
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_COIN(TEXT("/Game/sA_PickupSet_1/Fx/NiagaraSystems/NS_Coin.NS_Coin"));
	if (NS_COIN.Succeeded())
	{
		EffectComponent->SetAsset(NS_COIN.Object);
	}
}

void AGoldAutoLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer)
	{
		ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(LSPlayer->GetPlayerState());
		if (LSPlayerState && LSPlayer->GetResourceManager())
		{
			float CurrentPlayerGold = LSPlayerState->GetCurrentGold();
			LSPlayer->GetResourceManager()->SetGoldAmount(CurrentPlayerGold + DropAmount);
		}
	}
	Destroy();
}
