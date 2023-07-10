// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerController.h"
#include "LSHUDWidget.h"
#include "LSPlayerState.h"
#include "LSCharacter.h"


ALSPlayerController::ALSPlayerController()
{
    static ConstructorHelpers::FClassFinder<ULSHUDWidget> UI_HUD_C(TEXT("/Game/LS/UI/UI_HUD.UI_HUD_C"));
    if (UI_HUD_C.Succeeded())
    {
        HUDWidgetClass = UI_HUD_C.Class;
    }
}


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

void ALSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    //    ChangeInputMode(true);

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);


    HUDWidget  = CreateWidget<ULSHUDWidget>(this, HUDWidgetClass);
    LSCHECK(nullptr != HUDWidget);
    HUDWidget->AddToViewport();

/*
    HUDWidget->AddToViewport(1);
*/
    LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    // ALSPlayerState*  LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    //auto LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    LSCHECK(nullptr != LSPlayerState);
    HUDWidget->BindPlayerState(LSPlayerState);
    LSPlayerState->OnPlayerStateChanged.Broadcast();  

/*
    ResultWidget = CreateWidget<ULSGameplayResultWidget>(this, ResultWidgetClass);
    LSCHECK(nullptr != ResultWidget);
*/
}

ULSHUDWidget* ALSPlayerController::GetHUDWidget() const
{
    return HUDWidget;
}

void ALSPlayerController::NPCKill(ALSCharacter* KilledNPC) const
{
    LSPlayerState->AddExp(KilledNPC->GetExp());
}

void ALSPlayerController::AddGameScore() const
{
    LSPlayerState->AddGameScore();
}