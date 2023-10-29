// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameplayWidget.h"
#include "Components/Button.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ULSGameplayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
    if (nullptr != ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &ULSGameplayWidget::OnResumeClicked);
    }

    ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
    if (nullptr != ReturnToTitleButton)
    {
        ReturnToTitleButton->OnClicked.AddDynamic(this, &ULSGameplayWidget::OnReturnToTitleClicked);
    }

    RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
    if (nullptr != RetryGameButton)
    {
        RetryGameButton->OnClicked.AddDynamic(this, &ULSGameplayWidget::OnRetryGameClicked);
    }
}

void ULSGameplayWidget::OnResumeClicked()
{
    auto LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    LSCHECK(nullptr != LSPlayerController);

    RemoveFromParent();

    LSPlayerController->ChangeInputMode(true);
    LSPlayerController->SetPause(false);
}

void ULSGameplayWidget::OnReturnToTitleClicked()
{
    // #include "Kismet/GameplayStatics.h"
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void ULSGameplayWidget::OnRetryGameClicked()
{
    auto LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    LSCHECK(nullptr != LSPlayerController);
    LSPlayerController->RestartLevel();
}
