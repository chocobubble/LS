// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "LooterShooter/Character/LSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
    NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if (NavSystem == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ALSAIController::HomePosKey);
    FNavLocation NextPatrol;
    FVector TestVector = FVector(1390.f, 4300.f, 0.f);
    // 맵 넘어가면 제대로 작동이 안함..
    if (NavSystem->GetRandomPointInNavigableRadius(Origin, 1000.0f, NextPatrol))
    //if (NavSystem->GetRandomPointInNavigableRadius(TestVector, 1000.0f, NextPatrol))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(ALSAIController::PatrolPosKey, NextPatrol.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;

}
