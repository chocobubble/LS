// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ALSAIController::ALSAIController()
{
    RepeatInterval = 3.0f;
/*
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/Book/AI/BB_LSCharacter.BB_LSCharacter'"));
    if (BBObject.Succeeded())
    {
        BBAsset = BBObject.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Book/AI/BT_LSCharacter.BT_LSCharacter'"));
    if (BTObject.Succeeded())
    {
        BTAsset = BTObject.Object;
    }
*/
}

void ALSAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ALSAIController::OnRepeatTimer, RepeatInterval, true);

/*
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

    FNavLocation NextLocation;
    if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
    {
        //#include "Blueprint/AIBlueprintHelperLibrary.h"
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
        LSLOG(Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
    }
}
