// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LooterShooter/Types/LootItemType.h"
#include "LSLootItem.generated.h"

class USoundCue;
class USphereComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class LOOTERSHOOTER_API ALSLootItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSLootItem();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Loot")
	USphereComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	UParticleSystemComponent* Effect;

	UPROPERTY(VisibleAnywhere, Category = "Loot")
	ELootItemType LootItemType;

	UPROPERTY(VisibleAnywhere, category = "Sound")
	USoundCue* LootSound;

	UPROPERTY(EditAnywhere, category = "Collision", meta = (AllowPrivateAccess = "true"))
	float TriggerRange = 100.0f;

public:
	UStaticMeshComponent* GetItemMesh()
	{
		return ItemMesh;
	}
};
