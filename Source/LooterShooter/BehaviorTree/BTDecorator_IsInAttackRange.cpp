// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "LSAIController.h"
#include "LSPlayer.h"
#include "LSMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
    NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn == nullptr)
    {
        return false;
    }

    ALSPlayer* Target = Cast<ALSPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ALSAIController::TargetKey));
    if (Target == nullptr)
    {
        return false;
    }

    bResult = (Target->GetDistanceTo(ControllingPawn) <= 2500.0f);
    return bResult;
}
