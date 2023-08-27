// Fill out your copyright notice in the Description page of Project Settings.


#include "LSRoundProgressbar.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"


void ULSRoundProgressbar::NativeConstruct()
{
    Super::NativeConstruct();
    LSLOG(Warning, TEXT("Reload_1"));
    RoundPBImg = Cast<UImage>(GetWidgetFromName(TEXT("pbRound")));
    LSCHECK(nullptr != RoundPBImg);
    
    LSLOG(Warning, TEXT("Reload_2"));
    
    //RoundPBInst = Cast<UMaterialInstanceDynamic>(RoundPBImg->GetBrush().GetResourceObject());  
    

    LSLOG(Warning, TEXT("Reload_3"));

    SetPercentPB(0.0f);
    SetVisibility(ESlateVisibility::Hidden);
    
    // SetPercentPB(0.5f);
    // SetBrushFromMaterial
}

void ULSRoundProgressbar::StartReload(float GunReloadTime)
{
    /*
    LSLOG(Warning, TEXT("Reload_1"));
    
    RoundPBImg = Cast<UImage>(GetWidgetFromName(TEXT("pbRound")));
    LSCHECK(nullptr != RoundPBImg);
    
    LSLOG(Warning, TEXT("Reload_2"));
    
    //RoundPBInst = Cast<UMaterialInstanceDynamic>(RoundPBImg->GetBrush().GetResourceObject());  
    RoundPBInst = RoundPBImg->GetDynamicMaterial();
    LSCHECK(nullptr != RoundPBInst);

    LSLOG(Warning, TEXT("Reload_3"));

    SetPercentPB(0.0f);
    SetVisibility(ESlateVisibility::Hidden);
    */
   RoundPBInst = RoundPBImg->GetDynamicMaterial();
    LSCHECK(nullptr != RoundPBInst);
    SetVisibility(ESlateVisibility::Visible);
    ReloadTime = GunReloadTime;
    SetPercentPB(0.0f);

    LSLOG(Warning, TEXT("Reload_4"));
} 

void ULSRoundProgressbar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if(ReloadTime < KINDA_SMALL_NUMBER) return;
    ElapsedTime += InDeltaTime;
    SetPercentPB(ElapsedTime);
    if(ElapsedTime >= ReloadTime)
    {
        ReloadTime = 0.0f;
        ElapsedTime = 0.0f;
        SetVisibility(ESlateVisibility::Hidden);
        LSLOG(Warning, TEXT("Reload_5"));
    }
}

void ULSRoundProgressbar::SetPercentPB(float ProgressElapsedTime)
{
    float Percent = (ProgressElapsedTime / ReloadTime) * 0.75f;
    //float Percent = ProgressElapsedTime;
    LSCHECK(RoundPBInst != nullptr);
    RoundPBInst->SetScalarParameterValue(TEXT("Percent"), Percent);
}