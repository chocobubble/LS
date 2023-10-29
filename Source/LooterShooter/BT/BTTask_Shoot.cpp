// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "LooterShooter/Character/LSMonster.h"
#include "LooterShooter/Character/LSAIController.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ALSMonster* LSMonster = Cast<ALSMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (LSMonster == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    LSMonster->Attack();

    return EBTNodeResult::Succeeded;
}