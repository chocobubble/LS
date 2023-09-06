// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSSection.h"
#include "LSBossSection.generated.h"

class ALSDoor;
class ALSMonster;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSBossSection : public ALSSection
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void BattleStart() override;
	virtual void SectionClear() override;

private:
	UFUNCTION()
	void OnMonsterSpawn();

	UFUNCTION()
	void OnMonsterDestroyed(AActor* DestroyedActor);

	UPROPERTY(VisibleAnywhere)
	FVector MonsterSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	FVector DoorSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	ALSDoor* LSDoor;

	FTimerHandle SpawnBossTimerHandle = {};
	
};
