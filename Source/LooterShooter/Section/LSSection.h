// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSSection.generated.h"

class UBoxComponent;
class ALSPlayerController;
class ALSSectionStarter;

enum class ESectionState : uint8
{
	ESS_Default,
	ESS_Ready,
	ESS_Battle,
	ESS_Complete
};

/**
 * 게임 내 각 섹션의 부모 클래스
*/

UCLASS()
class LOOTERSHOOTER_API ALSSection : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSSection();

	void SetState(ESectionState NewState);

	UFUNCTION()
	virtual void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnKeyNPCDestroyed(AActor* DestroyedActor);	

	void BindInteractableObject();
	
	FTimerHandle SpawnNPCTimerHandle = {};

	FTimerHandle SpawnItemBoxTimerHandle = {};

	UFUNCTION()
	virtual void BattleStart();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void SectionClear(); 

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool bNoBattle = false;

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	float EnemySpawnTime = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	float ItemBoxSpawnTime = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	int32 MonsterLevel = 1;

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	ALSSectionStarter* SectionStarter;

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	ALSPlayerController* LSPlayerController;

	ESectionState CurrentState = ESectionState::ESS_Default;
};
