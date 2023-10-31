// Fill out your copyright notice in the Description page of Project Settings.

#include "LSCharacterWidget.h"
#include "Components/ProgressBar.h"
#include "LooterShooter/Component/LSDefenseComponent.h"


void ULSCharacterWidget::BindDefenseComponent(ULSDefenseComponent* NewDefenseComponent)
{
    if (NewDefenseComponent == nullptr)
    {
        return;
    }
    CurrentDefenseManager = NewDefenseComponent;
    CurrentDefenseManager->OnShieldChanged.AddUObject(this, &ULSCharacterWidget::UpdateShieldWidget);
    CurrentDefenseManager->OnHPChanged.AddUObject(this, &ULSCharacterWidget::UpdateHPWidget);
}

void ULSCharacterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
    if (HPProgressBar)
    {
        UpdateHPWidget();
    }
    
    ShieldProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_ShieldBar")));
    if (ShieldProgressBar)
    {
        UpdateShieldWidget();
    }
}

void ULSCharacterWidget::UpdateHPWidget()
{
    if (CurrentDefenseManager)
    {
        if (HPProgressBar)
        {
            HPProgressBar->SetPercent(CurrentDefenseManager->GetHPRatio());
        }
    }
}

void ULSCharacterWidget::UpdateShieldWidget()
{
    if (CurrentDefenseManager)
    {
        if (ShieldProgressBar)
        {
            ShieldProgressBar->SetPercent(CurrentDefenseManager->GetShieldRatio());
        }
    }
}