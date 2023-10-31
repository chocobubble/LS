// Fill out your copyright notice in the Description page of Project Settings.

#include "LSFirstSection.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Obstacles/LSDoor.h"

ALSFirstSection::ALSFirstSection()
{
 	PrimaryActorTick.bCanEverTick = false;
}

void ALSFirstSection::BeginPlay()
{
    Super::BeginPlay();

    KilledMonsterCount = 0;
    ClearCondition = 2;
    EnemySpawnTime = 5.0f;
    MonsterSpawnPoint = FVector(1390.f, 3200.f, 0.f);
    DoorSpawnPoint = FVector(1320.f, 5200.f, 190.f);
}

void ALSFirstSection::BattleStart()
{
    Super::BattleStart();

    GetWorld()->GetTimerManager().SetTimer(
        SpawnMonsterTimerHandle,
        FTimerDelegate::CreateUObject(this, &ALSFirstSection::OnMonsterSpawn),
        EnemySpawnTime, 
        true
    );

    LSDoor = GetWorld()->SpawnActor<ALSDoor>(DoorSpawnPoint, FRotator(0.f, 180.f, 0.f));
}

void ALSFirstSection::OnMonsterSpawn()
{
	ALSMonster* Monster = GetWorld()->SpawnActor<ALSMonster>(MonsterSpawnPoint + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	if (Monster)
	{
        int32 MonsterLevel = 1;
        Monster->Init(MonsterLevel);
		Monster->OnDestroyed.AddDynamic(this, &ALSFirstSection::OnMonsterDestroyed);
        MonsterArray.Push(Monster);
        if (MonsterArray.Num() >= 3) // 몬스터 3 생성 시 스폰 중단
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
        if (LiveMonster)
        {
            LiveMonster->SetCharacterState(ECharacterState::DEAD);
        }
    }
    if (LSDoor)
    {
        LSDoor->Destroy();
    }
}
