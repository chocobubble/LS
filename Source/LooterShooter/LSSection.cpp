// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSection.h"
#include "Components/BoxComponent.h"
#include "LSMonster.h"
#include "LSItemBox.h"
#include "LSGameMode.h"
#include "LSPlayerController.h"
#include "LSPlayer.h"

// Sets default values
ALSSection::ALSSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/LS/Meshes/SM_floor.SM_floor");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ITEM(*AssetPath);
	if (ITEM.Succeeded())
	{
		Mesh->SetStaticMesh(ITEM.Object);
	}
	else 
	{
		LSLOG_S(Warning);
	}

	//#include "Components/BoxComponent.h" 
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetBoxExtent(FVector(40.0f, 40.0f, 100.0f));
	//Trigger->SetRelativeLocation()
	Trigger->SetCollisionProfileName(TEXT("LSTrigger"));

	bNoBattle = false;

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALSSection::OnTriggerBeginOverlap);

	EnemySpawnTime = 5.0f;
	ItemBoxSpawnTime = 5.0f;
}

// Called when the game starts or when spawned
void ALSSection::BeginPlay()
{
	Super::BeginPlay();
	
	//SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void ALSSection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
		case ESectionState::READY :
		{
			Trigger->SetCollisionProfileName(TEXT("LSTrigger"));
			break;
		}
		case ESectionState::BATTLE :
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			BattleStart();
/*
			GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle,
				FTimerDelegate::CreateUObject(this, &ALSSection::OnNPCSpawn),
				EnemySpawnTime, true);

			GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle,
				FTimerDelegate::CreateLambda([this]() -> void {
					FVector2D RandXY = FMath::RandPointInCircle(600.0f);
					GetWorld()->SpawnActor<ALSItemBox>(GetActorLocation() +
						FVector(RandXY, 30.0f), FRotator::ZeroRotator);		
				}), ItemBoxSpawnTime, false);

*/
			break;
		}
		case ESectionState::COMPLETE :
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			SectionClear();
			break;
		}
	}

	CurrentState = NewState;
}

void ALSSection::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void ALSSection::OnTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (CurrentState == ESectionState::READY)
	{
		SetState(ESectionState::BATTLE);
		LSLOG(Warning, TEXT("Set Battle State"));
	}
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	LSPlayerController = Cast<ALSPlayerController>(LSPlayer->GetController());
}
/*
void ALSSection::OnNPCSpawn()
{
/*
	GetWorld()->SpawnActor<ALSMonster>(GetActorLocation() + FVector::UpVector * 80.0f,
										 FRotator::ZeroRotator);
*/
/*
	GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
	auto KeyNPC = GetWorld()->SpawnActor<ALSMonster>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	if (nullptr != KeyNPC)
	{
		KeyNPC->OnDestroyed.AddDynamic(this, &ALSSection::OnKeyNPCDestroyed);
	}

}
*/

void ALSSection::OnKeyNPCDestroyed(AActor* DestroyedActor)
{
	/*
	auto LSMonster = Cast<ALSMonster>(DestroyedActor);
	LSCHECK(nullptr != LSMonster);

	auto LSPlayerController = Cast<ALSPlayerController>(LSMonster->LastHitBy);
	LSCHECK(nullptr != LSPlayerController);
*/
	auto LSGameMode = Cast<ALSGameMode>(GetWorld()->GetAuthGameMode());
	LSCHECK(nullptr != LSGameMode);
	//LSGameMode->AddScore(LSPlayerController);

	//SetState(ESectionState::COMPLETE);
}
// Called every frame
/*
void ALSSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

void ALSSection::BattleStart() {}
void ALSSection::SectionClear() {}


