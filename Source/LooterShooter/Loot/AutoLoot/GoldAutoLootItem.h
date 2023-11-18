// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSAutoLootItem.h"
#include "GoldAutoLootItem.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API AGoldAutoLootItem : public ALSAutoLootItem
{
	GENERATED_BODY()

public:
	AGoldAutoLootItem();

protected:
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
