// Fill out your copyright notice in the Description page of Project Settings.


#include "LSBossSection.h"
#include "LSMonster.h"
#include "LSDoor.h"
#include "LSPlayerController.h"

void ALSBossSection::BeginPlay()
{
    Super::BeginPlay();
    DoorSpawnPoint = FVector(1320.f, 5230.f, 190.f);
    MonsterSpawnPoint = FVector(1390.f, 7260.f, 0.f);
    EnemySpawnTime = 1.0f;
}

void ALSBossSection::BattleStart()
{
    Super::BattleStart();

    GetWorld()->GetTimerManager().SetTimer(SpawnBossTimerHandle,
            FTimerDelegate::CreateUObject(this, &ALSBossSection::OnMonsterSpawn),
            EnemySpawnTime, false);

    LSDoor = GetWorld()->SpawnActor<ALSDoor>(DoorSpawnPoint, FRotator(0.f, 180.f, 0.f));
	LSCHECK(LSDoor);
}

void ALSBossSection::OnMonsterSpawn()
{
	//
	auto Monster = GetWorld()->SpawnActor<ALSMonster>(MonsterSpawnPoint + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
    LSCHECK(Monster);
    Monster->SetMonsterLevel(10);
    Monster->OnDestroyed.AddDynamic(this, &ALSBossSection::OnMonsterDestroyed);
}

void ALSBossSection::OnMonsterDestroyed(AActor* DestroyedActor) 
{
    SetState(ESectionState::COMPLETE);
}

void ALSBossSection::SectionClear() 
{
    Super::SectionClear();
    GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
    DisableInput(LSPlayerController);
    LSPlayerController->ShowResultUI();

    //LSCHECK(LSDoor != nullptr);
    //LSDoor->Destroy();
}