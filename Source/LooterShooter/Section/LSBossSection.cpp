// Fill out your copyright notice in the Description page of Project Settings.

#include "LSBossSection.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Obstacles/LSDoor.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ALSBossSection::BeginPlay()
{
    Super::BeginPlay();

    DoorSpawnPoint = FVector(1320.0f, 5230.0f, 190.0f);
    MonsterSpawnPoint = FVector(-332.0f, 3618.0f, 7787.0f);
    EnemySpawnTime = 1.0f;
    MonsterLevel = 10; // 보스 몬스터 레벨 
}

void ALSBossSection::BattleStart()
{
    Super::BattleStart();

    GetWorld()->GetTimerManager().SetTimer(
        SpawnBossTimerHandle,
        FTimerDelegate::CreateUObject(this, &ALSBossSection::OnMonsterSpawn),
        EnemySpawnTime,
        false
    );

    //LSDoor = GetWorld()->SpawnActor<ALSDoor>(DoorSpawnPoint, FRotator(0.0f, 180.0f, 0.0f));
}

void ALSBossSection::OnMonsterSpawn()
{
	ALSMonster* Monster = GetWorld()->SpawnActor<ALSMonster>(MonsterSpawnPoint + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
    if (Monster)
    {
        Monster->Init(10);//MonsterLevel);
        //Monster->SetMonsterLevel(MonsterLevel);
        Monster->OnDestroyed.AddDynamic(this, &ALSBossSection::OnMonsterDestroyed);
    }
}

void ALSBossSection::OnMonsterDestroyed(AActor* DestroyedActor) 
{
    GetWorld()->GetTimerManager().ClearTimer(ClearTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(
        ClearTimerHandle,
        FTimerDelegate::CreateLambda([this]() -> void {
            SetState(ESectionState::ESS_Complete); }),
        EnemySpawnTime,
        false
    );
}

void ALSBossSection::SectionClear() 
{
    Super::SectionClear();

    GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("LS_Level_1"));
}