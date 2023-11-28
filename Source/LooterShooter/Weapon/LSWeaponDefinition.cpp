// Fill out your copyright notice in the Description page of Project Settings.

#include "LSWeaponDefinition.h"
#include "LooterShooter/Component/LSEquipmentComponent.h"
#include "LooterShooter/System/LSGameInstance.h"
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
	WeaponInstance = NewWeapon;
    return NewWeapon;
}

void ULSWeaponDefinition::SetWeaponDefinitionData(FWeaponSaveData* WeaponSaveDataPtr)
{
	WeaponSaveData = WeaponSaveDataPtr;
	WeaponType = WeaponSaveData->GetWeaponType();
	WeaponItemLevel = WeaponSaveData->GetWeaponLevel();
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (LSGameInstance)
	{
		WeaponBaseData = LSGameInstance->GetWeaponData(WeaponType, WeaponItemLevel);
		if (WeaponBaseData)
		{
			SetWeaponDefaultStats();
		}
	}

	EnhancementLevel = WeaponSaveData->GetEnhancementLevel();
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
	//OnWeaponStatChanged.Broadcast();
}

bool ULSWeaponDefinition::TryEnhanceWeapon()
{
	bool ReturnValue;
	const float Rnd = FMath::FRandRange(0.0f, 1.0f);
	if (Rnd <= 0.5f)
	{
		SetWeaponDefaultStats();
		ReturnValue = false;
	}
	else
	{
		++EnhancementLevel;
		EnhanceWeapon();
		ReturnValue = true;
	}
	WeaponInstance->SetWeaponStats();
	WeaponSaveData->SetEnhancementLevel(EnhancementLevel);
	OnWeaponStatChanged.Broadcast();
	LSLOG(Warning, TEXT("Enhance result : level - %d, enhance - %d"), WeaponSaveData->GetWeaponLevel(), WeaponSaveData->GetEnhancementLevel());

	return ReturnValue;
}

void ULSWeaponDefinition::EnhanceWeapon()
{
	MagazineCapacity = MagazineCapacity * 1.1f;
	BulletDamage = BulletDamage * 1.1f;
	CriticalHitChance = CriticalHitChance * 1.1f;
	CriticalHitMultiplier = CriticalHitMultiplier * 1.1f;
	//OnWeaponStatChanged.Broadcast(); 
}

void ULSWeaponDefinition::SetWeaponDefinitionStats()
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
}