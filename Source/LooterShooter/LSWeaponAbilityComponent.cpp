// Fill out your copyright notice in the Description page of Project Settings.


#include "LSWeaponAbilityComponent.h"
#include "LSWeaponInstance.h"

void UWeaponAbility::SetAbilityStat(float Stat)
{
	AbilityStat = Stat;
}

void UBulletDamageAbility::ApplyAbility(ALSWeaponInstance* WeaponInstance) 
{
	LSLOG(Warning, TEXT("Bullet Damage before enhanced : %f"), WeaponInstance->GetBulletDamage());
	WeaponInstance->SetBulletDamage(WeaponInstance->GetBulletDamage() + WeaponInstance->GetBulletDamage() * AbilityStat);
	LSLOG(Warning, TEXT("Bullet Damage after enhanced : %f"), WeaponInstance->GetBulletDamage());
}

/*
FString UBulletDamageAbility::GetAbilityText() 
{
	FString AbilityText = FString(TEXT("Muliplies Bullet Damage : +%f"), AbilityStat);
	return AbilityText;
}
*/



// Sets default values for this component's properties
ULSWeaponAbilityComponent::ULSWeaponAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	// FBulletDamageAbility DMGAbility(FString("AbilityName"), 1.1f);
}


// Called when the game starts
void ULSWeaponAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	UBulletDamageAbility* DMGAbilityPtr = NewObject<UBulletDamageAbility>();
	DMGAbilityPtr->SetAbilityStat(1.1f);
	//UWeaponAbility* DMGAbilityPtr = &DMGAbility;
	AbilityList.Add(DMGAbilityPtr);
	// ...
	
}

void ULSWeaponAbilityComponent::EnhanceWeaponStat(ALSWeaponInstance* WeaponInstance)
{
	// ALSWeaponInstance* WeaponInstance = GetOwner();
	for(UWeaponAbility* Ability : AbilityList)
	{
		Ability->ApplyAbility(WeaponInstance);
	}
}

/*
// Called every frame
void ULSWeaponAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

