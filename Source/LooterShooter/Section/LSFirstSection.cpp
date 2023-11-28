// Fill out your copyright notice in the Description page of Project Settings.

#include "LSFirstSection.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Obstacles/LSDoor.h"
#include "LSSpawnPoint.h"

ALSFirstSection::ALSFirstSection()
{
 	PrimaryActorTick.bCanEverTick = false;
    FirstSpawnPointPos = FVector(-5760.0f, 2720.0f, 7521.0f);
    SecondSpawnPointPos = FVector(-5490.0f, 3190.0f, 7353.0f);
    ThirdSpawnPointPos = FVector(-5870.0f, 3550.0f, 7270.0f);
}

void ALSFirstSection::BeginPlay()
{
    Super::BeginPlay();

    KilledMonsterCount = 0;
    ClearCondition = 3;
    EnemySpawnTime = 5.0f;
    //DoorSpawnPoint = FVector(1320.0f, 5200.0f, 190.0f);

    //MonsterSpawnPoint = FVector(1390.0f, 3200.0f, 0.0f);

    FirstSpawnPoint = GetWorld()->SpawnActor<ALSSpawnPoint>(FirstSpawnPointPos, FRotator::ZeroRotator);
    SecondSpawnPoint = GetWorld()->SpawnActor<ALSSpawnPoint>(SecondSpawnPointPos, FRotator::ZeroRotator);
    ThirdSpawnPoint = GetWorld()->SpawnActor<ALSSpawnPoint>(ThirdSpawnPointPos, FRotator::ZeroRotator);
    MonsterSpawnPoints.Add(FirstSpawnPoint);
    MonsterSpawnPoints.Add(SecondSpawnPoint);
    MonsterSpawnPoints.Add(ThirdSpawnPoint);
    
}

void ALSFirstSection::BattleStart()
{
    Super::BattleStart();

    OnMonsterSpawn();
    //LSDoor = GetWorld()->SpawnActor<ALSDoor>(DoorSpawnPoint, FRotator(0.0f, 180.0f, 0.0f));
}

void ALSFirstSection::OnMonsterSpawn()
{
    if (MonsterSpawnPoints.Num() <= 0)
    {
        return;
    }
    for (ALSSpawnPoint* MonsterSpawnPoint : MonsterSpawnPoints)
    {
        ALSMonster* Monster = GetWorld()->SpawnActor<ALSMonster>(MonsterSpawnPoint->GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
    	if (Monster)
    	{
            Monster->Init(MonsterLevel);
            //Monster->SetMonsterLevel(MonsterLevel);
    		Monster->OnDestroyed.AddDynamic(this, &ALSFirstSection::OnMonsterDestroyed);
            MonsterArray.Push(Monster);
            if (MonsterArray.Num() >= 3) // 몬스터 3 생성 시 스폰 중단
            {
                GetWorld()->GetTimerManager().ClearTimer(SpawnMonsterTimerHandle);
            }
	    }
    }
	
}

void ALSFirstSection::OnMonsterDestroyed(AActor* DestroyedActor) 
{
    ++KilledMonsterCount;
    if (KilledMonsterCount >= ClearCondition)
    {
        SetState(ESectionState::ESS_Complete);
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
            LiveMonster->SetCharacterState(ECharacterState::ECS_Dead);
        }
    }
    if (LSDoor)
    {
        LSDoor->Destroy();
    }
}
