// Fill out your copyright notice in the Description page of Project Settings.


#include "LooterShooter/Character/LSAIController.h"
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
}

void ALSAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void ALSAIController::RunAI()
{
    LSLOG(Warning, TEXT("Run AI"));

    UBlackboardComponent* BlackboardComp = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardComp))
    {
        this->Blackboard = BlackboardComp;
        Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
        RunBehaviorTree(BTAsset);
    }
}

void ALSAIController::StopAI()
{
    UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BehaviorTreeComponent)
    {
        BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
    }
}