// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacterWidget.h"

#include "LSCharacterStatComponent.h"

#include "Components/ProgressBar.h"

#include "LSDefenseComponent.h"

/*
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
*/

void ULSCharacterWidget::BindDefenseComponent(ULSDefenseComponent* NewDefenseComponent)
{
    LSCHECK(nullptr != NewDefenseComponent);
    LSLOG(Warning, TEXT("BindDefenseComponent"))
    CurrentDefenseManager = NewDefenseComponent;

    CurrentDefenseManager->OnShieldChanged.AddUObject(this, &ULSCharacterWidget::UpdateShieldWidget);
    CurrentDefenseManager->OnHPChanged.AddUObject(this, &ULSCharacterWidget::UpdateHPWidget);
}


void ULSCharacterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // #include "Components/ProgressBar.h"
    HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
    LSCHECK(nullptr != HPProgressBar);
    UpdateHPWidget();
    ShieldProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_ShieldBar")));
    LSCHECK(nullptr != ShieldProgressBar);
    UpdateShieldWidget();
}

void ULSCharacterWidget::UpdateHPWidget()
{
    if (CurrentDefenseManager.IsValid())
    {
        if (nullptr != HPProgressBar)
        {
            HPProgressBar->SetPercent(CurrentDefenseManager->GetHPRatio());
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