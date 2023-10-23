// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryItemButton.h"
#include "LSInventoryWidget.h"
#include "Styling/SlateTypes.h"

ULSInventoryItemButton::ULSInventoryItemButton()
{
    OnClicked.AddDynamic(this, &ULSInventoryItemButton::Selected);
}

void ULSInventoryItemButton::Init(const ULSInventoryWidget* Widget, ULSWeaponDefinition* WeaponDefinition)
{
    // InventoryWidget = Widget;
    LSLOG(Warning, TEXT("button init"));
    //DefaultSelectedButton = Widget->ItemClickedButton;
    InventoryWidget = Widget;
    LSCHECK(Widget);
    Weapon = WeaponDefinition;
    LSCHECK(Weapon);
    //LSCHECK(DefaultSelectedButton != nullptr);
    //SelectedButtonStyle = DefaultSelectedButton->GetStyle();
}

void ULSInventoryItemButton::Selected()
{
    LSLOG(Warning, TEXT("Button Clicked"));
    bIsSelected = !bIsSelected;
    if (bIsSelected)
    {
        
        LSLOG(Warning, TEXT("Item is selected"));
        LSLOG(Warning, TEXT("Number of Children is : %d"), GetChildrenCount());
        LSCHECK(InventoryWidget != nullptr && InventoryWidget->ItemClickedButton != nullptr);
        SetStyle(InventoryWidget->ItemClickedButton->GetStyle());
        //FButtonStyle SelectedButtonStyle = DefaultSelectedButton->GetStyle();
        //SetStyle(SelectedButtonStyle);
    }
    else
    {
        
        LSLOG(Warning, TEXT("Item isn't selected"));
    }
}