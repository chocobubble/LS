// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameplayWidget.h"
#include "Components/Button.h"
#include "LooterShooter/Character/LSPlayerController.h"
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

    RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
    if (RetryGameButton)
    {
        RetryGameButton->OnClicked.AddDynamic(this, &ULSGameplayWidget::OnRetryGameClicked);
    }
}

void ULSGameplayWidget::OnResumeClicked()
{
    ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    if (ALSPlayerController)
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

void ULSGameplayWidget::OnRetryGameClicked()
{
    ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    if (LSPlayerController)
    {
        LSPlayerController->RestartLevel();
    }
}
