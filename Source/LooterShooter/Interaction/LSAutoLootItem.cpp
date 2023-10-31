// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAutoLootItem.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Component/LSCharacterStatComponent.h"
#include "LooterShooter/Component/LSDefenseComponent.h"
#include "LooterShooter/Types/LootItemType.h"

ALSAutoLootItem::ALSAutoLootItem()
{	
}

void ALSAutoLootItem::SetAutoLootItem(ELootItemType LootedItemType, int32 Amount)
{
	LootingAmount = Amount;
	LootItemType = LootedItemType;
}

void ALSAutoLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer == nullptr)
	{
		return;
	}
	
	switch(LootItemType)
	{
		case ELootItemType::GOLD:
		{
			LSPlayer->GetResourceManager()->SetGoldAmount(LootingAmount);
			break;
		}
		case ELootItemType::HP:
		{
			LSPlayer->GetDefenseManager()->SetHP(LSPlayer->GetDefenseManager()->GetCurrentHP() + LootingAmount);
			break;
		}	
		case ELootItemType::MP:
		{
			break;
		}
		case ELootItemType::RIFLEAMMO:
		{
			ULSResourceManageComponent* ResourceManager = LSPlayer->GetResourceManager();
			if (ResourceManager)
			{
				int32 CurrentAmmo = ResourceManager->GetCurrentAmmo(EAmmoType::RIFLE);
				int32 MaxAmmo = ResourceManager->GetMaxAmmo(EAmmoType::RIFLE);
				int32 FinalAmmo = (CurrentAmmo + LootingAmount) > MaxAmmo ? MaxAmmo : (CurrentAmmo + LootingAmount);
				ResourceManager->SetCurrentAmmo(EAmmoType::RIFLE, FinalAmmo);
			}
			break;
		}
		case ELootItemType::SHOTGUNAMMO:
		{
			// TODO
			LSLOG(Warning, TEXT("Shotgun Ammo gain"));
			break;
		}
		case ELootItemType::PISTOLAMMO:
		{
			// TODO
			LSLOG(Warning, TEXT("Pistol Ammo gain"));
			break;
		}
	}	
    Destroy();
}