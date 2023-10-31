// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSEquipmentComponent.generated.h"

class ALSWeapon;
class ALSWeaponInstance;

DECLARE_MULTICAST_DELEGATE(FOnEquipmentChangedDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoundsRemainingChangedDelegate, int32);

/**
 * 캐릭터에 장착된 장비 아이템을 관리하는 컴포넌트
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULSEquipmentComponent();

	void EquipWeapon(ALSWeaponInstance* Weapon);

	void EquipWeapon(ALSWeaponInstance* Weapon, int8 index);

	/** 사격 시 총알 수 감소 */
	int32 DecreaseRoundsRemaining();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	int32 CurrentWeaponIndex = 0;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	ALSWeaponInstance* CurrentWeaponInstance;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TArray<ALSWeaponInstance*> WeaponInstanceList;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TSubclassOf<ALSWeaponInstance> WeaponInstanceClass;

public:
	ALSWeaponInstance* GetCurrentWeaponInstance()
	{
		return GetWeaponInstance(CurrentWeaponIndex);
	}

	ALSWeaponInstance* GetWeaponInstance(int32 Index);

	void SetCurrentWeaponIndex(int32 Index)
	{
		CurrentWeaponIndex = Index;
	}

	int32 GetCurrentWeaponIndex() const
	{
		return CurrentWeaponIndex;
	}

	void SetRoundsRemaining(int32 NewRoundsRemaining);

	int32 GetRoundsRemaining() const;


	FOnEquipmentChangedDelegate OnEquipmentChanged;		

	FOnRoundsRemainingChangedDelegate OnRoundsRemainingChanged;
};
