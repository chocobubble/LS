// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSLootItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

enum class LootItemType 
{
	Gold,
	HP,
	MP,
	Ammo1,
	Ammo2,
	Ammo3,
	Equipment
};

UCLASS()
class LOOTERSHOOTER_API ALSLootItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSLootItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	UFUNCTION()
	virtual void OnCharacterOverlap(
		UPrimitiveComponent * OverlappedComp, 
		AActor * OtherActor, 
		UPrimitiveComponent * OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult);

	// Called every frame
	// virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere, Category = Loot)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMeshComponent* LootItem;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;
};
