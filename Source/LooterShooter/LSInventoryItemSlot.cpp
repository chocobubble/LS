// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryItemSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"

void ULSInventoryItemSlot::NativeConstruct()
{
    Super::NativeConstruct();
    SlotBorder = Cast<UBorder>(GetWidgetFromName(TEXT("border")));
    LSCHECK(nullptr != SlotBorder);

    //FLinearColor YellowColor(FColor::Yellow)
    //SlotBorder->SetBrushColor(FColor::Yellow);
    SlotBorder->SetVisibility(ESlateVisibility::Hidden);


    SlotButton = Cast<UButton>(GetWidgetFromName(TEXT("btnItem")));
    LSCHECK(nullptr != SlotButton);
    SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::TurnOn);
    SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::Print);
}

void ULSInventoryItemSlot::Init()
{
    LSCHECK(nullptr != SlotButton);
    SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::TurnOn);
    SlotButton->OnClicked.AddDynamic(this, &ULSInventoryItemSlot::Print);
}

void ULSInventoryItemSlot::TurnOn()
{
    LSLOG(Warning, TEXT("Item Slot Clicked"));
    SlotBorder->SetVisibility(ESlateVisibility::Visible);
}

void ULSInventoryItemSlot::Print()
{
    LSLOG(Warning, TEXT("Clicked"));
}

