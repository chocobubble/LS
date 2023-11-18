// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSAutoLootItem.h"
#include "HPAutoLootItem.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API AHPAutoLootItem : public ALSAutoLootItem
{
	GENERATED_BODY()
	
public:
	AHPAutoLootItem();

protected:
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
