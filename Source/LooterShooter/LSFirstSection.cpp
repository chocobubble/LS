// Fill out your copyright notice in the Description page of Project Settings.

#include "LSFirstSection.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "LSMonster.h"
ALSFirstSection::ALSFirstSection()
{
 	PrimaryActorTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DOOR(TEXT("/Game/LS/Meshes/SM_Door.SM_Door"));
	if (!SM_DOOR.Succeeded())
	{
		LSLOG_S(Error);
	}
/*
    NextDoor = GetWorld()->SpawnActor<AActor>(FVector(0.f,0.f,0.f), FRotator::ZeroRotator);//(FVector(1330.f, 5200.f, 190.f), FRotator(0.f, 180.f, 0.f));
    UStaticMeshComponent* DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
    NextDoor->SetRootComponent(DoorMesh);
    LSCHECK(SM_DOOR.Object);
    DoorMesh->SetStaticMesh(SM_DOOR.Object);
*/
}
void ALSFirstSection::BeginPlay()
{
    Super::BeginPlay();
    KilledMonsterCount = 0;
    ClearCondition = 2;
    EnemySpawnTime = 10.0f;

    /*
    UWorld* CurrentWorld = GetWorld();
    for(const auto& Entry : FActorRange(CurrentWorld))
    {
        LSLOG(Warning, TEXT("%s"), *Entry->GetName());
        if(*Entry->GetName() == FName("MonsterSpawnPoint"))
        {
            SpawnPointActor = Cast<AActor>(Entry);
        }
        if(SpawnPointActor != nullptr) 
        {
            LSLOG(Warning, TEXT("Get mOnster spawn point "));
        }
    }
    */
    SpawnPoint = FVector(1390.f, 4300.f, 0.f);
}

void ALSFirstSection::BattleStart()
{
    Super::BattleStart();

    GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle,
            FTimerDelegate::CreateUObject(this, &ALSFirstSection::OnMonsterSpawn),
            EnemySpawnTime, true);
}

void ALSFirstSection::OnMonsterSpawn()
{
	//
	auto Monster = GetWorld()->SpawnActor<ALSMonster>(SpawnPoint + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	if (nullptr != Monster)
	{
        MonsterArray.Push(Monster);
		Monster->OnDestroyed.AddDynamic(this, &ALSFirstSection::OnMonsterDestroyed);
	}
}

void ALSFirstSection::OnMonsterDestroyed(AActor* DestroyedActor) 
{
    ++KilledMonsterCount;
    if(KilledMonsterCount >= ClearCondition)
    {
        SetState(ESectionState::COMPLETE);
    }
}

void ALSFirstSection::SectionClear() 
{
    Super::SectionClear();

    GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
    for(ALSMonster* LiveMonster : MonsterArray)
    {
        if(LiveMonster != nullptr)
        {
            LiveMonster->SetCharacterState(ECharacterState::DEAD);
        }
    }
    LSCHECK(NextDoor != nullptr);
    NextDoor->Destroy();
}
