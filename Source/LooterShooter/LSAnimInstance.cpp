// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ULSAnimInstance::ULSAnimInstance()
{
    CurrentPawnSpeed = 0.0f;
    IsInAir = false;

	bIsDead = false;
}

void ULSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    APawn* Pawn = TryGetPawnOwner();
    if (!::IsValid(Pawn)) return;

    if (!bIsDead)
    {
        CurrentPawnSpeed = Pawn->GetVelocity().Size();

        // #include "GameFramework/Character.h"
        ACharacter* Character = Cast<ACharacter>(Pawn);
        if (Character)
        {
            // #include "GameFramework/CharacterMovementComponent.h"
            IsInAir = Character->GetMovementComponent()->IsFalling();
        }
        else
        {
            LSLOG_S(Warning);
        }
    }
}
