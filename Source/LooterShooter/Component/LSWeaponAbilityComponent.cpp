// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponAbilityComponent.h"
#include "LSWeaponDefinition.h"

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

	/** 테스트 용 */
	UBulletDamageAbility* DMGAbilityPtr = NewObject<UBulletDamageAbility>();
	DMGAbilityPtr->SetAbilityStat(1.1f);
	AbilityList.Add(DMGAbilityPtr);
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
		if (Ability != nullptr) 
		{
			Ability->ApplyAbility(WeaponDefinition);
		}
	}
}

void ULSWeaponAbilityComponent::AttachWeaponAbility(UWeaponAbility* WeaponAbility)
{
	if (WeaponAbility != nullptr) 
	{
		AbilityList.Add(WeaponAbility);
	}
}


