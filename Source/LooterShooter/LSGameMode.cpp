// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameMode.h"
#include "LSCharacter.h"
#include "LSPlayerController.h"

ALSGameMode::ALSGameMode()
{
    DefaultPawnClass = ALSCharacter::StaticClass();
    //PlayerControllerClass = ALSPlayerController::StaticClass();
} 

void ALSGameMode::PostLogin(APlayerController * NewPlayer)
{
    LSLOG(Warning, TEXT("PostLogin Begin"));
    Super::PostLogin(NewPlayer);
    LSLOG(Warning, TEXT("PostLogin End"));
}

