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
    LSCHECK(nullptr != SlotBorder);
    GunImage = Cast<UImage>(GetWidgetFromName(TEXT("imgGun")));
    LSCHECK(nullptr != GunImage);

    //FLinearColor YellowColor(FColor::Yellow)`
    //SlotBorder->SetBrushColor(FColor::Yellow);
    SlotBorder->SetVisibility(ESlateVisibility::Hidden);


    SlotButton = Cast<UButton>(GetWidgetFromName(TEXT("btnItem")));
    LSCHECK(nullptr != SlotButton);
    SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::TurnOn);
    SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::Print);

    //later, delete
    ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    LSCHECK(LSGameInstance != nullptr); 
    LSCHECK(GunImage != nullptr);
    GunImage->SetBrushFromMaterial(LSGameInstance->MI_Rifle);
}


void ULSInventoryItemSlot::Init(ULSWeaponDefinition* WeaponDefinition)
{
    LSCHECK(WeaponDefinition != nullptr);
    ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (WeaponDefinition->GetWeaponType() == EWeaponType::RIFLE) 
    {
        LSCHECK(GunImage != nullptr);
        GunImage->SetBrushFromMaterial(LSGameInstance->MI_Rifle);
    }

    // later delete
    LSCHECK(GunImage != nullptr);
    GunImage->SetBrushFromMaterial(LSGameInstance->MI_Rifle);
}


void ULSInventoryItemSlot::TurnOn()
{
    LSLOG(Warning, TEXT("Item Slot Clicked"));
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
    LSLOG(Warning, TEXT("Clicked"));
}

