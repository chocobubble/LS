// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameplayResultWidget.h"
#include "Components/TextBlock.h"

void ULSGameplayResultWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UTextBlock* Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
    LSCHECK(nullptr != Result);

    UTextBlock* TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
    LSCHECK(nullptr != TotalScore);
}