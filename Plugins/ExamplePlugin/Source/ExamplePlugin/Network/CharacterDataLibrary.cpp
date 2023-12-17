// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDataLibrary.h"

TArray<FString> UCharacterDataLibrary::KennelDoggoList(UCharacterDataAsset* dataAsset)
{
	return TArray<FString>();
}

int32 UCharacterDataLibrary::CharacterLevel(UCharacterDataAsset* dataAsset)
{
	return dataAsset->Test();
}
