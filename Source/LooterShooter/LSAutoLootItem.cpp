// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAutoLootItem.h"
#include "LSCharacter.h"
#include "LSCharacterStatComponent.h"

ALSAutoLootItem::ALSAutoLootItem()
{	
}


void ALSAutoLootItem::SetAutoLootItem(ELootItemType LootedItemType, int32 Amount)
{
	LootingAmount = Amount;
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
}


void ALSAutoLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	LSLOG_S(Warning);

	ALSCharacter* LSCharacter = Cast<ALSCharacter>(OtherActor);
	LSCHECK(nullptr != LSCharacter);

	if (nullptr != LSCharacter)// && nullptr != WeaponItemClass)
	{
		LSLOG(Warning, TEXT("OnCharacterOverlap"));
		switch(LootItemType)
	{
		case ELootItemType::GOLD:
		{
			LSCharacter->ResourceManager->SetGoldAmount(LootingAmount);
			break;
		}
		case ELootItemType::HP:
		{
			LSCharacter->CharacterStat->SetHP(LSCharacter->CharacterStat->GetCurrentHP() + LootingAmount);
			break;
		}
		case ELootItemType::MP:
		{
			LSCharacter->ResourceManager->SetHP(LSCharacter->CharacterStat->GetCurrentMP() + LootingAmount);
			break;
		}
		case ELootItemType::RIFLEAMMO:
		{
			LSCharacter->ResourceManager->SetCurrentAmmo(EAmmoType::RIFLE, LootingAmount);
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
		LSLOG(Warning, TEXT("LSCharacter is nullptr when CharacterOverlap"));
	}
}