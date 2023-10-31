// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSInventoryComponent.generated.h"

class ULSWeaponDefinition;
class ULSEquipmentComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULSInventoryComponent();

	// 게임 첫 시작 시 기본 무기 생성
	void SetDefaultWeapon();
	
	int32 GetEmptyIndex();

	void AddWeaponToInventory(TObjectPtr<ULSWeaponDefinition> WeaponDefinition);

	void EquipItem(int32 ItemIndex);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<ULSWeaponDefinition>> WeaponList;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	ULSEquipmentComponent* EquipmentManager;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 MaxInventoryCapacity = 60;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 CurrentInventoryCapacity = 0;

public:
	void SetEquipmentComponent(ULSEquipmentComponent* EquipmentComponent)
	{
		EquipmentManager = EquipmentComponent;
	}

	bool IsInventoryFull()
	{
		return MaxInventoryCapacity == CurrentInventoryCapacity;
	}

	TObjectPtr<ULSWeaponDefinition> GetWeaponDefinitionInList(int32 Index) const
	{
		return WeaponList[Index];
	}

};
