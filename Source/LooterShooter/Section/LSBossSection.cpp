// Fill out your copyright notice in the Description page of Project Settings.

#include "LSBossSection.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Obstacles/LSDoor.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "Kismet/GameplayStatics.h"

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

    GetWorld()->GetTimerManager().SetTimer(
        SpawnBossTimerHandle,
        FTimerDelegate::CreateUObject(this, &ALSBossSection::OnMonsterSpawn),
        EnemySpawnTime,
        false
    );

    LSDoor = GetWorld()->SpawnActor<ALSDoor>(DoorSpawnPoint, FRotator(0.f, 180.f, 0.f));
}

void ALSBossSection::OnMonsterSpawn()
{
	ALSMonster* Monster = GetWorld()->SpawnActor<ALSMonster>(MonsterSpawnPoint + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
    if (Monster)
    {
        Monster->SetMonsterLevel(10);
        Monster->OnDestroyed.AddDynamic(this, &ALSBossSection::OnMonsterDestroyed);
    }
}

void ALSBossSection::OnMonsterDestroyed(AActor* DestroyedActor) 
{
    GetWorld()->GetTimerManager().ClearTimer(ClearTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(
        ClearTimerHandle,
        FTimerDelegate::CreateLambda([this]() -> void {
            SetState(ESectionState::COMPLETE);}),
        EnemySpawnTime,
        false
    );
}

void ALSBossSection::SectionClear() 
{
    Super::SectionClear();

    GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
/*
    if (LSPlayerController)
    {
        DisableInput(LSPlayerController);
        LSPlayerController->ShowResultUI();
    }
*/
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("LS_Level_1"));
}