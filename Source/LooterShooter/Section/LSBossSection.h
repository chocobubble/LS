// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSSection.h"
#include "LSBossSection.generated.h"

class ALSDoor;
class ALSMonster;

/**
 * 보스 방 섹션 
 */
UCLASS()
class LOOTERSHOOTER_API ALSBossSection : public ALSSection
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnMonsterSpawn();

	UFUNCTION()
	void OnMonsterDestroyed(AActor* DestroyedActor);

	FTimerHandle SpawnBossTimerHandle = {};

	FTimerHandle ClearTimerHandle = {};

protected:
	virtual void BeginPlay() override;

	virtual void BattleStart() override;

	virtual void SectionClear() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Monster")
	FVector MonsterSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	FVector DoorSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	ALSDoor* LSDoor;
};
