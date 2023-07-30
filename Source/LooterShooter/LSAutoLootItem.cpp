// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAutoLootItem.h"
#include "LSCharacter.h"
#include "LSCharacterStatComponent.h"

ALSAutoLootItem::ALSAutoLootItem()
{
	
}

/*
void ALSAutoLootItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALSAutoLootItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSItemBox::OnCharacterOverlap);
}
*/

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
	/*
	switch(LootedItemType)
	{
		case ELootItemType::GOLD:
		{
			LootItemType = ELootItemType::GOLD;

			static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM(TEXT("/Game/LS/Meshes/SM_LootItem_Gold.SM_LootItem_Gold"));
			if (SM_LOOTITEM.Succeeded())
			{
				ItemMesh->SetStaticMesh(SM_LOOTITEM.Object);
			}
			else
			{
				LSLOG_S(Error);
			}
		}
		case ELootItemType::HP:
		{
			LootItemType = ELootItemType::HP;
			static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM(TEXT("/Game/LS/Meshes/SM_LootItem_HP.SM_LootItem_HP"));
			if (SM_LOOTITEM.Succeeded())
			{
				ItemMesh->SetStaticMesh(SM_LOOTITEM.Object);
			}
			else
			{
				LSLOG_S(Error);
			}
		}
		case ELootItemType::MP:
		{
			LootItemType = ELootItemType::MP;
			static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM(TEXT("/Game/LS/Meshes/SM_LootItem_MP.SM_LootItem_MP"));
			if (SM_LOOTITEM.Succeeded())
			{
				ItemMesh->SetStaticMesh(SM_LOOTITEM.Object);
			}
			else
			{
				LSLOG_S(Error);
			}
		}
		case ELootItemType::RIFLEAMMO:
		{
			LootItemType = ELootItemType::RIFLEAMMO;
			static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM(TEXT("/Game/LS/Meshes/SM_LootItem_Rifle_Ammo.SM_LootItem_Rifle_Ammo"));
			if (SM_LOOTITEM.Succeeded())
			{
				ItemMesh->SetStaticMesh(SM_LOOTITEM.Object);
			}
			else
			{
				LSLOG_S(Error);
			}
		}
		case ELootItemType::SHOTGUNAMMO:
		{
			LootItemType = ELootItemType::SHOTGUNAMMO;
			static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM(TEXT("/Game/LS/Meshes/SM_LootItem_Shotgun_Ammo.SM_LootItem_Shotgun_Ammo"));
			if (SM_LOOTITEM.Succeeded())
			{
				ItemMesh->SetStaticMesh(SM_LOOTITEM.Object);
			}
			else
			{
				LSLOG_S(Error);
			}
		}
		case ELootItemType::PISTOLAMMO:
		{
			LootItemType = ELootItemType::PISTOLAMMO;
			static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM(TEXT("/Game/LS/Meshes/SM_LootItem_Pistol_Ammo.SM_LootItem_Pistol_Ammo"));
			if (SM_LOOTITEM.Succeeded())
			{
				ItemMesh->SetStaticMesh(SM_LOOTITEM.Object);
			}
			else
			{
				LSLOG_S(Error);
			}
		}
	}
	*/
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
			LSCharacter->ResourceManager->SetGoldAmount(LootingAmount);
			break;
		}
		case ELootItemType::RIFLEAMMO:
		{
			LSCharacter->ResourceManager->SetCurrentAmmo(EAmmoType::RIFLE, LootingAmount);
			break;
		}
		case ELootItemType::SHOTGUNAMMO:
		{
			LSLOG(Warning, TEXT("Shotgun Ammo gain"));
			break;
		}
		case ELootItemType::PISTOLAMMO:
		{
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