// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryItemSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULSInventoryItemSlot::NativeConstruct()
{
    Super::NativeConstruct();

    SlotBorder = Cast<UBorder>(GetWidgetFromName(TEXT("border")));
    if (SlotBorder)
    {
        SlotBorder->SetVisibility(ESlateVisibility::Hidden);
    }
    
    SlotButton = Cast<UButton>(GetWidgetFromName(TEXT("btnItem")));
    if (SlotButton)
    {  
        SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::TurnOn);
        SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::Print);
    }
    
    ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    GunImage = Cast<UImage>(GetWidgetFromName(TEXT("imgGun")));
    if (LSGameInstance && GunImage)
    {
        GunImage->SetBrushFromMaterial(LSGameInstance->GetMIRifle());
    }
}

void ULSInventoryItemSlot::Init(ULSWeaponDefinition* WeaponDefinition)
{
    ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (LSGameInstance == nullptr)
    {
        return;
    }

    if (WeaponDefinition && GunImage)
    {
        if (WeaponDefinition->GetWeaponType() == EWeaponType::EWT_Rifle) 
        {
            GunImage->SetBrushFromMaterial(LSGameInstance->GetMIRifle());
        }
    }
}


void ULSInventoryItemSlot::TurnOn()
{
    if (bIsTurnedOn)
    {
        SlotBorder->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        SlotBorder->SetVisibility(ESlateVisibility::Visible);
    }
    bIsTurnedOn = !bIsTurnedOn;
}

void ULSInventoryItemSlot::Print()
{
    
}

