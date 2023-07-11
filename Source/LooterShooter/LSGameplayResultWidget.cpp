// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameplayResultWidget.h"
#include "Components/TextBlock.h"
#include "LSGameState.h"

void ULSGameplayResultWidget::BindGameState(class ALSGameState* GameState)
{
    LSCHECK(nullptr != GameState);
    CurrentGameState = GameState;
}

void ULSGameplayResultWidget::NativeConstruct()
{
    Super::NativeConstruct();

    auto Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
    LSCHECK(nullptr != Result);

    Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Complete") : TEXT("Mission Failed")));

    auto TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
    LSCHECK(nullptr != TotalScore);
    TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));


}