// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAutoLootItem.h"
#include "LSPlayer.h"
#include "LSPlayerStatComponent.h"

ALSAutoLootItem::ALSAutoLootItem()
{	
}


void ALSAutoLootItem::SetAutoLootItem(ELootItemType LootedItemType, int32 Amount)
{
	LootingAmount = Amount;
	LootItemType = LootedItemType;
	/*
	switch(LootedItemType)
	{
		case ELootItemType::GOLD:
		{
			LootItemType = ELootItemType::GOLD;
			break;
		}
		case ELootItemType::HP:
		{
			LootItemType = ELootItemType::HP;
			break;
		}
		case ELootItemType::MP:
		{
			LootItemType = ELootItemType::MP;
			break;
		}
		case ELootItemType::RIFLEAMMO:
		{
			LootItemType = ELootItemType::RIFLEAMMO;
			break;
		}
		case ELootItemType::SHOTGUNAMMO:
		{
			LootItemType = ELootItemType::SHOTGUNAMMO;
			break;
		}
		case ELootItemType::PISTOLAMMO:
		{
			LootItemType = ELootItemType::PISTOLAMMO;
			break;
		}
	}
	*/
}


void ALSAutoLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	LSLOG_S(Warning);

	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	LSCHECK(nullptr != LSPlayer);

	if (nullptr != LSPlayer)// && nullptr != WeaponItemClass)
	{
		LSLOG(Warning, TEXT("OnCharacterOverlap"));
		switch(LootItemType)
	{
		case ELootItemType::GOLD:
		{
			LSPlayer->ResourceManager->SetGoldAmount(LootingAmount);
			break;
		}
		case ELootItemType::HP:
		{
			LSPlayer->CharacterStat->SetHP(LSPlayer->CharacterStat->GetCurrentHP() + LootingAmount);
			break;
		}
		case ELootItemType::MP:
		{
			//LSPlayer->ResourceManager->SetHP(LSPlayer->CharacterStat->GetCurrentMP() + LootingAmount);
			break;
		}
		case ELootItemType::RIFLEAMMO:
		{
			LSPlayer->ResourceManager->SetCurrentAmmo(EAmmoType::RIFLE, LootingAmount);
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
	else
	{
		LSLOG(Warning, TEXT("LSPlayer is nullptr when CharacterOverlap"));
	}
}