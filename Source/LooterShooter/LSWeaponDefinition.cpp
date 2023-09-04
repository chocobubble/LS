// Fill out your copyright notice in the Description page of Project Settings.

#include "LSWeaponDefinition.h"
#include "LSEquipmentComponent.h"
#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LSWeaponAbilityComponent.h"

ULSWeaponDefinition::ULSWeaponDefinition()
{
    WeaponAbilityComponent = CreateDefaultSubobject<ULSWeaponAbilityComponent>(TEXT("WEAPONABILITY"));
	WeaponInstanceClass = ALSWeaponInstance::StaticClass();
}

ALSWeaponInstance* ULSWeaponDefinition::InstantiateWeapon()
{
	ALSWeaponInstance* NewWeapon = GetWorld()->SpawnActor<ALSWeaponInstance>(FVector::ZeroVector, FRotator::ZeroRotator);
    /** @TODO: 소유자 Player로 설정 */ 
    NewWeapon->SetBaseWeaponDefinition(this);
	NewWeapon->Init();
    return NewWeapon;
}

void ULSWeaponDefinition::SetWeaponDefinitionData(EWeaponType WeaponTypeParam, int32 ItemLevel)
{
	this->WeaponType = WeaponTypeParam;
	WeaponItemLevel = ItemLevel;
	
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	WeaponBaseData = LSGameInstance->GetWeaponData(WeaponType, WeaponItemLevel);
	LSCHECK(WeaponBaseData);
	SetWeaponDefinitionStats();
	WeaponAbilityComponent->EnhanceWeaponStat(this);
}

void ULSWeaponDefinition::SetWeaponDefaultStats()
{
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
	Enhancement = 0;
}

void ULSWeaponDefinition::TryEnhanceWeapon()
{
	float Rnd = FMath::FRandRange(0.f, 1.f);
	if (Rnd <= 0.5f)
	{
		LSLOG(Warning, TEXT("Enhance failed"));
		SetWeaponDefaultStats();
	}
	else
	{
		LSLOG(Warning, TEXT("Enhance succecced"));
		EnhanceWeapon();
	}
}

void ULSWeaponDefinition::EnhanceWeapon()
{
	Enhancement += 1;
	MagazineCapacity = MagazineCapacity * 1.1f;
	BulletDamage = BulletDamage * 1.1f;
	CriticalHitChance = CriticalHitChance * 1.1f;
	CriticalHitMultiplier = CriticalHitMultiplier * 1.1f;
}

void ULSWeaponDefinition::SetWeaponDefinitionStats()
{
	MagazineCapacity = WeaponBaseData->MagazineCapacity + FMath::FRandRange(-10.f, 10.f);
	FireRate = WeaponBaseData->FireRate + FMath::FRandRange(-200.f, 200.f);
	MovementSpeed = WeaponBaseData->MovementSpeed;
	BulletDamage = WeaponBaseData->BulletDamage + FMath::FRandRange(-10.f, 10.f);
	CriticalHitChance = WeaponBaseData->CriticalHitChance + FMath::FRandRange(-0.01f, 0.05f);
	CriticalHitMultiplier = WeaponBaseData->CriticalHitMultiplier + FMath::FRandRange(-0.3f, 0.5f);
	DamageReduceDistance = WeaponBaseData->DamageReduceDistance;
	ReloadTime = WeaponBaseData->ReloadTime + FMath::FRandRange(-0.5f, 0.5f);
	BulletsPerCatridge = WeaponBaseData->BulletsPerCatridge;
	MaxRange = WeaponBaseData->MaxRange;
}