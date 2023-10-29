// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

/**
 * AI가 일정 주기로 플레이어를 탐지하는 클래스
 */
UCLASS()
class LOOTERSHOOTER_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)	override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BT", meta = (AllowPrivateAccess = "true"))
    float DetectRadius = 2000.0f;
};
