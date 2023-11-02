// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Components/ActorComponent.h"
#include "LooterShooter/Types/AmmoType.h"
#include "LSResourceManageComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnResourceChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSResourceManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULSResourceManageComponent();

	void ConsumeAmmo(EAmmoType AmmoType, int32 Amount);

	UFUNCTION()
	void TestFunc();

	void UpdateResources();

	FOnResourceChangedDelegate OnResourceChanged;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 MaxRifleAmmo = 500;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 MaxPistolAmmo = 250;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 MaxShotgunAmmo = 100;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 CurrentRifleAmmo = 250; 
 
	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 CurrentPistolAmmo = 125; 

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 CurrentShotgunAmmo = 50; 

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 GoldAmount = 200;

public:	
	void SetCurrentAmmo(EAmmoType AmmoType, int32 Amount);

	void SetCurrentAmmo(const TMap<EAmmoType, int32>& CurrentAmmoMap);

	int32 GetCurrentAmmo(EAmmoType AmmoType) const;
	
	int32 GetMaxAmmo(EAmmoType AmmoType) const;
	
	void SetGoldAmount(int32 Amount);
		
	int32 GetGoldAmount() const
	{
		return GoldAmount;
	}
};
