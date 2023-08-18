// Fill out your copyright notice in the Description page of Project Settings.


#include "LSInventoryWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "LSPlayerController.h"
#include "Kismet/GameplayStatics.h"

 void ULSInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
    GunImage1 = Cast<UImage>(GetWidgetFromName(TEXT("imgGun_1")));
    LSCHECK(nullptr != GunImage1);
    GunImage2 = Cast<UImage>(GetWidgetFromName(TEXT("imgGun_2")));
    LSCHECK(nullptr != GunImage2);
    GunImage3 = Cast<UImage>(GetWidgetFromName(TEXT("imgEquippedGun")));
    LSCHECK(nullptr != GunImage3);

    GunImage2->SetBrush(GunImage1->GetBrush());

    ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
    LSCHECK(nullptr != ResumeButton );
    ResumeButton->OnClicked.AddDynamic(this, &ULSInventoryWidget::OnResumeClicked);
}

void ULSInventoryWidget::OnResumeClicked()
{
    auto LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    LSCHECK(nullptr != LSPlayerController);

    RemoveFromParent();

    LSPlayerController->ChangeInputMode(true);
    LSPlayerController->SetPause(false);
}