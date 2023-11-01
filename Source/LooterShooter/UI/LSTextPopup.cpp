// Fill out your copyright notice in the Description page of Project Settings.


#include "LSTextPopup.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"

ALSTextPopup::ALSTextPopup()
{
    GetTextRender()->SetText(FText::FromString(TEXT("TEXT")));
}

void ALSTextPopup::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(
        DisappearTimerHandle, 
        FTimerDelegate::CreateLambda([this]()->void {
			LSLOG(Warning, TEXT("Destroy text"));
            Destroy();}),
        DisappearTimer,
        false
    );
}

void ALSTextPopup::SetPopupText(int32 PopupText)
{
    GetTextRender()->SetText(FText::FromString(FString::FromInt(PopupText)));
}


void ALSTextPopup::SetTextRotation(const FVector& FromVector, const FVector& ToVector)
{
    SetActorRotation(UKismetMathLibrary::FindLookAtRotation(FromVector, ToVector));
}