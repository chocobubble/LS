// Fill out your copyright notice in the Description page of Project Settings.


#include "LSTextPopup.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"

ALSTextPopup::ALSTextPopup()
{
    LSLOG(Warning, TEXT("Text popup constructor"));
    // 	#include "Components/TextRenderComponent.h"
    GetTextRender()->SetText(FText::FromString(TEXT("TEXT")));


}

void ALSTextPopup::BeginPlay()
{
    //Destroy();
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
			LSLOG(Warning, TEXT("Destroy text"));
            Destroy();
		}), DisappearTimer, false);
    
}

void ALSTextPopup::SetPopupText(int32 PopupText)
{
    GetTextRender()->SetText(FText::FromString(FString::FromInt(PopupText)));
}


void ALSTextPopup::SetTextRotation(FVector FromVector, FVector ToVector)
{
    SetActorRotation(UKismetMathLibrary::FindLookAtRotation(FromVector, ToVector));
}