// Fill out your copyright notice in the Description page of Project Settings.


#include "LSUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void ALSUIPlayerController::BeginPlay()
{
    Super::BeginPlay();

    LSCHECK(nullptr != UIWidgetClass);

    UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
    LSCHECK(nullptr != UIWidgetInstance);

    UIWidgetInstance->AddToViewport();

    FInputModeUIOnly Mode;
    Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
    SetInputMode(Mode);
    bShowMouseCursor = true;
}
