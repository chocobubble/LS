// Fill out your copyright notice in the Description page of Project Settings.

#include "LSWeaponDefinition.h"
#include "LSEquipmentComponent.h"
#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LSWeaponAbilityComponent.h"
#include "LSGameState.h"

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
	ALSGameState* LSGameState = Cast<ALSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	
	WeaponBaseData = LSGameState->GetLSWeaponData(WeaponItemLevel);
	LSCHECK(WeaponBaseData);
	SetWeaponDefinitionStats();
	WeaponAbilityComponent->EnhanceWeaponStat(this);
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