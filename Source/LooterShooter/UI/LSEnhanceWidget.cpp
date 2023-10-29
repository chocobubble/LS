// Fill out your copyright notice in the Description page of Project Settings.


#include "LSEnhanceWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"
#include "LSRoundProgressbar.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"

void ULSEnhanceWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void ULSEnhanceWidget::Init(ULSWeaponDefinition* WeaponDefinition, ULSResourceManageComponent* ResourceManager)
{
    Weapon = WeaponDefinition;
    Resource = ResourceManager;
    GoldText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtGold")));
    EnhancementCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtEnhancement")));
    WeaponTypeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtWeaponType")));
    DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtBulletDamage")));
    CriticalHitChanceText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCriticalHitChance")));
    CriticalHitMultiplierText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCriticalHitMultiplier")));
    EnhancementSuccessText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtSuccess")));
    EnhanceProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbEnhance")));

    
    OnWeaponStatUpdated();
    // TODO: Delegate 연결
    //Weapon->OnWeaponStatChanged.AddUObject(this, &ULSEnhanceWidget::OnWeaponStatUpdated);


    EnhancementButton = Cast<UButton>(GetWidgetFromName(TEXT("btnEnhancement")));
    LSCHECK(nullptr != EnhancementButton );
    EnhancementButton->OnClicked.AddDynamic(this, &ULSEnhanceWidget::OnEnhanceButtonClicked);

    
    BackButton = Cast<UButton>(GetWidgetFromName(TEXT("btnBack")));
    LSCHECK(nullptr != BackButton );
    BackButton->OnClicked.AddDynamic(this, &ULSEnhanceWidget::OnResumeClicked);

}

void ULSEnhanceWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
    if (bIsEnhancing)
    {
        ElapsedTime += DeltaSeconds;
        EnhanceProgressBar->SetPercent(ElapsedTime / EnhancementTime);
        if (ElapsedTime >= EnhancementTime)
        {
            Enhance();
        }
    }
}


void ULSEnhanceWidget::OnEnhanceButtonClicked()
{
    if (Resource->GetGoldAmount() < 100) return;
    LSCHECK(Weapon != nullptr);
    bIsEnhancing = true;
    ElapsedTime = 0.0f;
    bIsEnhanced = Weapon->TryEnhanceWeapon();
    Resource->SetGoldAmount(Resource->GetGoldAmount() - 100);
    
    //LSEnhancePB->StartReload(2.f);
    //LSEnhancePB = Cast<ULSRoundProgressbar>(GetWidgetFromName(TEXT("pbEnhancement")));
    ///LSCHECK(LSEnhancePB != nullptr);
    //LSEnhancePB->SetPercentPB(0.f);
    //LSLOG(Warning, TEXT("check"));
    GetWorld()->GetTimerManager().ClearTimer(EnhancementTimerHandle);
    EnhancementSuccessText->SetText(FText::FromString(TEXT("")));
    GetWorld()->GetTimerManager().SetTimer(EnhancementTimerHandle,
				FTimerDelegate::CreateUObject(this, &ULSEnhanceWidget::Enhance),
                2.f, false);
}

void ULSEnhanceWidget::Enhance()
{
    OnWeaponStatUpdated();
    bIsEnhancing = false;
    if (bIsEnhanced)
    {
        EnhancementSuccessText->SetText(FText::FromString(TEXT("성 공!")));
    }
    else
    {
        EnhancementSuccessText->SetText(FText::FromString(TEXT("실 패!")));
    }
}

void ULSEnhanceWidget::OnWeaponStatUpdated()
{
    LSCHECK(Weapon != nullptr);
    GoldText->SetText(FText::FromString(FString::FromInt(Resource->GetGoldAmount())));
    
    EnhancementCountText->SetText(FText::FromString(FString::FromInt(Weapon->GetEnhancement())));
    // WeaponTypeText->SetText(FText::FromString(FString::FromInt(Weapon->GetEnhancement())));
    DamageText->SetText(FText::FromString(FString::FromInt(Weapon->GetBulletDamage())));
    CriticalHitChanceText->SetText(FText::FromString(FString::FromInt(Weapon->GetCriticalHitChance() * 100)));
    CriticalHitMultiplierText->SetText(FText::FromString(FString::FromInt(Weapon->GetCriticalHitMultiplier() * 100)));      
}

void ULSEnhanceWidget::OnResumeClicked()
{
    //auto LSPlayerController = Cast<ALSPlayerController>(GetOwningPlayer());
    //LSCHECK(nullptr != LSPlayerController);

    RemoveFromParent();

    //LSPlayerController->ChangeInputMode(true);
    //LSPlayerController->SetPause(false);
}