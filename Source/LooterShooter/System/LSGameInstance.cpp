// Fill out your copyright notice in the Description page of Project Settings.

#include "LSGameInstance.h"

ULSGameInstance::ULSGameInstance()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_RIFLE(TEXT("/Game/LS/GameData/RifleBaseData.RifleBaseData"));
    if (DT_RIFLE.Succeeded())
    {
        LSRifleDataTable = DT_RIFLE.Object;
    }

    static ConstructorHelpers::FObjectFinder<UDataTable> DT_SHOTGUN(TEXT("/Game/LS/GameData/ShotgunBaseData.ShotgunBaseData"));
    if (DT_SHOTGUN.Succeeded())
    {
        LSShotgunDataTable = DT_SHOTGUN.Object;
    }
    
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_PISTOL(TEXT("/Game/LS/GameData/PistolBaseData.PistolBaseData"));
    if (DT_PISTOL.Succeeded())
    {
        LSPistolDataTable = DT_PISTOL.Object;
    }
    
    static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI_RIFLE(TEXT("/Game/LS/Meshes/MI_UI_Icon_ElimFeed_Rifle.MI_UI_Icon_ElimFeed_Rifle"));
    if (MI_RIFLE.Succeeded())
    {
        MI_Rifle = MI_RIFLE.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI_SHOTGUN(TEXT("/Game/LS/Meshes/MI_UI_Icon_ElimFeed_Shotgun.MI_UI_Icon_ElimFeed_Shotgun"));
    if (MI_SHOTGUN.Succeeded())
    {
        MI_Shotgun = MI_SHOTGUN.Object;
    }
    
    static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI_PISTOL(TEXT("/Game/LS/Meshes/MI_UI_Icon_ElimFeed_Pistol.MI_UI_Icon_ElimFeed_Pistol"));
    if (MI_PISTOL.Succeeded())
    {
        MI_Pistol = MI_PISTOL.Object;
    }
    
    
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSPLAYER(TEXT("/Game/LS/GameData/PlayerBaseData.PlayerBaseData"));
    if (DT_LSPLAYER.Succeeded())
    {
        LSPlayerTable = DT_LSPLAYER.Object;
    }
    
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LSMONSTER(TEXT("/Game/LS/GameData/MonsterBaseData.MonsterBaseData"));
    if (DT_LSMONSTER.Succeeded())
    {
        LSMonsterTable = DT_LSMONSTER.Object;
    }
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_GOLD(TEXT("/Game/LS/Meshes/SM_LootItem_Gold.SM_LootItem_Gold"));
    if (SM_LOOTITEM_GOLD.Succeeded())
    {
        GoldMesh = SM_LOOTITEM_GOLD.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_HP(TEXT("/Game/LS/Meshes/SM_LootItem_HP.SM_LootItem_HP"));
    if (SM_LOOTITEM_HP.Succeeded())
    {
        HPMesh = SM_LOOTITEM_HP.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_MP(TEXT("/Game/LS/Meshes/SM_LootItem_MP.SM_LootItem_MP"));
    if (SM_LOOTITEM_MP.Succeeded())
    {
        MPMesh = SM_LOOTITEM_MP.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_RIFLE_AMMO(TEXT("/Game/LS/Meshes/SM_LootItem_Rifle_Ammo.SM_LootItem_Rifle_Ammo"));
    if (SM_LOOTITEM_RIFLE_AMMO.Succeeded())
    {
        RifleAmmoMesh = SM_LOOTITEM_RIFLE_AMMO.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_SHOTGUN_AMMO(TEXT("/Game/LS/Meshes/SM_LootItem_Shotgun_Ammo.SM_LootItem_Shotgun_Ammo"));
    if (SM_LOOTITEM_SHOTGUN_AMMO.Succeeded())
    {
        ShotgunAmmoMesh = SM_LOOTITEM_SHOTGUN_AMMO.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM_PISTOL_AMMO(TEXT("/Game/LS/Meshes/SM_LootItem_Pistol_Ammo.SM_LootItem_Pistol_Ammo"));
    if (SM_LOOTITEM_PISTOL_AMMO.Succeeded())
    {
        PistolAmmoMesh = SM_LOOTITEM_PISTOL_AMMO.Object;
    }

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_RIFLE(TEXT("/Game/LS/Meshes/Assault_Rifle.Assault_Rifle"));
	if (SK_RIFLE.Succeeded())
	{
		RifleWeaponMesh = SK_RIFLE.Object;
	}

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SHOTGUN(TEXT("/Game/LS/Meshes/Shotgun.Shotgun"));
	if (SK_SHOTGUN.Succeeded())
	{
		ShotgunWeaponMesh = SK_SHOTGUN.Object;
	}

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_PISTOL(TEXT("/Game/LS/Meshes/Pistols.Pistols"));
	if (SK_PISTOL.Succeeded())
	{
		PistolWeaponMesh = SK_PISTOL.Object;
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
        return nullptr;
    }
    return LSPlayerTable->FindRow<FLSPlayerData>(*FString::FromInt(Level), TEXT(""));
}

FLSMonsterData* ULSGameInstance::GetLSMonsterData(int32 Level)
{
    if (LSMonsterTable == nullptr)
    {
        return nullptr;
    }
    return LSMonsterTable->FindRow<FLSMonsterData>(*FString::FromInt(Level), TEXT(""));
}

FLSWeaponBaseData* ULSGameInstance::GetWeaponData(EWeaponType WeaponType, int32 ItemLevel)
{
    switch(WeaponType)
    {
        case EWeaponType::RIFLE:
            if (LSRifleDataTable)
            {
                return LSRifleDataTable->FindRow<FLSWeaponBaseData>(*FString::FromInt(ItemLevel), TEXT(""));
            }
            break;
            
        case EWeaponType::SHOTGUN:
            if (LSShotgunDataTable)
            {
                return LSShotgunDataTable->FindRow<FLSWeaponBaseData>(*FString::FromInt(ItemLevel), TEXT(""));
            }
            break;

        case EWeaponType::PISTOL:
            if (LSPistolDataTable)
            {
                return LSPistolDataTable->FindRow<FLSWeaponBaseData>(*FString::FromInt(ItemLevel), TEXT(""));
            }
            break;
    }
    return nullptr;
}

void ULSGameInstance::SpawnAutoLootItem(FVector SpawnLocation, ELootItemType LootedItemType, int32 Amount)
{
    TWeakObjectPtr<ALSAutoLootItem> AutoLootItem = GetWorld()->SpawnActor<ALSAutoLootItem>(SpawnLocation, FRotator::ZeroRotator);
    if (AutoLootItem == nullptr)
    {
        return;
    }
    AutoLootItem->SetAutoLootItem(LootedItemType, Amount);
    switch(LootedItemType)
	{
		case ELootItemType::GOLD:
			AutoLootItem->ItemMesh->SetStaticMesh(GoldMesh);
			break;

        case ELootItemType::HP:
			AutoLootItem->ItemMesh->SetStaticMesh(HPMesh);
			break;

        case ELootItemType::MP:
			AutoLootItem->ItemMesh->SetStaticMesh(MPMesh);
			break;

        case ELootItemType::RIFLEAMMO:
			AutoLootItem->ItemMesh->SetStaticMesh(RifleAmmoMesh);
			break;

        case ELootItemType::SHOTGUNAMMO:
			AutoLootItem->ItemMesh->SetStaticMesh(ShotgunAmmoMesh);
			break;

        case ELootItemType::PISTOLAMMO:
			AutoLootItem->ItemMesh->SetStaticMesh(PistolAmmoMesh);
			break;

	}
}	