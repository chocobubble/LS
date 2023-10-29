// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSInventoryComponent.generated.h"

// DECLARE_MULTICAST_DELEGATE(FOn)

class ULSWeaponDefinition;
class ULSEquipmentComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULSInventoryComponent();

	void SetEquipmentComponent(ULSEquipmentComponent* EquipmentComponent)
	{
		EquipmentManager = EquipmentComponent;
	}

	void SetDefaultWeapon();
	bool IsInventoryFull()
	{
		return MaxInventoryCapacity == CurrentInventoryCapacity;
	}
	int32 GetEmptyIndex();
	// later, 
	void AddWeaponToInventory(TObjectPtr<ULSWeaponDefinition> WeaponDefinition);
	void EquipItem(int32 ItemIndex);
	TObjectPtr<ULSWeaponDefinition> GetWeaponDefinitionInList(int32 Index) const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Inventory)
	TArray<TObjectPtr<ULSWeaponDefinition>> WeaponList;

	UPROPERTY(EditAnywhere, Category = Equipment)
	ULSEquipmentComponent* EquipmentManager;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	int32 MaxInventoryCapacity = 60;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	int32 CurrentInventoryCapacity = 0;

};
