// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ULSPlayerAnimInstance::ULSPlayerAnimInstance()
{
}

void ULSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    APawn* Pawn = TryGetPawnOwner();
    if (!::IsValid(Pawn)) return;

    if (!bIsDead)
    {
        CurrentPawnSpeed = Pawn->GetVelocity().Size();
        ACharacter* Character = Cast<ACharacter>(Pawn);
        if (Character)
        {
            IsInAir = Character->GetMovementComponent()->IsFalling();
        }
    }
}

void ULSPlayerAnimInstance::SetAimAnim(bool IsAiming)
{
    bIsAiming = IsAiming;
}

void ULSPlayerAnimInstance::SetReloadAnim(bool IsReloading)
{
    bIsReloading = IsReloading;
}

void ULSPlayerAnimInstance::SetWeaponType(EWeaponType WeaponType)
{
    EquippedWeaponType = WeaponType;
}