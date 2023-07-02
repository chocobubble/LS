// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerController.h"

void ALSPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    LSLOG_S(Warning);
}

void ALSPlayerController::OnPossess(APawn* aPawn)
{
    LSLOG_S(Warning);
    Super::OnPossess(aPawn);
}