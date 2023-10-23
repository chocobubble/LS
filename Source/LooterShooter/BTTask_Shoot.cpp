// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "LSMonster.h"
#include "LSAIController.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ALSMonster* LSMonster = Cast<ALSMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (nullptr == LSMonster)
    {
        return EBTNodeResult::Failed;
    }

    // LSMonster->Attack();
    LSLOG(Warning, TEXT("Monster Shoot"));
    LSMonster->Attack();

    return EBTNodeResult::Succeeded;
    
}