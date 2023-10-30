// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSaveGame.h"

ULSSaveGame::ULSSaveGame()
{
    Level = 1;
    Exp = 0;
    PlayerName = TEXT("Guest");
	Gold = 1000;
	AmmoMap.Add(EAmmoType::RIFLE, 100);
	WeaponLevel = 1
	WeaponEnhancementLevel = 0;
}