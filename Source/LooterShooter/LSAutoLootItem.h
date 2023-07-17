// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "LSLootItem.h"
#include "LSAutoLootItem.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSAutoLootItem : public ALSLootItem
{
	GENERATED_BODY()

public:
	ALSAutoLootItem();

protected:
	//virtual void BeginPlay() override;
	//virtual void PostInitializeComponents() override;
	
public:
	//UFUNCTION()
	virtual void OnCharacterOverlap(
		UPrimitiveComponent * OverlappedComp, 
		AActor * OtherActor, 
		UPrimitiveComponent * OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult) override;
};
