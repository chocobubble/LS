// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "LooterShooter/Character/LSAIController.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/Character/LSMonster.h"
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
    if (ControllingPawn == nullptr)
	{
		return;
	} 
    UWorld* World = ControllingPawn->GetWorld();
    if (nullptr == World) 
	{
		return;
	}
    TArray<FOverlapResult> OverlapResults;
    FVector Center = ControllingPawn->GetActorLocation();
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
        for (FOverlapResult const& OverlapResult : OverlapResults)
        {
            ALSPlayer* LSPlayer = Cast<ALSPlayer>(OverlapResult.GetActor());
            if (LSPlayer && LSPlayer->GetController() && LSPlayer->GetController()->IsPlayerController())
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(ALSAIController::TargetKey, LSPlayer);
                ALSMonster* LSMonster = Cast<ALSMonster>(ControllingPawn);
				if (LSMonster)
				{
					LSMonster->SetAttackTarget(Cast<APawn>(OverlapResult.GetActor()));
				}
            }
        }
    }
}
