// Fill out your copyright notice in the Description page of Project Settings.


#include "LSHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "LSCharacterStatComponent.h"
#include "LSPlayerState.h"
#include "LSEquipmentComponent.h"
#include "LSResourceManageComponent.h"
#include "LSDefenseComponent.h"
#include "LSWeaponInstance.h"
#include "LSPlayer.h"
#include "LSRoundProgressbar.h"
#include "LSInventoryItemSlot.h"

void ULSHUDWidget::BindCharacterStat(ULSCharacterStatComponent* CharacterStat)
{
    LSCHECK(nullptr != CharacterStat);
    CurrentCharacterStat = CharacterStat;
    CharacterStat->OnHPChanged.AddUObject(this, &ULSHUDWidget::UpdateCharacterStat);
}

void ULSHUDWidget::BindDefenseComponent(ULSDefenseComponent* DefenseManager)
{
    LSCHECK(nullptr != DefenseManager);
    CurrentDefenseManager = DefenseManager;
    DefenseManager->OnHPChanged.AddUObject(this, &ULSHUDWidget::UpdateCurrentHP);
    DefenseManager->OnShieldChanged.AddUObject(this, &ULSHUDWidget::UpdateCurrentShield);
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

void ULSHUDWidget::BindPlayer(ALSPlayer* LSPlayer)
{
    LSCHECK(nullptr != LSPlayer);
    CurrentLSPlayer = LSPlayer;
    CurrentLSPlayer->OnInteractProgress.AddUObject(this, &ULSHUDWidget::UpdateInteractProgress);
    CurrentLSPlayer->OnEnableToInteract.AddUObject(this, &ULSHUDWidget::ShowOrHideInteractPopup);
    CurrentLSPlayer->OnReloadProgress.AddUObject(this, &ULSHUDWidget::ShowReloadProgressbar);
}

void ULSHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
    LSCHECK(nullptr != HPBar);

    ShieldBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbShield")));
    LSCHECK(nullptr != ShieldBar);

    ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
    LSCHECK(nullptr != ExpBar);

    InteractionProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbInteract")));
    LSCHECK(nullptr != InteractionProgressBar);

    InteractBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("InteractBox")));
    LSCHECK(nullptr != InteractBox);

    ReloadBox = Cast<USizeBox>(GetWidgetFromName(TEXT("boxReload")));
    LSCHECK(nullptr != ReloadBox);

    PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
    LSCHECK(nullptr != PlayerLevel);

    CurrentExp = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentExp")));
    LSCHECK(nullptr != CurrentExp);

    NextExp = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtNextExp")));
    LSCHECK(nullptr != NextExp);

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

    
    // ItemSlot->Init();

    LSLOG_S(Warning);

    RoundsRemainingTextList.Add(FirstWeaponRoundsRemaining);
    RoundsRemainingTextList.Add(SecondWeaponRoundsRemaining);
    RoundsRemainingTextList.Add(ThirdWeaponRoundsRemaining);

    ReloadProgressbar = Cast<ULSRoundProgressbar>(GetWidgetFromName(TEXT("WB_RoundProgressbar")));
    LSCHECK(nullptr != ReloadProgressbar);

    ItemSlot = Cast<ULSInventoryItemSlot>(GetWidgetFromName(TEXT("UI_InventoryItemSlot")));
    LSCHECK(nullptr != ItemSlot);
}

//Error: ULSHUDWidget::UpdateCharacterStat(45) ASSERTION : 'CurrentCharacterStat.IsValid()'
void ULSHUDWidget::UpdateCharacterStat()
{
    LSCHECK(CurrentCharacterStat.IsValid());

    HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void ULSHUDWidget::UpdateCurrentHP()
{
    LSCHECK(CurrentDefenseManager.IsValid());
    // LSLOG_S(Warning);
    HPBar->SetPercent(CurrentDefenseManager->GetHPRatio());
}

void ULSHUDWidget::UpdateCurrentShield()
{
    LSCHECK(CurrentDefenseManager.IsValid());
    // LSLOG_S(Warning);
    ShieldBar->SetPercent(CurrentDefenseManager->GetShieldRatio());
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
    CurrentExp->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCurrentExp())));
    
    NextExp->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetNextExp())));
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
    switch(CurrentEquipmentComponent->GetCurrentWeaponIndex())
    {
        case 0 :
        {
            EAmmoType CurrentAmmoType = CurrentEquipmentComponent->GetWeaponInstance(0)->GetAmmoType();
            FirstWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(CurrentAmmoType))));
            break;
        }
        case 1 :
        {
            EAmmoType CurrentAmmoType = CurrentEquipmentComponent->GetWeaponInstance(1)->GetAmmoType();
            SecondWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(CurrentAmmoType))));
            break;
        }
        case 2 :
        {
            EAmmoType CurrentAmmoType = CurrentEquipmentComponent->GetWeaponInstance(2)->GetAmmoType();
            ThirdWeaponCurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(CurrentAmmoType))));
            break;
        }
    }
}

void ULSHUDWidget::UpdateInteractProgress(float ElapsedRatio)
{
    InteractionProgressBar->SetPercent(ElapsedRatio);
}

void ULSHUDWidget::ShowOrHideInteractPopup(bool Value)
{
    if(Value == true)
    {
        LSLOG(Warning, TEXT("Show interact popup.."));
        InteractBox->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        LSLOG(Warning, TEXT("hide interact popup.."));
        InteractBox->SetVisibility(ESlateVisibility::Hidden);
    }
}


void ULSHUDWidget::ShowReloadProgressbar(float ReloadTime)
{
    ReloadProgressbar->StartReload(ReloadTime);
}