// Fill out your copyright notice in the Description page of Project Settings.


#include "LSHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "LooterShooter/Component/LSCharacterStatComponent.h"
#include "LooterShooter/Character/LSPlayerState.h"
#include "LooterShooter/Component/LSEquipmentComponent.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
#include "LooterShooter/Component/LSDefenseComponent.h"
#include "LooterShooter/Weapon/LSWeaponInstance.h"
#include "LooterShooter/Character/LSPlayer.h"
#include "LSRoundProgressbar.h"
#include "LSInventoryItemSlot.h"
#include "Kismet/GameplayStatics.h"

void ULSHUDWidget::BindCharacterStat(ULSCharacterStatComponent* CharacterStat)
{
    if (CharacterStat)
    {
        CurrentCharacterStat = CharacterStat;
        CurrentCharacterStat->OnHPChanged.AddUObject(this, &ULSHUDWidget::UpdateCharacterStat);
    }
}

void ULSHUDWidget::BindDefenseComponent(ULSDefenseComponent* DefenseManager)
{
    if (DefenseManager)
    {
        CurrentDefenseManager = DefenseManager;
        CurrentDefenseManager->OnHPChanged.AddUObject(this, &ULSHUDWidget::UpdateCurrentHP);
        CurrentDefenseManager->OnShieldChanged.AddUObject(this, &ULSHUDWidget::UpdateCurrentShield);
        CurrentDefenseManager->OnMPChanged.AddUObject(this, &ULSHUDWidget::UpdateCurrentMP);
    }
}

void ULSHUDWidget::BindPlayerState(ALSPlayerState* PlayerState)
{
    if (PlayerState)
    {
        CurrentPlayerState = PlayerState;
        CurrentPlayerState->OnPlayerStateChanged.AddUObject(this, &ULSHUDWidget::UpdatePlayerState);
    }
}

void ULSHUDWidget::BindResourceManageComponent(ULSResourceManageComponent* ResourceManager)
{
    if (ResourceManager)
    {
        CurrentResourceManager = ResourceManager;
        CurrentResourceManager->OnResourceChanged.AddUObject(this, &ULSHUDWidget::UpdateCurrentAmmo);
    }
}

void ULSHUDWidget::BindEquipmentComponent(ULSEquipmentComponent* EquipmentComponent)
{
    if (EquipmentComponent)
    {
        CurrentEquipmentComponent = EquipmentComponent;
        CurrentEquipmentComponent->OnRoundsRemainingChanged.AddUObject(this, &ULSHUDWidget::UpdateRoundsRemaining);
    }
}

void ULSHUDWidget::BindPlayer(ALSPlayer* LSPlayer)
{
    if (LSPlayer)
    {
        CurrentLSPlayer = LSPlayer;
        CurrentLSPlayer->OnInteractProgress.AddUObject(this, &ULSHUDWidget::UpdateInteractProgress);
        CurrentLSPlayer->OnEnableToInteract.AddUObject(this, &ULSHUDWidget::ShowOrHideInteractPopup);
        CurrentLSPlayer->OnReloadProgress.AddUObject(this, &ULSHUDWidget::ShowReloadProgressbar);
    }
}

void ULSHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
    ShieldBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbShield")));
    MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbMP")));
    InteractionProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbInteract")));
    InteractBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("InteractBox")));
    PlayerLevelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
    CurrentExpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentExp")));    
    NextExpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtNextExp")));
    FirstWeaponCurrentAmmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo")));
    FirstWeaponRoundsRemainingText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtRoundsRemaining")));
    SecondWeaponCurrentAmmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo_1")));
    SecondWeaponRoundsRemainingText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtRoundsRemaining_1")));
    ThirdWeaponCurrentAmmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo_2")));
    ThirdWeaponRoundsRemainingText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtRoundsRemaining_2")));
    ReloadProgressbar = Cast<ULSRoundProgressbar>(GetWidgetFromName(TEXT("WB_RoundProgressbar")));
    ItemSlot = Cast<ULSInventoryItemSlot>(GetWidgetFromName(TEXT("UI_InventoryItemSlot")));
    CrosshairCenter = Cast<UImage>(GetWidgetFromName(TEXT("imgCrosshairCenter")));
    CrosshairLeft = Cast<UImage>(GetWidgetFromName(TEXT("imgCrosshairLeft")));
    CrosshairRight = Cast<UImage>(GetWidgetFromName(TEXT("imgCrosshairRight")));
    CrosshairTop = Cast<UImage>(GetWidgetFromName(TEXT("imgCrosshairTop")));
    CrosshairBottom = Cast<UImage>(GetWidgetFromName(TEXT("imgCrosshairBottom")));
    
    if (GEngine == nullptr || GEngine->GameViewport == nullptr)
    {
        return;
    }
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);
    FVector CrosshairWorldPos, CrosshairWorldDir;
    bool bCrosshairScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
        UGameplayStatics::GetPlayerController(this, 0),
        FVector2D(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f),
        CrosshairWorldPos,
        CrosshairWorldDir
    );
    FWidgetTransform WTF = CrosshairCenter->GetRenderTransform();
    WTF.Translation.X = CrosshairWorldPos.X;
    WTF.Translation.Y = CrosshairWorldPos.Y;
    CrosshairCenter->SetRenderTransform(WTF);

    RoundsRemainingTextList.Add(FirstWeaponRoundsRemainingText);
    RoundsRemainingTextList.Add(SecondWeaponRoundsRemainingText);
    RoundsRemainingTextList.Add(ThirdWeaponRoundsRemainingText);
}

