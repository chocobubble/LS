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
    DoorSpawnPoint = FVector(1320.0f, 5200.0f, 190.0f);

    MonsterSpawnPoints.Add(FVector(1390.0f, 3200.0f, 0.0f));
    MonsterSpawnPoints.Add(FVector(1590.0f, 3400.0f, 0.0f));
    MonsterSpawnPoints.Add(FVector(1590.0f, 3000.0f, 0.0f));
    
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

    LSDoor = GetWorld()->SpawnActor<ALSDoor>(DoorSpawnPoint, FRotator(0.0f, 180.0f, 0.0f));
    
	ALSPlayer* LSPlayer = Cast<ALSPlayer>(OtherActor);
	if (LSPlayer)
	{
		LSPlayerController = Cast<ALSPlayerController>(LSPlayer->GetController());
		MonsterLevel = LSPlayer->GetPlayerLevel();
	}
}

void ALSFirstSection::OnMonsterSpawn()
{
    if (MonsterSpawnPoints.Num() <= 0)
    {
        return;
    }
    for (FVector& MonsterSpawnPoint : MonsterSpawnPoints)
    {
        ALSMonster* Monster = GetWorld()->SpawnActor<ALSMonster>(MonsterSpawnPoint + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
    	if (Monster)
    	{
         `  Monster->Init(MonsterLevel);
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
