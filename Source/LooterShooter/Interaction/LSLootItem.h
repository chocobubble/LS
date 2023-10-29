// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSLootItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UENUM(BlueprintType)
enum class ELootItemType 
{
	DEFAULT,
	GOLD,
	HP,
	MP,
	RIFLEAMMO,
	SHOTGUNAMMO,
	PISTOLAMMO,
	EQUIPMENT
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


public:
	UPROPERTY(VisibleAnywhere, Category = Loot)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;

	UPROPERTY(VisibleAnywhere, Category = Loot)
	ELootItemType LootItemType;
};
