// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameplayWidget.h"
#include "Components/Button.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Character/LSPlayerState.h"
#include "LooterShooter/Network/HttpActor.h"
#include "Kismet/GameplayStatics.h"

void ULSGameplayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &ULSGameplayWidget::OnResumeClicked);
    }

    ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
    if (ReturnToTitleButton)
    {
        ReturnToTitleButton->OnClicked.AddDynamic(this, &ULSGameplayWidget::OnReturnToTitleClicked);
    }

    SaveButton = Cast<UButton>(GetWidgetFromName(TEXT("btnSave")));
    if (SaveButton)
    {
        SaveButton->OnClicked.AddDynamic(this, &ULSGameplayWidget::OnSaveClicked);
    }
}

void ULSGameplayWidget::OnResumeClicked()
{
    ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    if (LSPlayerController)
    {
        RemoveFromParent();

        LSPlayerController->ChangeInputMode(true);
        LSPlayerController->SetPause(false);
    }
}

void ULSGameplayWidget::OnReturnToTitleClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void ULSGameplayWidget::OnSaveClicked()
{
    ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    if (LSPlayerController)
    {
        ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(LSPlayerController->PlayerState);
        if (LSPlayerState)
        {
            LSPlayerState->SaveDataToServer();
        }
    }
}
