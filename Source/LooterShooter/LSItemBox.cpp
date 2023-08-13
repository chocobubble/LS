// Fill out your copyright notice in the Description page of Project Settings.


#include "LSItemBox.h"
#include "LSWeapon.h"
#include "Components/BoxComponent.h"
#include "LSPlayer.h"
#include "Particles/ParticleSystemComponent.h"
#include "LSWeaponDefinition.h"

// Sets default values
ALSItemBox::ALSItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// #include "Components/BoxComponent.h"
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(80.0f, 80.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}
	else
	{
		LSLOG_S(Warning);
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("Interact"));

	WeaponItemClass = ULSWeaponDefinition::StaticClass();

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}
}
// Called when the game starts or when spawned
void ALSItemBox::BeginPlay()
{
	Super::BeginPlay();


	// LSCHECK(GetWorld() != nullptr);
	WeaponItem = NewObject<ULSWeaponDefinition>(Cast<ULSGameInstance>(GetGameInstance()), WeaponItemClass);
	// NewWeapon-> invisible?
	WeaponItem->SetWeaponDefinitionData(EWeaponType::RIFLE, 8);		

}

void ALSItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSItemBox::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALSItemBox::OnCharacterEndOverlap);
}

void ALSItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	LSLOG_S(Warning);

	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	LSCHECK(nullptr != LSPlayer);
	LSPlayer->SetIsNearInteractableObject(true);

}

void ALSItemBox::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex)
{
	LSLOG_S(Warning);

	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	LSCHECK(nullptr != LSPlayer);
	LSPlayer->SetIsNearInteractableObject(false);
}

void ALSItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	Destroy();
}

void ALSItemBox::OpenChest()
{
	
	Effect->Activate(true);
	Box->SetHiddenInGame(true, true);
	SetActorEnableCollision(false);
	if(bIsDestroying)
	{
		LSLOG(Error, TEXT("SOmething wrong"));
		return;
	}
	bIsDestroying = true;

	//LSPlayer->SetWeapon(NewWeapon);
/*
	if (nullptr != LSPlayer && nullptr != WeaponItemClass)
	{
		if (LSPlayer->CanSetWeapon())
		{
			ALSWeaponInstance* NewWeapon = GetWorld()->SpawnActor<ALSWeaponInstance>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			LSPlayer->SetWeapon(NewWeapon);

			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			Effect->OnSystemFinished.AddDynamic(this, &ALSItemBox::OnEffectFinished);
		}
		else
		{
			LSLOG(Warning, TEXT("cannot equip"));
		}
	}
	else
	{
		LSLOG_S(Warning);
	}
*/
}


ULSWeaponDefinition* ALSItemBox::GetWeaponItem()
{
	LSLOG_S(Warning);
	Destroy();
	return WeaponItem;
}

void ALSItemBox::SetWeaponItem(ALSPlayer* LSPlayer)
{
	LSLOG(Warning, TEXT("SetWeaponItem start"));
	// 	LSCHECK(Box->GetWorld() != nullptr);
	LSCHECK(WeaponItem != nullptr);
	WeaponItem = NewObject<ULSWeaponDefinition>(LSPlayer);
	// NewWeapon-> invisible?
	WeaponItem->SetWeaponDefinitionData(EWeaponType::RIFLE, 8);	
}

