// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/Loot/LSLootItem.h"
#include "LSAutoLootItem.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

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

protected:
	/** 드롭되는 아이템의 양 */
	UPROPERTY(EditAnywhere, Category = "Loot", meta = (AllowPrivateAccess = "true"))
	int32 DropAmount = 0;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraComponent* EffectComponent;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* DestroyEffect;
};
