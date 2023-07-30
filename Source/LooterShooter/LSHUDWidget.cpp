// Fill out your copyright notice in the Description page of Project Settings.


#include "LSHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "LSCharacterStatComponent.h"
#include "LSPlayerState.h"
#include "LSEquipmentComponent.h"
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

void ULSHUDWidget::BindResourceManageComponent(ULSResourceManageComponent* ResourceManager)
{
    LSCHECK(nullptr != ResourceManager);
    CurrentResourceManager = ResourceManager;
    CurrentResourceManager->OnResourceChanged.AddUObject(this, &ULSHUDWidget::UpdateCurrentAmmo);
}

void ULSHUDWidget::BindEquipmentComponent(ULSEquipmentComponent* EquipmentComponent)
{
    LSCHECK(nullptr != EquipmentComponent);
    CurrentEquipmentComponent = EquipmentComponent;
    CurrentEquipmentComponent->OnRoundsRemainingChanged.AddUObject(this, &ULSHUDWidget::UpdateRoundsRemaining);
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


    FirstWeaponCurrentAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo")));
    LSCHECK(nullptr != FirstWeaponCurrentAmmo);

    FirstWeaponRoundsRemaining = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtRoundsRemaining")));
    LSCHECK(nullptr != FirstWeaponRoundsRemaining);

    SecondWeaponCurrentAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo_1")));
    LSCHECK(nullptr != SecondWeaponCurrentAmmo);

    SecondWeaponRoundsRemaining = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtRoundsRemaining_1")));
    LSCHECK(nullptr != SecondWeaponRoundsRemaining);

    ThirdWeaponCurrentAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo_2")));
    LSCHECK(nullptr != ThirdWeaponCurrentAmmo);

    ThirdWeaponRoundsRemaining = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtRoundsRemaining_2")));
    LSCHECK(nullptr != ThirdWeaponRoundsRemaining);

    LSLOG_S(Warning);

    RoundsRemainingTextList.Add(FirstWeaponRoundsRemaining);
    RoundsRemainingTextList.Add(SecondWeaponRoundsRemaining);
    RoundsRemainingTextList.Add(ThirdWeaponRoundsRemaining);
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

/*
void ULSHUDWidget::BindResourceManageComponent(ULSResourceManageComponent* ResourceManageComponent)
{
    /*
    LSCHECK(nullptr != ResourceManageComponent);
    CurrentResourceManageComponent = ResourceManageComponent;
    CurrentResourceManageComponent->OnResourceChanged.AddUObject(this, &ULSHUDWidget::UpdateResource);

    LSCHECK(nullptr != RoundsRemaining);
    LSCHECK(nullptr != CurrentResourceManageComponent);
    LSCHECK(nullptr != CurrentResourceManageComponent->ResourceData);
    //LSCHECK(nullptr != CurrentResourceManageComponent->ResourceData->MaxRifleAmmo);
    RoundsRemaining->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->ResourceData->MaxRifleAmmo)));

    LSLOG_S(Warning);
    */
/*
    LSCHECK(nullptr != ResourceManageComponent);
    CurrentResourceManageComponent = ResourceManageComponent;
    CurrentResourceManageComponent->OnResourceChanged.AddUObject(this, &ULSHUDWidget::UpdateResource);

    LSCHECK(nullptr != CurrentResourceManageComponent);
    FirstWeaponRoundsRemaining->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetRoundsRemaining())));
    FirstWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetCurrentAmmo(EAmmoType::RIFLE))));

    LSLOG_S(Warning);
}
*/
/*
void ULSHUDWidget::UpdateResource()
{
    LSCHECK(CurrentResourceManageComponent.IsValid());

    FirstWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetCurrentAmmo(EAmmoType::RIFLE))));
    FirstWeaponRoundsRemaining->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetRoundsRemaining())));
    SecondWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetCurrentAmmo(EAmmoType::RIFLE))));
    SecondWeaponRoundsRemaining->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetRoundsRemaining())));
    ThirdWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetCurrentAmmo(EAmmoType::RIFLE))));
    ThirdWeaponRoundsRemaining->SetText(FText::FromString(FString::FromInt(CurrentResourceManageComponent->GetRoundsRemaining())));
    LSLOG_S(Warning);
}
*/

void ULSHUDWidget::UpdateRoundsRemaining(int32 CurrentWeaponIndex)
{
    LSCHECK(CurrentEquipmentComponent.IsValid());
    RoundsRemainingTextList[CurrentWeaponIndex]->SetText(FText::FromString(FString::FromInt(CurrentEquipmentComponent->GetRoundsRemaining())));
}


void ULSHUDWidget::UpdateCurrentAmmo()
{
    LSCHECK(CurrentResourceManager.IsValid());
    FirstWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(EAmmoType::RIFLE))));
    SecondWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(EAmmoType::RIFLE))));
    ThirdWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(EAmmoType::RIFLE))));
    LSLOG_S(Warning);
}