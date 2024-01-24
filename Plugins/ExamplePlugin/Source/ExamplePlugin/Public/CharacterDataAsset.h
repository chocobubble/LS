// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Protocol.pb.h"

#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, hidecategories = (Object))
class EXAMPLEPLUGIN_API UCharacterDataAsset : public UObject
{
	GENERATED_BODY()

	friend class AHttpActor;
public:
	 void MakeProto(size_t& OutSize);

	 bool Parse(const uint8*& Buffer, size_t length);
	 bool Parse(void*& Buffer, size_t length);
	 bool Parse(std::string str);

	 bool ParseTest();
	 int32 Test();

	 void SerializeData();
	// void SynchronizeCharacterData(const FServerSaveData& SaveData);
private:
	 CharacterData data;
	 CharacterData characterData;
	 WeaponSaveData weaponSaveData;
	 FString SerializedCharacterData;


};
