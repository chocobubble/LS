// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory.h"
#include "Components/Button.h"
#include "Components/Image.h"


 void UUI_Inventory::NativeConstruct()
{
    Super::NativeConstruct();
    GunImage1 = Cast<UImage>(GetWidgetFromName(TEXT("gunImage")));
    GunImage2 = Cast<UImage>(GetWidgetFromName(TEXT("gunImage_1")));
    GunImage3 = Cast<UImage>(GetWidgetFromName(TEXT("gunImage_2")));

    GunImage2->SetBrush(GunImage1->GetBrush());
}