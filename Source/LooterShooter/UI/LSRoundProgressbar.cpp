// Fill out your copyright notice in the Description page of Project Settings.


#include "LSRoundProgressbar.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"


void ULSRoundProgressbar::NativeConstruct()
{
    Super::NativeConstruct();
    
    RoundPBImg = Cast<UImage>(GetWidgetFromName(TEXT("pbRound")));
    
    SetPercentPB(0.0f);
    
    SetVisibility(ESlateVisibility::Hidden);
}

void ULSRoundProgressbar::StartReload(float GunReloadTime)
{
    RoundPBInst = RoundPBImg->GetDynamicMaterial();
    SetVisibility(ESlateVisibility::Visible);
    ReloadTime = GunReloadTime;
    SetPercentPB(0.0f);
} 

void ULSRoundProgressbar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (ReloadTime < KINDA_SMALL_NUMBER)
    {
        return;
    }
    ElapsedTime += InDeltaTime;
    SetPercentPB(ElapsedTime);
    if (ElapsedTime >= ReloadTime)
    {
        ReloadTime = 0.0f;
        ElapsedTime = 0.0f;
        SetVisibility(ESlateVisibility::Hidden);
    }
}

void ULSRoundProgressbar::SetPercentPB(float ProgressElapsedTime)
{
    float Percent = (ProgressElapsedTime / ReloadTime) * 0.75f;
    if (RoundPBInst)
    {
        RoundPBInst->SetScalarParameterValue(TEXT("Percent"), Percent);
    }
}