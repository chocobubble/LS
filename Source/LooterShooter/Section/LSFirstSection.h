// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSSection.h"
#include "LSFirstSection.generated.h"

class ALSMonster;
class ALSDoor;

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSFirstSection : public ALSSection
{
	GENERATED_BODY()
public:
	ALSFirstSection();
	
	UFUNCTION()
	void OnMonsterSpawn();

	UFUNCTION()
	void OnMonsterDestroyed(AActor* DestroyedActor);

	FTimerHandle SpawnMonsterTimerHandle = {};

protected:
	virtual void BeginPlay() override;

	virtual void BattleStart() override;

	virtual void SectionClear() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Monster")
	FVector MonsterSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Monster")
	int32 KilledMonsterCount;

	UPROPERTY(VisibleAnywhere, Category = "Monster")
	int32 ClearCondition;

	UPROPERTY(VisibleAnywhere, Category = "Monster")
	TArray<ALSMonster*> MonsterArray;

	UPROPERTY(VisibleAnywhere, Category = "Monster")
	AActor* SpawnPointActor;

	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	ALSDoor* LSDoor;

	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	FVector DoorSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	AActor* NextDoor;
};
