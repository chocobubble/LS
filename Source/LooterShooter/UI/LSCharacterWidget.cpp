// Fill out your copyright notice in the Description page of Project Settings.

#include "LSCharacterWidget.h"
#include "Components/ProgressBar.h"
#include "LooterShooter/Component/LSDefenseComponent.h"


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