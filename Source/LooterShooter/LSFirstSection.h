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
	int32 KilledMonsterCount;

	UPROPERTY(VisibleAnywhere)
	int32 ClearCondition;

	UPROPERTY(VisibleAnywhere)
	TArray<ALSMonster*> MonsterArray;

	UPROPERTY(VisibleAnywhere)
	ALSDoor* LSDoor;
	
	
	FTimerHandle SpawnMonsterTimerHandle = {};


public:
	UPROPERTY(VisibleAnywhere)
	AActor* SpawnPointActor;

	UPROPERTY(VisibleAnywhere)
	AActor* NextDoor;


};