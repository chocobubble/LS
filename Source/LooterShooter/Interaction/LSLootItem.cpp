// Fill out your copyright notice in the Description page of Project Settings.


#include "LSLootItem.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALSLootItem::ALSLootItem()
{
	LSLOG(Warning, TEXT("ALSLootItem Contstructor"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	 
	LootItemType = ELootItemType::DEFAULT;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LOOTITEM"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	RootComponent = Trigger;
	ItemMesh->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);
	Trigger->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	Trigger->SetCollisionProfileName(TEXT("LootItem"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DEFAULTITEM(TEXT("/Game/LS/Meshes/Shape_Sphere.Shape_Sphere"));
	if (SM_DEFAULTITEM.Succeeded())
	{
		ItemMesh->SetStaticMesh(SM_DEFAULTITEM.Object);
	}
	else
	{
		LSLOG_S(Warning);
	}

	//LootItem->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	ItemMesh->SetCollisionProfileName(TEXT("NoCollision"));
/*
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_ITEMDROP(TEXT("/Game/LS/Particle/P_Default.P_Default"));
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

// Called when the game starts or when spawned
void ALSLootItem::BeginPlay()
{
	Super::BeginPlay();
}

void ALSLootItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSLootItem::OnCharacterOverlap);
}


void ALSLootItem::OnCharacterOverlap(
		UPrimitiveComponent * OverlappedComp, 
		AActor * OtherActor, 
		UPrimitiveComponent * OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult) {}

/*
// Called every frame
void ALSLootItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
