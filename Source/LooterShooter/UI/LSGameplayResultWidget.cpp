// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameplayResultWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "LooterShooter/GameMode/LSGameState.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LooterShooter/UI/LSEnhanceWidget.h"
#include "LooterShooter/Component/LSInventoryComponent.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"

void ULSGameplayResultWidget::NativeConstruct()
{
    Super::NativeConstruct();

    EnhanceButton = Cast<UButton>(GetWidgetFromName(TEXT("btnEnhance")));
    if (EnhanceButton)
    {
        EnhanceButton->OnClicked.AddDynamic(this, &ULSGameplayResultWidget::OnEnhanceClicked);
    }
}


void ULSGameplayResultWidget::BindGameState(ALSGameState* GameState)
{
    
}

void ULSGameplayResultWidget::OnEnhanceClicked()
{
    LSPlayerController = LSPlayerController ? LSPlayerController : Cast<ALSPlayerController>(GetOwningPlayer());
    if (LSPlayerController)
    {
        LSPlayerController->OnEnhanceUIOpen();
        LSPlayerController->SetPause(true);
        LSPlayerController->ChangeInputMode(false);
    }
}

void ULSGameplayResultWidget::ShowEnhanceUI()
{
    EnhanceWidget = EnhanceWidget ? EnhanceWidget : CreateWidget<ULSEnhanceWidget>(this, EnhanceWidgetClass);
    LSPlayerController = LSPlayerController ? LSPlayerController : Cast<ALSPlayerController>(GetOwningPlayer());
    if (EnhanceWidget && LSPlayerController)
    {   
        ALSPlayer* LSPlayer = Cast<ALSPlayer>(LSPlayerController->GetPawn());
        if (LSPlayer)
        {
            EnhanceWidget->Init(LSPlayer->GetInventoryManager()->GetWeaponDefinitionInList(0), LSPlayer->GetResourceManager());
            EnhanceWidget->AddToViewport();
            LSPlayerController->ChangeInputMode(false);
        }
    }
}
