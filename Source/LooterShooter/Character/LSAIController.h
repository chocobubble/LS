// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "AIController.h"
#include "LSAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;
/**
 * Monster의 베이스 컨트롤러
 */
UCLASS()
class LOOTERSHOOTER_API ALSAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALSAIController();

	/** 몬스터 생성 후 AI 시작 */
	void RunAI();

	/** 몬스터 사망 시 AI 중단 */
	void StopAI();

	static const FName HomePosKey;
	
	static const FName PatrolPosKey;

	static const FName TargetKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBlackboardData* BBAsset;
};
