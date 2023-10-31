// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LSLootItem.h"
#include "LSAutoLootItem.generated.h"

/**
 * 캐릭터와 겹치면 자동으로 룻되는 아이템 클래스
 */
UCLASS()
class LOOTERSHOOTER_API ALSAutoLootItem : public ALSLootItem
{
	GENERATED_BODY()

public:
	ALSAutoLootItem();

	// auto loot item의 type 및 amount 설정
	void SetAutoLootItem(ELootItemType LootItemType, int32 Amount);

protected:
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	/** 드롭되는 아이템의 양 */
	UPROPERTY(EditAnywhere, Category = "Loot", meta = (AllowPrivateAccess = "true"))
	int32 LootingAmount = 0;
};
