// Fill out your copyright notice in the Description page of Project Settings.


#include "LSHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "LSCharacterStatComponent.h"
#include "LSPlayerState.h"

#include "LSResourceManageComponent.h"

void ULSHUDWidget::BindCharacterStat(ULSCharacterStatComponent* CharacterStat)
{
    LSCHECK(nullptr != CharacterStat);
    CurrentCharacterStat = CharacterStat;
    CharacterStat->OnHPChanged.AddUObject(this, &ULSHUDWidget::UpdateCharacterStat);
}

void ULSHUDWidget::BindPlayerState(ALSPlayerState* PlayerState)
{
    LSCHECK(nullptr != PlayerState);
    CurrentPlayerState = PlayerState;
    PlayerState->OnPlayerStateChanged.AddUObject(this, &ULSHUDWidget::UpdatePlayerState);
}

void ULSHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
    LSCHECK(nullptr != HPBar);

    ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
    LSCHECK(nullptr != ExpBar);

    PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
    LSCHECK(nullptr != PlayerLevel);

    CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
    LSCHECK(nullptr != CurrentScore);

    HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
    LSCHECK(nullptr != HighScore);


    CurrentAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo")));
    LSCHECK(nullptr != CurrentAmmo);

    MaxAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtMaxAmmo")));
    LSCHECK(nullptr != MaxAmmo);

    LSLOG_S(Warning);

    
}

//Error: ULSHUDWidget::UpdateCharacterStat(45) ASSERTION : 'CurrentCharacterStat.IsValid()'
void ULSHUDWidget::UpdateCharacterStat()
{
    LSCHECK(CurrentCharacterStat.IsValid());

    HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void ULSHUDWidget::UpdatePlayerState()
{
    LSCHECK(CurrentPlayerState.IsValid());

    // Move somewhere
    //ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());


/*
    if(CurrentPlayerState->GetPlayerName() == "")
    {
        PlayerName->SetText(FText::FromString("Start Man"));
    }
    else
    {
        PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
    }
*/
    PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
    CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));
    
    HighScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameHighScore())));
}


void ULSHUDWidget::BindResourceManageComponent(ULSResourceManageComponent* ResourceManageComponent)
{
    LSCHECK(nullptr != ResourceManageComponent);
    CurrentResourceManageComponent = ResourceManageComponent;
    CurrentResourceManageComponent->OnResourceChanged.AddUObject(this, &ULSHUDWidget::UpdateResource);

    LSCHECK(nullptr != MaxAmmo);
    LSCHECK(nullptr != CurrentResourceManageComponent);
    LSCHECK(nullptr != CurrentResourceManageComponent->ResourceData);
    //LSCHECK(nullptr != CurrentResourceManageComponent->ResourceData->MaxRifleAmmo);
    MaxAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->ResourceData->MaxRifleAmmo)));

    LSLOG_S(Warning);
}

void ULSHUDWidget::UpdateResource()
{
    LSCHECK(CurrentResourceManageComponent.IsValid());

    CurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->ResourceData->CurrentRifleAmmo)));

    LSLOG_S(Warning);
}