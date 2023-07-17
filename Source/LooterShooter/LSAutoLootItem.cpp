// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAutoLootItem.h"
#include "LSCharacter.h"

ALSAutoLootItem::ALSAutoLootItem()
{
    LSLOG_S(Warning);
    //ALSLootItem();

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOOTITEM(TEXT("/Game/LS/Meshes/SM_LootItem_01.SM_LootItem_01"));
	if (SM_LOOTITEM.Succeeded())
	{
		LootItem->SetStaticMesh(SM_LOOTITEM.Object);
	}
	else
	{
		LSLOG_S(Warning);
	}

/*
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_ITEMDROP(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (P_ITEMDROP.Succeeded())
	{
		Effect->SetTemplate(P_ITEMDROP.Object);
		// Effect->bAutoActivate = true;
	}
	else 
	{
		LSLOG_S(Warning);
	}
*/
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

void ALSAutoLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	LSLOG_S(Warning);

	ALSCharacter* LSCharacter = Cast<ALSCharacter>(OtherActor);
	LSCHECK(nullptr != LSCharacter);

	if (nullptr != LSCharacter)// && nullptr != WeaponItemClass)
	{
		LSLOG(Warning, TEXT("OnCharacterOverlap"));
        Destroy();
	}
	else
	{
		LSLOG(Warning, TEXT("LSCharacter is nullptr when CharacterOverlap"));
	}
}
