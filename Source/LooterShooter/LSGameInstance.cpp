// Fill out your copyright notice in the Description page of Project Settings.

#include "LSGameInstance.h"

ULSGameInstance::ULSGameInstance()
{
    LSLOG_S(Warning);

    // FString PlayerDataPath = TEXT("/Game/LS/GameData/PlayerBaseData.PlayerBaseData");
    // static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSPLAYER(*PlayerDataPath);
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSPLAYER(TEXT("/Game/LS/GameData/PlayerBaseData.PlayerBaseData"));
    LSCHECK(DT_LSPLAYER.Succeeded());
    LSPlayerTable = DT_LSPLAYER.Object;
    LSCHECK(LSPlayerTable->GetRowMap().Num() > 0);

    FString MonsterDataPath = TEXT("/Game/LS/GameData/MonsterBaseData.MonsterBaseData");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSMONSTER(*MonsterDataPath);
    // static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSCHARACTER(TEXT("/Script/Engine.DataTable'/Game/LS/GameData/LSCD.LSCD'"));
    LSCHECK(DT_LSMONSTER.Succeeded());
    LSMonsterTable = DT_LSMONSTER.Object;
    LSCHECK(LSMonsterTable->GetRowMap().Num() > 0);

    FString WeaponDataPath = TEXT("/Game/LS/GameData/WeaponBaseData.WeaponBaseData");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSWEAPON(*WeaponDataPath);
    // static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSCHARACTER(TEXT("/Script/Engine.DataTable'/Game/LS/GameData/LSCD.LSCD'"));
    LSCHECK(DT_LSWEAPON.Succeeded());
    LSWeaponTable = DT_LSWEAPON.Object;
    LSCHECK(LSWeaponTable->GetRowMap().Num() > 0);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_GOLD(TEXT("/Game/LS/Meshes/SM_LootItem_Gold.SM_LootItem_Gold"));
    if (SM_LOOTITEM_GOLD.Succeeded())
    {
        // GoldMesh->SetStaticMesh(SM_LOOTITEM.Object);
        GoldMesh = SM_LOOTITEM_GOLD.Object;
    }
    else
    {
        LSLOG_S(Error);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_HP(TEXT("/Game/LS/Meshes/SM_LootItem_HP.SM_LootItem_HP"));
    if (SM_LOOTITEM_HP.Succeeded())
    {
        HPMesh = SM_LOOTITEM_HP.Object;
    }
    else
    {
        LSLOG_S(Error);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_MP(TEXT("/Game/LS/Meshes/SM_LootItem_MP.SM_LootItem_MP"));
    if (SM_LOOTITEM_MP.Succeeded())
    {
        MPMesh = SM_LOOTITEM_MP.Object;
    }
    else
    {
        LSLOG_S(Error);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_RIFLE_AMMO(TEXT("/Game/LS/Meshes/SM_LootItem_Rifle_Ammo.SM_LootItem_Rifle_Ammo"));
    if (SM_LOOTITEM_RIFLE_AMMO.Succeeded())
    {
        RifleAmmoMesh = SM_LOOTITEM_RIFLE_AMMO.Object;
    }
    else
    {
        LSLOG_S(Error);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_SHOTGUN_AMMO(TEXT("/Game/LS/Meshes/SM_LootItem_Shotgun_Ammo.SM_LootItem_Shotgun_Ammo"));
    if (SM_LOOTITEM_SHOTGUN_AMMO.Succeeded())
    {
        ShotgunAmmoMesh = SM_LOOTITEM_SHOTGUN_AMMO.Object;
    }
    else
    {
        LSLOG_S(Error);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_PISTOL_AMMO(TEXT("/Game/LS/Meshes/SM_LootItem_Pistol_Ammo.SM_LootItem_Pistol_Ammo"));
    if (SM_LOOTITEM_PISTOL_AMMO.Succeeded())
    {
        PistolAmmoMesh = SM_LOOTITEM_PISTOL_AMMO.Object;
    }
    else
    {
        LSLOG_S(Error);
    }
}

void ULSGameInstance::Init()
{
    Super::Init();
}

FLSPlayerData* ULSGameInstance::GetLSPlayerData(int32 Level)
{
    if (LSPlayerTable == nullptr)
    {
        LSLOG_S(Warning);
        return nullptr;
    }
    return LSPlayerTable->FindRow<FLSPlayerData>(*FString::FromInt(Level), TEXT(""));
}

FLSMonsterData* ULSGameInstance::GetLSMonsterData(int32 Level)
{
    if (LSMonsterTable == nullptr)
    {
        LSLOG_S(Warning);
        return nullptr;
    }
    return LSMonsterTable->FindRow<FLSMonsterData>(*FString::FromInt(Level), TEXT(""));
}

FLSWeaponBaseData* ULSGameInstance::GetLSWeaponData(int32 Level)
{
    if (LSWeaponTable == nullptr)
    {
        LSLOG_S(Warning);
        return nullptr;
    }
    return LSWeaponTable->FindRow<FLSWeaponBaseData>(*FString::FromInt(Level), TEXT(""));
}

void ULSGameInstance::SpawnAutoLootItem(FVector SpawnLocation, ELootItemType LootedItemType, int32 Amount)
{
    TWeakObjectPtr<ALSAutoLootItem> AutoLootItem = GetWorld()->SpawnActor<ALSAutoLootItem>(SpawnLocation, FRotator::ZeroRotator);
    AutoLootItem->SetAutoLootItem(LootedItemType, Amount);
    switch(LootedItemType)
	{
		case ELootItemType::GOLD:
		{
			AutoLootItem->ItemMesh->SetStaticMesh(GoldMesh);
			break;
        }
        case ELootItemType::HP:
		{
			AutoLootItem->ItemMesh->SetStaticMesh(HPMesh);
			break;
        }
        case ELootItemType::MP:
		{
			AutoLootItem->ItemMesh->SetStaticMesh(MPMesh);
			break;
        }
        case ELootItemType::RIFLEAMMO:
		{
			AutoLootItem->ItemMesh->SetStaticMesh(RifleAmmoMesh);
			break;
        }
        case ELootItemType::SHOTGUNAMMO:
		{
			AutoLootItem->ItemMesh->SetStaticMesh(ShotgunAmmoMesh);
			break;
        }
        case ELootItemType::PISTOLAMMO:
		{
			AutoLootItem->ItemMesh->SetStaticMesh(PistolAmmoMesh);
			break;
        }
	}
}	