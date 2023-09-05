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

    //auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    //ALSPlayer* ControllingPawn = Cast<ALSPlayer>(OwnerComp.GetAIOwner()->GetPawn());

    //ALSMonster* ControllingPawn = Cast<ALSMonster>(OwnerComp.GetAIOwner()->GetPawn());
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if(nullptr == ControllingPawn)
    {
        return false;
    }

    ALSPlayer* Target = Cast<ALSPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ALSAIController::TargetKey));
    if (nullptr == Target)
    {
        return false;
    }

    bResult = (Target->GetDistanceTo(ControllingPawn) <= 1000.0f);
    //bResult = (Target->GetDistanceTo(ControllingPawn) <= ControllingPawn->GetFinalAttackRange());
    return bResult;
}
