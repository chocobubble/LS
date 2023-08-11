// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "AIController.h"
#include "LSAIController.generated.h"

/**
 * Monster의 베이스 컨트롤러
 */
UCLASS()
class LOOTERSHOOTER_API ALSAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALSAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	void RunAI();
	void StopAI();

private:
	UPROPERTY(VisibleAnywhere)
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
