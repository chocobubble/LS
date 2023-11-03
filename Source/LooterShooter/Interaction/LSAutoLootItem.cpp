// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAutoLootItem.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Component/LSCharacterStatComponent.h"
#include "LooterShooter/Component/LSDefenseComponent.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
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
		case ELootItemType::ELIT_Gold:
		{
			LSPlayer->GetResourceManager()->SetGoldAmount(LootingAmount);
			break;
		}
		case ELootItemType::ELIT_HP:
		{
			LSPlayer->GetDefenseManager()->SetHP(LSPlayer->GetDefenseManager()->GetCurrentHP() + LootingAmount);
			break;
		}	
		case ELootItemType::ELIT_MP:
		{
			break;
		}
		case ELootItemType::ELIT_RifleAmmo:
		{
			ULSResourceManageComponent* ResourceManager = LSPlayer->GetResourceManager();
			if (ResourceManager)
			{
				int32 CurrentAmmo = ResourceManager->GetCurrentAmmo(EAmmoType::EAT_Rifle);
				int32 MaxAmmo = ResourceManager->GetMaxAmmo(EAmmoType::EAT_Rifle);
				int32 FinalAmmo = (CurrentAmmo + LootingAmount) > MaxAmmo ? MaxAmmo : (CurrentAmmo + LootingAmount);
				ResourceManager->SetCurrentAmmo(EAmmoType::EAT_Rifle, FinalAmmo);
			}
			break;
		}
		case ELootItemType::ELIT_ShotgunAmmo:
		{
			// TODO
			break;
		}
		case ELootItemType::ELIT_PistolAmmo:
		{
			// TODO
			break;
		}
	}	

    Destroy();
}