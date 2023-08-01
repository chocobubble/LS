// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LSInventoryComponent.generated.h"

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
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	TArray<ULSWeaponDefinition*> WeaponList;

	UPROPERTY(VisibleAnywhere, Category = Equipment)
	ULSEquipmentComponent* EquipmentManager;

};
