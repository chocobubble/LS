// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSAutoLootItem.h"
#include "AmmoAutoLootItem.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API AAmmoAutoLootItem : public ALSAutoLootItem
{
	GENERATED_BODY()

public:
	AAmmoAutoLootItem();

protected:
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
