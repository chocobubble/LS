// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponAbilityComponent.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"

void UWeaponAbility::SetAbilityStat(float Stat)
{
	AbilityStat = Stat;
}

void UBulletDamageAbility::ApplyAbility(ULSWeaponDefinition* WeaponDefinition) 
{
	if (WeaponDefinition == nullptr)
	{
		return;
	}
	WeaponDefinition->SetBulletDamage(WeaponDefinition->GetBulletDamage() + WeaponDefinition->GetBulletDamage() * AbilityStat);
}

ULSWeaponAbilityComponent::ULSWeaponAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULSWeaponAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	/** 테스트 용도 */
	UBulletDamageAbility* DMGAbilityPtr = NewObject<UBulletDamageAbility>();
	if (DMGAbilityPtr)
	{
		DMGAbilityPtr->SetAbilityStat(1.1f);
		AbilityList.Add(DMGAbilityPtr);
	}
	//////////////
}

void ULSWeaponAbilityComponent::EnhanceWeaponStat(ULSWeaponDefinition* WeaponDefinition)
{
	if (WeaponDefinition == nullptr)
	{
		return;
	}
	for (UWeaponAbility* Ability : AbilityList)
	{
		if (Ability) 
		{
			Ability->ApplyAbility(WeaponDefinition);
		}
	}
}

void ULSWeaponAbilityComponent::AttachWeaponAbility(UWeaponAbility* WeaponAbility)
{
	if (WeaponAbility) 
	{
		AbilityList.Add(WeaponAbility);
	}
}


