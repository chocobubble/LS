// Fill out your copyright notice in the Description page of Project Settings.

#include "LSFirstSection.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Obstacles/LSDoor.h"
ALSFirstSection::ALSFirstSection()
{
 	PrimaryActorTick.bCanEverTick = false;
/*
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DOOR(TEXT("/Game/LS/Meshes/SM_Door.SM_Door"));
	if (!SM_DOOR.Succeeded())
	{
		LSLOG_S(Error);
	}

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
    EnemySpawnTime = 5.0f;

    /*
    
    */
    MonsterSpawnPoint = FVector(1390.f, 3200.f, 0.f);
    DoorSpawnPoint = FVector(1320.f, 5200.f, 190.f);
}

void ALSFirstSection::BattleStart()
{
    Super::BattleStart();

    GetWorld()->GetTimerManager().SetTimer(SpawnMonsterTimerHandle,
            FTimerDelegate::CreateUObject(this, &ALSFirstSection::OnMonsterSpawn),
            EnemySpawnTime, true);

    LSDoor = GetWorld()->SpawnActor<ALSDoor>(DoorSpawnPoint, FRotator(0.f, 180.f, 0.f));
	LSCHECK(LSDoor);
/*
     UWorld* CurrentWorld = GetWorld();
    for (const auto& Entry : FActorRange(CurrentWorld))
    {
        LSLOG(Warning, TEXT("%s"), *Entry->GetName());
        if (*Entry->GetName() == FName("MonsterSpawnPoint"))
        {
            SpawnPointActor = Cast<AActor>(Entry);
        }
        if (SpawnPointActor != nullptr) 
        {
            LSLOG(Warning, TEXT("Get mOnster spawn point "));
        }
    }
*/
}

void ALSFirstSection::OnMonsterSpawn()
{
	//
	auto Monster = GetWorld()->SpawnActor<ALSMonster>(MonsterSpawnPoint + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
    LSCHECK(Monster != nullptr);
    //Monster->SetMonsterLevel(1);
    Monster->Init(1);
	if (nullptr != Monster)
	{
		Monster->OnDestroyed.AddDynamic(this, &ALSFirstSection::OnMonsterDestroyed);
        MonsterArray.Push(Monster);
        if (MonsterArray.Num() >= 3) // 몬스터 5 생성 시 스폰 중단
        {
            GetWorld()->GetTimerManager().ClearTimer(SpawnMonsterTimerHandle);
        }
	}
}

void ALSFirstSection::OnMonsterDestroyed(AActor* DestroyedActor) 
{
    ++KilledMonsterCount;
    if (KilledMonsterCount >= ClearCondition)
    {
        SetState(ESectionState::COMPLETE);
    }
}

void ALSFirstSection::SectionClear() 
{
    Super::SectionClear();

    GetWorld()->GetTimerManager().ClearTimer(SpawnMonsterTimerHandle);
    for (ALSMonster* LiveMonster : MonsterArray)
    {
        if (LiveMonster != nullptr)
        {
            LiveMonster->SetCharacterState(ECharacterState::DEAD);
        }
    }
    LSCHECK(LSDoor != nullptr);
    LSDoor->Destroy();
}
