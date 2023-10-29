// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameplayResultWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "LSGameState.h"
#include "LSPlayerController.h"
#include "LSPlayer.h"
#include "LSEnhanceWidget.h"
#include "LSInventoryComponent.h"
#include "LSResourceManageComponent.h"

void ULSGameplayResultWidget::NativeConstruct()
{
    Super::NativeConstruct();

    EnhanceButton = Cast<UButton>(GetWidgetFromName(TEXT("btnEnhance")));
    if (nullptr != EnhanceButton)
    {
        EnhanceButton->OnClicked.AddDynamic(this, &ULSGameplayResultWidget::OnEnhanceClicked);
    }

}


void ULSGameplayResultWidget::BindGameState(class ALSGameState* GameState)
{
    //LSCHECK(nullptr != GameState);
    //CurrentGameState = GameState;
}

void ULSGameplayResultWidget::OnEnhanceClicked()
{
    LSLOG(Warning, TEXT("Enhancemnet UI Open"));
    ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    LSCHECK(nullptr != LSPlayerController);
    LSPlayerController->ShowEnhanceUI();
    LSPlayerController->SetPause(true);
    LSPlayerController->ChangeInputMode(false);
}

void ULSGameplayResultWidget::ShowEnhanceUI()
{
    EnhanceWidget = CreateWidget<ULSEnhanceWidget>(this, EnhanceWidgetClass);
    LSCHECK(nullptr != EnhanceWidget);
    ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    LSCHECK(nullptr != LSPlayerController);
    ALSPlayer* LSPlayer = Cast<ALSPlayer>(LSPlayerController->GetPawn());
    LSCHECK(nullptr != LSPlayer);
    EnhanceWidget->Init(LSPlayer->GetInventoryManager()->GetWeaponDefinitionInList(0),
                        LSPlayer->GetResourceManager());
    EnhanceWidget->AddToViewport();
    LSPlayerController->ChangeInputMode(false);
}
