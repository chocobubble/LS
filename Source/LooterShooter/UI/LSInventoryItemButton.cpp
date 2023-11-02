// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryItemButton.h"
#include "LSInventoryWidget.h"
#include "Styling/SlateTypes.h"

ULSInventoryItemButton::ULSInventoryItemButton()
{
    OnClicked.AddDynamic(this, &ULSInventoryItemButton::Selected);
}

void ULSInventoryItemButton::Init(ULSInventoryWidget* Widget, ULSWeaponDefinition* WeaponDefinition)
{
    InventoryWidget = Widget;
    Weapon = WeaponDefinition;
}

void ULSInventoryItemButton::Selected()
{
    bIsSelected = !bIsSelected;
    if (bIsSelected)
    {
        if (InventoryWidget && InventoryWidget->GetItemClickedButton())
        {
            SetStyle(InventoryWidget->GetItemClickedButton()->GetStyle());
        }
    }
}