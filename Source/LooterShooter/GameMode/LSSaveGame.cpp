// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSaveGame.h"

ULSSaveGame::ULSSaveGame()
{
    PlayerName = TEXT("Guest");
	if (AmmoMap.IsEmpty())
	{
		AmmoMap.Add(EAmmoType::EAT_Rifle, 100);
	}

	if (SavedWeapons.Num() == 0)
	{
		SavedWeapons.Add(FirstWeaponData);
	}
}

TMap<EAmmoType, int32>& ULSSaveGame::GetSavedAmmoMap()
{
	if (AmmoMap.IsEmpty())
	{
		AmmoMap.Add(EAmmoType::EAT_Rifle, 100);
	}
	AmmoMap[EAmmoType::EAT_Rifle] = RifleAmmo;
	return AmmoMap;
}

void ULSSaveGame::SaveAmmoMap(TMap<EAmmoType, int32>& CurrentAmmoMap)
{
	AmmoMap = CurrentAmmoMap;
	RifleAmmo = AmmoMap[EAmmoType::EAT_Rifle];
	LSLOG(Warning, TEXT("%d rifle ammo saved"), RifleAmmo);
}

void ULSSaveGame::SaveOwnedWeapons(TArray<FWeaponSaveData>& CurrentOwnedWeapons)
{
	if (SavedWeapons.IsEmpty() || CurrentOwnedWeapons.IsEmpty())
	{
		LSLOG(Warning, TEXT("SavedOwnWeaponS nullptr"));
		return;
	}
	//SavedWeapons[0]->SetWeaponLevel(CurrentOwnedWeapons[0]->GetWeaponLevel());
	SavedWeapons[0].SetEnhancementLevel(CurrentOwnedWeapons[0].GetEnhancementLevel());
	LSLOG(Warning, TEXT("%d Owndweapon level, %d owned weapon enhancement"), FirstWeaponData.WeaponLevel, FirstWeaponData.EnhancementLevel);
}
