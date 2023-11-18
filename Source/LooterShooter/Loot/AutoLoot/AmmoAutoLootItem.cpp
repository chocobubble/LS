// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoAutoLootItem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
#include "LooterShooter/Types/AmmoType.h"

AAmmoAutoLootItem::AAmmoAutoLootItem()
{
	DropAmount = 50;
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_AMMO(TEXT("/Game/sA_PickupSet_1/Fx/NiagaraSystems/NS_AMMO.NS_AMMO"));
	if (NS_AMMO.Succeeded())
	{
		EffectComponent->SetAsset(NS_AMMO.Object);
	}
}

void AAmmoAutoLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer)
	{
		ULSResourceManageComponent* ResourceManager = LSPlayer->GetResourceManager();
		if (ResourceManager)
		{
			int32 CurrentAmmo = ResourceManager->GetCurrentAmmo(EAmmoType::EAT_Rifle);
			ResourceManager->SetCurrentAmmo(EAmmoType::EAT_Rifle, CurrentAmmo + DropAmount);
		}
	}
	Destroy();
}
