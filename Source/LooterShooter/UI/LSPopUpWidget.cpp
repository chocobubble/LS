// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPopUpWidget.h"
#include "Components/TextBlock.h"

void ULSPopUpWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    PopUpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPopUp")));

    GetWorld()->GetTimerManager().SetTimer(
        DestroyTimerHandle, 
        FTimerDelegate::CreateLambda([this]()->void {
			RemoveFromParent();}),
        DisappearTimer,
        false
    );
}
