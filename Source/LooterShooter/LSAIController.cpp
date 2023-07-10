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
    // RepeatInterval = 3.0f;

    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/LS/AI/LSCharacter.LSCharacter"));
    if (BBObject.Succeeded())
    {
        BBAsset = BBObject.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/LS/AI/BT_LSCharacter.BT_LSCharacter"));
    if (BTObject.Succeeded())
    {
        BTAsset = BTObject.Object;
    }
}

void ALSAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    //GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ALSAIController::OnRepeatTimer, RepeatInterval, true);

/*

    // #include "BehaviorTree/BlackboardComponent.h"
    UBlackboardComponent* BlackboardComp = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardComp))
    {
        
        this->Blackboard = BlackboardComp;
        
        Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());


        if (!RunBehaviorTree(BTAsset))
        {
            LSLOG(Error, TEXT("AIController couldn't run behavior tree!"));
        }
    }
*/
}

/*
void ALSAIController::OnUnPossess()
{
    Super::OnUnPossess();
    GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}



void ALSAIController::OnRepeatTimer()
{
    auto CurrentPawn = GetPawn();
    LSCHECK(nullptr != CurrentPawn);

    // #include "NavigationSystem.h"
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (nullptr == NavSystem) return;

    FVector CenterLocation = FVector(1500.0f, 2000.0f, 250.0f);
    FNavLocation NextLocation;
    if (NavSystem->GetRandomPointInNavigableRadius(CenterLocation, 500.0f, NextLocation))
    {
        //#include "Blueprint/AIBlueprintHelperLibrary.h"
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
        LSLOG(Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
    }
}
*/

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