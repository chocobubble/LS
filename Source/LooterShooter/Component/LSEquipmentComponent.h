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

	ALSWeaponInstance* GetCurrentWeaponInstance();
	ALSWeaponInstance* GetWeaponInstance(int32 Index);

	void SetCurrentWeaponIndex(int32 Index);
	int32 GetCurrentWeaponIndex() const;
	void SetRoundsRemaining(int32 NewRoundsRemaining);
	int32 GetRoundsRemaining() const;

	void DecreaseRoundsRemaining();
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	int32 CurrentWeaponIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	ALSWeaponInstance* CurrentWeaponInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	TArray<ALSWeaponInstance*> WeaponInstanceList;
private:
	UPROPERTY(VisibleAnywhere, Category = Equipment)
	TSubclassOf<ALSWeaponInstance> WeaponInstanceClass;

public:
	FOnEquipmentChangedDelegate OnEquipmentChanged;		
	FOnRoundsRemainingChangedDelegate OnRoundsRemainingChanged;
};
