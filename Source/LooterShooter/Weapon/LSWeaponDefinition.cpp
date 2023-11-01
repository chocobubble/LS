// Fill out your copyright notice in the Description page of Project Settings.

#include "LSWeaponDefinition.h"
#include "LooterShooter/Component/LSEquipmentComponent.h"
#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LooterShooter/Component/LSWeaponAbilityComponent.h"

ULSWeaponDefinition::ULSWeaponDefinition()
{
    WeaponAbilityComponent = CreateDefaultSubobject<ULSWeaponAbilityComponent>(TEXT("WEAPONABILITY"));
	WeaponInstanceClass = ALSWeaponInstance::StaticClass();
}

ALSWeaponInstance* ULSWeaponDefinition::InstantiateWeapon()
{
	ALSWeaponInstance* NewWeapon = GetWorld()->SpawnActor<ALSWeaponInstance>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (NewWeapon)
	{
    	/** @TODO: 소유자 Player로 설정 */ 
    	NewWeapon->SetBaseWeaponDefinition(this);
		NewWeapon->Init();
	}
    return NewWeapon;
}

void ULSWeaponDefinition::SetWeaponDefinitionData(EWeaponType WeaponTypeParam, int32 WeaponLevel, int32 WeaponEnhancementLevel)
{
	this->WeaponType = WeaponTypeParam;
	WeaponItemLevel = WeaponLevel;
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (LSGameInstance)
	{
		WeaponBaseData = LSGameInstance->GetWeaponData(WeaponType, WeaponItemLevel);
		if (WeaponBaseData)
		{
			SetWeaponDefaultStats();
		}
	}

	EnhancementLevel = WeaponEnhancementLevel;
	if (EnhancementLevel > 0)
	{
		for (int32 Idx = 0; Idx < EnhancementLevel; ++Idx)
		{
			EnhanceWeapon();
		}
	}

	if (WeaponAbilityComponent)
	{
		WeaponAbilityComponent->EnhanceWeaponStat(this);
	}
}

void ULSWeaponDefinition::SetWeaponDefaultStats()
{
	if (WeaponBaseData == nullptr)
	{
		return;
	}
	MagazineCapacity = WeaponBaseData->MagazineCapacity;
	FireRate = WeaponBaseData->FireRate;
	MovementSpeed = WeaponBaseData->MovementSpeed;
	BulletDamage = WeaponBaseData->BulletDamage;
	CriticalHitChance = WeaponBaseData->CriticalHitChance;
	CriticalHitMultiplier = WeaponBaseData->CriticalHitMultiplier;
	DamageReduceDistance = WeaponBaseData->DamageReduceDistance;
	ReloadTime = WeaponBaseData->ReloadTime;
	BulletsPerCatridge = WeaponBaseData->BulletsPerCatridge;
	MaxRange = WeaponBaseData->MaxRange;
	EnhancementLevel = 0;
	OnWeaponStatChanged.Broadcast();
}

bool ULSWeaponDefinition::TryEnhanceWeapon()
{
	const float Rnd = FMath::FRandRange(0.0f, 1.0f);
	if (Rnd <= 0.5f)
	{
		SetWeaponDefaultStats();
		return false;
	}
	else
	{
		++EnhancementLevel;
		EnhanceWeapon();
		return true;
	}
}

void ULSWeaponDefinition::EnhanceWeapon()
{
	MagazineCapacity = MagazineCapacity * 1.1f;
	BulletDamage = BulletDamage * 1.1f;
	CriticalHitChance = CriticalHitChance * 1.1f;
	CriticalHitMultiplier = CriticalHitMultiplier * 1.1f;
	OnWeaponStatChanged.Broadcast();
}

void ULSWeaponDefinition::SetWeaponDefinitionStats()
{
	if (WeaponBaseData == nullptr)
	{
		return;
	}

	MagazineCapacity = WeaponBaseData->MagazineCapacity + FMath::FRandRange(-10.0f, 10.0f);
	FireRate = WeaponBaseData->FireRate + FMath::FRandRange(-200.0f, 200.0f);
	MovementSpeed = WeaponBaseData->MovementSpeed;
	BulletDamage = WeaponBaseData->BulletDamage + FMath::FRandRange(-10.0f, 10.0f);
	CriticalHitChance = WeaponBaseData->CriticalHitChance + FMath::FRandRange(-0.01f, 0.05f);
	CriticalHitMultiplier = WeaponBaseData->CriticalHitMultiplier + FMath::FRandRange(-0.3f, 0.5f);
	DamageReduceDistance = WeaponBaseData->DamageReduceDistance;
	ReloadTime = WeaponBaseData->ReloadTime + FMath::FRandRange(-0.5f, 0.5f);
	BulletsPerCatridge = WeaponBaseData->BulletsPerCatridge;
	MaxRange = WeaponBaseData->MaxRange;
}