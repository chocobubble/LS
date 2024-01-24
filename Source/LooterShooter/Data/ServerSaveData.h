#pragma once

#include "LooterShooter/Types/WeaponType.h"

#include "ServerSaveData.generated.h"
/**
 *
 */
USTRUCT()
struct FServerSaveData
{
	GENERATED_BODY()
	int32 CharacterLevel;

	int32 CharacterExp;

	FString PlayerName;

	int32 Gold;

	int32 RifleAmmo;

	EWeaponType WeaponType = EWeaponType::EWT_Rifle;

	int32 WeaponLevel;

	int32 EnhancementLevel;
};
