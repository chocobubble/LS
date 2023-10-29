// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "LSAIController.h"
#include "LSCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
    bNotifyTick = true;
    IsAttacking = false;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (!IsAttacking)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }   
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ALSCharacter* LSCharacter = Cast<ALSCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (LSCharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    LSCharacter->Attack();
    IsAttacking = true;
    LSCharacter->OnAttackEnd.AddLambda([]() -> void {
        IsAttacking = false;
    });

    return EBTNodeResult::InProgress;
}

