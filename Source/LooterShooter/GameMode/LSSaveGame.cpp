// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSaveGame.h"

ULSSaveGame::ULSSaveGame()
{
    PlayerName = TEXT("Guest");
	AmmoMap.Add(EAmmoType::RIFLE, 100);
}