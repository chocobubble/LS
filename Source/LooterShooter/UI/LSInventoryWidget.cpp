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
/*
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_MANNY(TEXT("/Game/LS/Meshes/SKM_Player.SKM_Player"));
	if ( SKM_MANNY.Succeeded() )
	{
		
	}
*/
    ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
    LSCHECK(nullptr != ResumeButton );
    ResumeButton->OnClicked.AddDynamic(this, &ULSInventoryWidget::OnResumeClicked);
}

void ULSInventoryWidget::Init(ULSInventoryComponent* InventoryComponent)
{
    Inventory = InventoryComponent;
    for (int32 Idx = 0; Idx < 3; ++Idx) 
    {
        FString InventoryItemName = "imgGun_" + FString::FromInt(Idx);
        GunImages.Add(Cast<UImage>(GetWidgetFromName(*InventoryItemName)));
        LSCHECK(nullptr != GunImages[Idx]);
        InventoryItemName = "btnItem_" + FString::FromInt(Idx);
        InventoryItemButtons.Add(Cast<UButton>(GetWidgetFromName(*InventoryItemName)));
        LSCHECK(nullptr != InventoryItemButtons[Idx]);
        InventoryItemButtons[Idx]->OnClicked.AddDynamic(this, &ULSInventoryWidget::OnInventoryItemClicked);

        InventoryItemName = "btnItem_" + FString::FromInt(Idx+3);
        LSInventoryItemButtons.Add(Cast<ULSInventoryItemButton>(GetWidgetFromName(*InventoryItemName)));
        LSCHECK(nullptr != LSInventoryItemButtons[Idx]);
        LSInventoryItemButtons[Idx]->Init(this, InventoryComponent->GetWeaponDefinitionInList(Idx));
    }

    for (int32 Idx = 0; Idx < 3; ++Idx) 
    {
        FString EquippedItemName = "imgEquippedGun_" + FString::FromInt(Idx);
        EquippedGunImages.Add(Cast<UImage>(GetWidgetFromName(*EquippedItemName)));
        LSCHECK(nullptr != EquippedGunImages[Idx]);
        EquippedItemName = "btnEquippedGun_" + FString::FromInt(Idx);
        EquippedGunButtons.Add(Cast<UButton>(GetWidgetFromName(*EquippedItemName)));
        LSCHECK(nullptr != EquippedGunButtons[Idx]);
    }

    ItemClickedButton = Cast<UButton>(GetWidgetFromName(TEXT("btnItemClicked")));
    LSCHECK(ItemClickedButton != nullptr);
/*
    GunImage1 = Cast<UImage>(GetWidgetFromName(TEXT("imgGun_1")));
    LSCHECK(nullptr != GunImage1);
    GunImage2 = Cast<UImage>(GetWidgetFromName(TEXT("imgGun_2")));
    LSCHECK(nullptr != GunImage2);
    GunImage3 = Cast<UImage>(GetWidgetFromName(TEXT("imgEquippedGun")));
    LSCHECK(nullptr != GunImage3);

    GunImage2->SetBrush(GunImage3->GetBrush());
*/
    GunImages[0]->SetBrush(EquippedGunImages[0]->GetBrush()); 
    EquippedGunImages[1]->SetBrush(EquippedGunImages[0]->GetBrush()); 
    //FSlateColor Y(FColor::Yellow);
    //FSlateBrushOutlineSettings BtnOutlineSetting(Y, 2f);
    //FSlateBrush tempBrush;
    /*
    FColor Ye = FColor::Yellow;
    Yel = new FSlateColor(Ye);
    tempBrush.OutlineSettings.Color = *Yel;
    FButtonStyle tempStyle = EquippedGunButtons[2]->GetStyle();
    FButtonStyle temp2Styel = tempStyle.SetNormal(tempBrush);
    EquippedGunButtons[2]->SetStyle(temp2Styel);
    */
   
    FLinearColor LC(FColor::Yellow);
    EquippedGunButtons[2]->SetColorAndOpacity(LC);
    InventoryItemButtons[2]->SetStyle(ItemClickedButton->GetStyle());
}

void ULSInventoryWidget::OnResumeClicked()
{
    auto LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    LSCHECK(nullptr != LSPlayerController);

    RemoveFromParent();

    LSPlayerController->ChangeInputMode(true);
    LSPlayerController->SetPause(false);
}

void ULSInventoryWidget::OnInventoryItemClicked()
{
    LSLOG(Warning, TEXT("Item Button Clicked"));
    for (UButton* ItemButton : InventoryItemButtons)
    {
        if (ItemButton->IsPressed())
        {
            LSLOG(Warning, TEXT("Pressed Item Button"));
            ItemButton->SetStyle(ItemClickedButton->GetStyle());
            break;
        }
    }
}