void ULSHUDWidget::UpdateCharacterStat()
{
    if (CurrentCharacterStat.IsValid())
    {
        HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
    }
}

void ULSHUDWidget::UpdateCurrentHP()
{
    if (CurrentDefenseManager.IsValid())
    {
        HPBar->SetPercent(CurrentDefenseManager->GetHPRatio());
    }
}

void ULSHUDWidget::UpdateCurrentShield()
{
    if (CurrentDefenseManager.IsValid())
    {
        ShieldBar->SetPercent(CurrentDefenseManager->GetShieldRatio());
    }
}

void ULSHUDWidget::UpdateCurrentMP()
{
    if (CurrentDefenseManager.IsValid())
    {
        MPBar->SetPercent(CurrentDefenseManager->GetMPRatio());
    }
}


void ULSHUDWidget::UpdatePlayerState()
{
    if (CurrentPlayerState.IsValid())
    {
        PlayerLevelText->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
        CurrentExpText->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCurrentExp())));
        NextExpText->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetNextExp())));
    }
}

void ULSHUDWidget::UpdateRoundsRemaining(int32 CurrentWeaponIndex)
{
    if (CurrentEquipmentComponent.IsValid())
    {
        RoundsRemainingTextList[CurrentWeaponIndex]->SetText(FText::FromString(FString::FromInt(CurrentEquipmentComponent->GetRoundsRemaining())));
    }
}

void ULSHUDWidget::UpdateCurrentAmmo()
{
    if (CurrentResourceManager == nullptr || CurrentEquipmentComponent == nullptr)
    {
        return;
    }

    switch(CurrentEquipmentComponent->GetCurrentWeaponIndex())
    {
        case 0:
        {
            if (CurrentEquipmentComponent->GetWeaponInstance(0))
            {
                EAmmoType CurrentAmmoType = CurrentEquipmentComponent->GetWeaponInstance(0)->GetAmmoType();
                if (FirstWeaponCurrentAmmoText)
                {
                    FirstWeaponCurrentAmmoText->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(CurrentAmmoType))));
                }
            }
            break;
        }
        case 1:
        {
            if (CurrentEquipmentComponent->GetWeaponInstance(1))
            {
                EAmmoType CurrentAmmoType = CurrentEquipmentComponent->GetWeaponInstance(1)->GetAmmoType();
                if (SecondWeaponCurrentAmmoText)
                {
                    SecondWeaponCurrentAmmoText->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(CurrentAmmoType))));
                }
            }
            break;
        }
        case 2:
        {
            if (CurrentEquipmentComponent->GetWeaponInstance(2))
            {
                EAmmoType CurrentAmmoType = CurrentEquipmentComponent->GetWeaponInstance(2)->GetAmmoType();
                if (ThirdWeaponCurrentAmmoText)
                {
                    ThirdWeaponCurrentAmmoText->SetText(FText::FromString(FString::FromInt(CurrentResourceManager->GetCurrentAmmo(CurrentAmmoType))));
                }
            }
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
    if (Value)
    {
        InteractBox->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        InteractBox->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ULSHUDWidget::ShowReloadProgressbar(float ReloadTime)
{
    ReloadProgressbar->StartReload(ReloadTime);
}

void ULSHUDWidget::DrawCrosshairs()
{
    //DrawTexture
}
