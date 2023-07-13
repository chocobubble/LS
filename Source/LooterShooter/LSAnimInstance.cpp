// Fill out your copyright notice in the Description page of Project Settings.


#include "LSAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ULSAnimInstance::ULSAnimInstance()
{
    CurrentPawnSpeed = 0.0f;
    IsInAir = false;

	bIsDead = false;

    bIsAiming = false;

    static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/LS/Animations/AM_MM_Rifle_Melee.AM_MM_Rifle_Melee'"));
    //TEXT("/Script/Engine.AnimMontage'/Game/LS/Animations/Montage/UE4_Mannequin_Skeleton_Montage.UE4_Mannequin_Skeleton_Montage'"));
    //(TEXT("/Game/LS/Animations/AM_MM_Pistol_Melee.AM_MM_Pistol_Melee"));
    if (ATTACK_MONTAGE.Succeeded())
    {
        AttackMontage = ATTACK_MONTAGE.Object;
    }
    else
    {
        LSLOG(Warning, TEXT("No AttackMontage"));
    }
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

void ULSAnimInstance::PlayAttackMontage()
{
    Montage_Play(AttackMontage, 1.0f);
    LSLOG(Warning, TEXT("Montage playing"));
}

void ULSAnimInstance::SetAimAnim(bool IsAiming)
{
    bIsAiming = IsAiming;
}