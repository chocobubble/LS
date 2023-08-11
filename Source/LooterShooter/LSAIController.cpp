// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ALSAIController::HomePosKey(TEXT("HomePos"));
const FName ALSAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ALSAIController::TargetKey(TEXT("Target"));

ALSAIController::ALSAIController()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/LS/AI/LSCharacter.LSCharacter"));
    if (BBObject.Succeeded())
    {
        BBAsset = BBObject.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/LS/AI/BT_LSRifleman.BT_LSRifleman"));
    if (BTObject.Succeeded())
    {
        BTAsset = BTObject.Object;
    }
    else
    {
        LSLOG(Error, TEXT("BT Error"));
    }
}

void ALSAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void ALSAIController::RunAI()
{
    UBlackboardComponent* BlackboardComp = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardComp))
    {
        this->Blackboard = BlackboardComp;
        Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
        if (!RunBehaviorTree(BTAsset))
        {
            LSLOG(Error, TEXT("AIController couldn't run behavior tree!"));
        }
    }
}

void ALSAIController::StopAI()
{
    auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (nullptr != BehaviorTreeComponent )
    {
        BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
    }
}