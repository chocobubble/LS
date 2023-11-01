// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateColor.h"
#include "Math/Color.h"
#include "LSInventoryItemButton.h"
#include "LooterShooter/Component/LSInventoryComponent.h"

void ULSInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &ULSInventoryWidget::OnResumeClicked);
    }
}

void ULSInventoryWidget::Init(ULSInventoryComponent* InventoryComponent)
{
    Inventory = InventoryComponent;
    for (int32 Idx = 0; Idx < 3; ++Idx) 
    {
        FString InventoryItemName = "imgGun_" + FString::FromInt(Idx);
        GunImages.Add(Cast<UImage>(GetWidgetFromName(*InventoryItemName)));
        if (GunImages[Idx])
        {
            InventoryItemName = "btnItem_" + FString::FromInt(Idx);
            InventoryItemButtons.Add(Cast<UButton>(GetWidgetFromName(*InventoryItemName)));
        }
        if (InventoryItemButtons[Idx])
        {
            InventoryItemButtons[Idx]->OnClicked.AddDynamic(this, &ULSInventoryWidget::OnInventoryItemClicked);
            InventoryItemName = "btnItem_" + FString::FromInt(Idx+3);

        }
        
        LSInventoryItemButtons.Add(Cast<ULSInventoryItemButton>(GetWidgetFromName(*InventoryItemName)));
        if (LSInventoryItemButtons[Idx])
        {
            LSInventoryItemButtons[Idx]->Init(this, InventoryComponent->GetWeaponDefinitionInList(Idx));
        }
    }

    for (int32 Idx = 0; Idx < 3; ++Idx) 
    {
        FString EquippedItemName = "imgEquippedGun_" + FString::FromInt(Idx);
        EquippedGunImages.Add(Cast<UImage>(GetWidgetFromName(*EquippedItemName)));
        if (EquippedGunImages[Idx])
        {
            EquippedItemName = "btnEquippedGun_" + FString::FromInt(Idx);
        }
        
        EquippedGunButtons.Add(Cast<UButton>(GetWidgetFromName(*EquippedItemName)));
    }

    ItemClickedButton = Cast<UButton>(GetWidgetFromName(TEXT("btnItemClicked")));

///////////// 테스트 용도 ////////////
    GunImages[0]->SetBrush(EquippedGunImages[0]->GetBrush()); 
    EquippedGunImages[1]->SetBrush(EquippedGunImages[0]->GetBrush()); 
   
    FLinearColor LC(FColor::Yellow);
    EquippedGunButtons[2]->SetColorAndOpacity(LC);
    InventoryItemButtons[2]->SetStyle(ItemClickedButton->GetStyle());
///////////////////////////////////////
}

void ULSInventoryWidget::OnResumeClicked()
{
    ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    if (LSPlayerController)
    {
        RemoveFromParent();
        LSPlayerController->ChangeInputMode(true);
        LSPlayerController->SetPause(false);
    }
}

void ULSInventoryWidget::OnInventoryItemClicked()
{
    for (UButton* ItemButton : InventoryItemButtons)
    {
        if (ItemButton && ItemButton->IsPressed() && ItemClickedButton)
        {
            ItemButton->SetStyle(ItemClickedButton->GetStyle());
            break;
        }
    }
}
