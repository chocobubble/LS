#include "Engine/DataTable.h"

USTRUCT(BlueprintType)
struct FLSWeaponBaseData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 MagazineCapacity = 20;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float FireRate = 500.0f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MovementSpeed = 510.0f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float BulletDamage = 50.0f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float CriticalHitChance = 0.03f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float CriticalHitMultiplier = 1.5f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float DamageReduceDistance = 1000.0f;

	UPROPERTY(VisibleAnywhere,  Category = "Weapon")
	float ReloadTime = 2.0f;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 BulletsPerCatridge = 1;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float MaxRange = 10000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	float MaxSpreadAngle = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = Attack)
	float MinSpreadAngle = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = Attack)
	float HeatPerShot = 0.1f;
};
