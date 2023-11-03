// Fill out your copyright notice in the Description page of Project Settings.


#include "LSItemBox.h"
#include "LooterShooter/Weapon/LSWeapon.h"
#include "Components/BoxComponent.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "Particles/ParticleSystemComponent.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"

ALSItemBox::ALSItemBox()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = Trigger;
	Trigger->SetBoxExtent(FVector(80.0f, 80.0f, 30.0f));
	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Box->SetupAttachment(RootComponent);
	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	Box->SetCollisionProfileName(TEXT("Interact"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}

	WeaponItemClass = ULSWeaponDefinition::StaticClass();
}

void ALSItemBox::BeginPlay()
{
	Super::BeginPlay();

	WeaponItem = NewObject<ULSWeaponDefinition>(Cast<ULSGameInstance>(GetGameInstance()), WeaponItemClass);
	// 테스트 용도
	WeaponItem->SetWeaponDefinitionData(EWeaponType::EWT_Rifle, 1, 1);
}

void ALSItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSItemBox::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALSItemBox::OnCharacterEndOverlap);
}

void ALSItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer)
	{
		LSPlayer->SetIsNearInteractableObject(true);
	}
}

void ALSItemBox::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex)
{
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer)
	{
		LSPlayer->SetIsNearInteractableObject(false);
	}
}

void ALSItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

void ALSItemBox::OpenChest()
{
	Effect->Activate(true);
	Box->SetHiddenInGame(true, true);
	SetActorEnableCollision(false);
	if (bIsDestroying)
	{
		return;
	}
	bIsDestroying = true;
}

ULSWeaponDefinition* ALSItemBox::GetWeaponItem()
{
	Destroy();
	return WeaponItem;
}

void ALSItemBox::SetWeaponItem(ALSPlayer* LSPlayer)
{
	if (WeaponItem)
	{
		WeaponItem = NewObject<ULSWeaponDefinition>(LSPlayer);
		WeaponItem->SetWeaponDefinitionData(EWeaponType::EWT_Rifle, 1, 1);
	}
}

