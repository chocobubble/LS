// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSSection.generated.h"

class UBoxComponent;
class ALSPlayerController;

enum class ESectionState : uint8
{
	READY = 0,
	BATTLE,
	COMPLETE
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

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

	void SetState(ESectionState NewState);

private:
	ESectionState CurrentState = ESectionState::READY;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	bool bNoBattle;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	

protected:
	virtual void BattleStart();
	virtual void SectionClear(); 

	UFUNCTION()
	void OnKeyNPCDestroyed(AActor* DestroyedActor);

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float EnemySpawnTime;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float ItemBoxSpawnTime;

	UPROPERTY(VisibleAnywhere)
	ALSPlayerController* LSPlayerController;

	FTimerHandle SpawnNPCTimerHandle = {};
	FTimerHandle SpawnItemBoxTimerHandle = {};
};
