// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacterWidget.h"

#include "LSCharacterStatComponent.h"

#include "Components/ProgressBar.h"

#include "LSDefenseComponent.h"

void ULSCharacterWidget::BindCharacterStat(ULSCharacterStatComponent* NewCharacterStat)
{
    LSCHECK(nullptr != NewCharacterStat);
    CurrentCharacterStat = NewCharacterStat;

    NewCharacterStat->OnHPChanged.AddUObject(this, &ULSCharacterWidget::UpdateHPWidget);

    NewCharacterStat->OnHPChanged.AddLambda([this]() -> void {
        if(CurrentCharacterStat.IsValid())
        {
            LSLOG(Warning, TEXT("HPRatio : %f"), CurrentCharacterStat->GetHPRatio());
        }
    });
}

void ULSCharacterWidget::BindDefenseComonent(ULSDefenseComonent* NewDefenseComonent)
{
    LSCHECK(nullptr != NewDefenseComonent);
    CurrentDefenseComonent = NewDefenseComonent;

    CurrentDefenseComonent->OnShieldChanged.AddUObject(this, &ULSCharacterWidget::UpdateShieldWidget);
}


void ULSCharacterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // #include "Components/ProgressBar.h"
    HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
    LSCHECK(nullptr != HPProgressBar);
    UpdateHPWidget();
}

void ULSCharacterWidget::UpdateHPWidget()
{
    if (CurrentCharacterStat.IsValid())
    {
        if (nullptr != HPProgressBar)
        {
            HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
        }
    }
}

void ULSCharacterWidget::UpdateShieldWidget()
{
    if (CurrentDefenseManager.IsValid())
    {
        if (nullptr != ShieldProgressBar)
        {
            ShieldProgressBar->SetPercent(CurrentDefenseManager->GetShieldRatio());
        }
    }
}