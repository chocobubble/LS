// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSEquipmentComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEquipmentChangedDelegate);

class ALSWeapon;
class ALSWeaponInstance;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULSEquipmentComponent();

	void EquipWeapon(ALSWeapon* Weapon);
	void EquipWeapon(ALSWeapon* Weapon, int8 index);

	ALSWeapon* GetCurrentWeapon();
	ALSWeapon* GetWeapon(int32 Index) const;


	////////

	void EquipWeapon(ALSWeaponInstance* Weapon);
	void EquipWeapon(ALSWeaponInstance* Weapon, int8 index);

	ALSWeaponInstance* GetCurrentWeaponInstance();
	ALSWeaponInstance* GetWeaponInstance(int32 Index);

	void SetCurrentWeaponIndex(int32 Index);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
/*
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
*/
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	int32 CurrentWeaponIndex = 0;
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	ALSWeapon* CurrentWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	TArray<ALSWeapon*> WeaponList;

	UPROPERTY(EditInstanceOnly, Category = Equipment)
	TSubclassOf<ALSWeapon> WeaponClass;

///////////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	ALSWeaponInstance* CurrentWeaponInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	TArray<ALSWeaponInstance*> WeaponInstanceList;

	UPROPERTY(EditInstanceOnly, Category = Equipment)
	TSubclassOf<ALSWeaponInstance> WeaponInstanceClass;


	FOnEquipmentChangedDelegate OnEquipmentChanged;		
};
