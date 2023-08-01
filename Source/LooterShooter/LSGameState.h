// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/DataTable.h"


#include "LSGameState.generated.h"


USTRUCT(BlueprintType)
struct FLSWeaponBaseData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLSWeaponBaseData() : Level(1), MagazineCapacity(20), FireRate(500.0f),
		MovementSpeed(510.0f), BulletDamage(50.0f), CriticalHitChance(0.03f), 
		CriticalHitMultiplier(1.5f), DamageReduceDistance(1000.0f), ReloadTime(2.0f),
		BulletsPerCatridge(1), MaxRange(10000.0f), MaxSpreadAngle(1.0f),
		MinSpreadAngle(0.0f), HeatPerShot(0.1f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MagazineCapacity = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FireRate = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MovementSpeed = 510.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float BulletDamage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float CriticalHitChance = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float CriticalHitMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float DamageReduceDistance = 1000.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Weapon)
	float ReloadTime = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 BulletsPerCatridge = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MaxRange = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float MaxSpreadAngle  = 1.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Attack)
	float MinSpreadAngle = 1.f;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = Attack)
	float HeatPerShot = 0.1f;
};
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ALSGameState();

public:
	int32 GetTotalGameScore() const;
	void AddGameScore();

	void SetGameCleared();
	bool IsGameCleared() const;

	FLSWeaponBaseData* GetLSWeaponData(int32 Level);

private:
	UPROPERTY(Transient)
	int32 TotalGameScore;

	UPROPERTY(Transient)
	bool bGameCleared;

	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UDataTable> LSWeaponDataTable;
};
