// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "Components/ActorComponent.h"

#include "LSResourceManageComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnResourceChangedDelegate);

/*
USTRUCT(Atomic, BlueprintType)
struct FLSResourceData
{
	GENERATED_BODY()

	FLSResourceData() : MaxRifleAmmo(1000), MaxPistolAmmo(0), MaxShotgunAmmo(0),
		CurrentRifleAmmo(1000), CurrentPistolAmmo(0), CurrentShotgunAmmo(0)
	
	{LSLOG(Warning, TEXT("FLSResourceData constructor"));}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource)
	int32 Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource)
	int32 MaxRifleAmmo = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource)
	int32 MaxPistolAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource)
	int32 MaxShotgunAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource)
	int32 CurrentRifleAmmo = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource)
	int32 CurrentPistolAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource)
	int32 CurrentShotgunAmmo = 0;
};
*/

enum class EAmmoType
{
	RIFLE,
	PISTOL,
	SHOTGUN
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOTERSHOOTER_API ULSResourceManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULSResourceManageComponent();
	void SetCurrentAmmo(EAmmoType AmmoType, int32 Amount);
	int32 GetCurrentAmmo(EAmmoType AmmoType) const;
	int32 GetMaxAmmo(EAmmoType AmmoType) const;
	
	void SetGoldAmount(int32 Amount) ;
	
	void ConsumeAmmo(EAmmoType AmmoType, int32 Amount);

	int32 GetGoldAmount() const
	{
		return GoldAmount;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void NoFunc() {};

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 MaxRifleAmmo = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 MaxPistolAmmo = 250;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 MaxShotgunAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 CurrentRifleAmmo = 250;  // default
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 CurrentPistolAmmo = 125; // default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 CurrentShotgunAmmo = 50; // default

/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 RoundsRemaining = 0;
*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Resource, meta = (AllowPrivateAccess = "true"))
	int32 GoldAmount = 0;

public:	
	// Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// TSharedPtr<FLSResourceData> ResourceData = MakeShareable(new FLSResourceData());
	FOnResourceChangedDelegate OnResourceChanged;
		
};
