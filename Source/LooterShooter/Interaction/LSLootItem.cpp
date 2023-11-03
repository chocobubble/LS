// Fill out your copyright notice in the Description page of Project Settings.


#include "LSLootItem.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Particles/ParticleSystemComponent.h"

ALSLootItem::ALSLootItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	Trigger->SetCollisionProfileName(TEXT("LootItem"));
	RootComponent = Trigger;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LOOTITEM"));
	ItemMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DEFAULTITEM(TEXT("/Game/LS/Meshes/Shape_Sphere.Shape_Sphere"));
	if (SM_DEFAULTITEM.Succeeded())
	{
		ItemMesh->SetStaticMesh(SM_DEFAULTITEM.Object);
	}
	ItemMesh->SetCollisionProfileName(TEXT("NoCollision"));

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(RootComponent);
	
	LootItemType = ELootItemType::ELIT_Default;
}

void ALSLootItem::BeginPlay()
{
	Super::BeginPlay();
}

void ALSLootItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSLootItem::OnCharacterOverlap);
}

void ALSLootItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

void ALSLootItem::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex) {}
