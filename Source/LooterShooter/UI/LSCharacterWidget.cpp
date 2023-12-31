// Fill out your copyright notice in the Description page of Project Settings.

#include "LSCharacterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
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
    if (CurrentDefenseManager.IsValid())
    {
        if (HPProgressBar)
        {
            HPProgressBar->SetPercent(CurrentDefenseManager->GetHPRatio());
        }
    }
}

void ULSCharacterWidget::UpdateShieldWidget()
{
    if (CurrentDefenseManager.IsValid())
    {
        if (ShieldProgressBar)
        {
            ShieldProgressBar->SetPercent(CurrentDefenseManager->GetShieldRatio());
        }
    }
}

void ULSCharacterWidget::SetMonsterLevel(int32 Level)
{
    MonsterLevel = Level;
    LevelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtMonsterLevel")));
    if (LevelText)
    {
        LSLOG(Warning, TEXT(" Set MOnster Level %d"), MonsterLevel);
        LevelText->SetText(FText::FromString(FString::FromInt(MonsterLevel)));
    }
}
