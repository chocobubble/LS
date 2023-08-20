// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryItemButton.h"
#include "LSInventoryWidget.h"


void ULSInventoryItemButton::BeginPlay()
{
    Super::BeginPlay();
    OnClicked.AddDynamic(this, &ULSInventoryItemButton::Selected);
}

void ULSInventoryItemButton::Init(ULSInventoryWidget* Widget)
{
    // InventoryWidget = Widget;
    DefaultSelectedButton = Widget->ItemClickedButton;
}

void ULSInventoryItemButton::Selected()
{
    bIsSelected = !bIsSelected;
    if(bIsSelected)
    {
        
    }
}