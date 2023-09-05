// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "LSAIController.h"
#include "LSPlayer.h"
#include "LSMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
    NodeName = TEXT("Detect");
    Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn) return;
    UWorld* World = ControllingPawn->GetWorld();
    FVector Center = ControllingPawn->GetActorLocation();
    float DetectRadius = 1000.0f;

    if(nullptr == World) return;
    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
    bool bResult = World->OverlapMultiByChannel(
        OverlapResults,
        Center,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeSphere(DetectRadius),
        CollisionQueryParam
    );

    if (bResult)
    {
        for (auto const& OverlapResult : OverlapResults)
        {
            ALSPlayer* LSPlayer = Cast<ALSPlayer>(OverlapResult.GetActor());
            if (LSPlayer && LSPlayer->GetController()->IsPlayerController())
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(ALSAIController::TargetKey, LSPlayer);
                DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
                DrawDebugPoint(World, LSPlayer->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
                DrawDebugLine(World, ControllingPawn->GetActorLocation(), LSPlayer->GetActorLocation(), FColor::Blue, false, 0.2f);

                ALSMonster* LSMonster = Cast<ALSMonster>(ControllingPawn);
                LSMonster->SetAttackTarget(Cast<APawn>(OverlapResult.GetActor()));

                return;
            }
        }
    }


    DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
