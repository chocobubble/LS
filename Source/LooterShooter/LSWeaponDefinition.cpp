// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponDefinition.h"
#include "LSEquipmentComponent.h"
#include "LSWeaponInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LSWeaponAbilityComponent.h"
// #include "LSCharacter.h"


ULSWeaponDefinition::ULSWeaponDefinition()
{
    WeaponAbilityComponent = CreateDefaultSubobject<ULSWeaponAbilityComponent>(TEXT("WEAPONABILITY"));
	
}

// 우선은 instantiate하고 stat 설정만..
ALSWeaponInstance* ULSWeaponDefinition::InstantiateWeapon()
{
    // 파라미터에 문제 있을 수 있음 
	ALSWeaponInstance* NewWeapon = GetWorld()->SpawnActor<ALSWeaponInstance>( FVector::ZeroVector, FRotator::ZeroRotator);
	NewWeapon->SetActorHiddenInGame(true);
    // 소유자 어떻게 설정되는지 확인해보기
	// NewWeapon->SetOwner(GetOwner());
	//GetOwner<LSCharacter>()->EquipmentManager->WeaponInstanceList.Emplace(NewWeapon);
    NewWeapon->SetWeaponData(this);//(EWeaponType::RIFLE, 1);
    return NewWeapon;
}


void ULSWeaponDefinition::SetWeaponDefinitionData(EWeaponType WeaponType, int32 ItemLevel)
{
	this->GunType = WeaponType;
	WeaponItemLevel = ItemLevel;
	
	ULSGameInstance* LSGameInstance = Cast<ULSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	// later switch by weapon type
	WeaponBaseData = LSGameInstance->GetLSWeaponData(WeaponItemLevel);
	LSCHECK(WeaponBaseData);
	SetWeaponStats();
	WeaponAbilityComponent->EnhanceWeaponStat(this);
	// RoundsRemaining = WeaponBaseData->MagazineCapacity;
}

void ULSWeaponDefinition::SetWeaponDefinitionStats()
{
	// bIsSet 추가?
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