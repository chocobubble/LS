// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterData.pb.h"

#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, hidecategories = (Object))
class EXAMPLEPLUGIN_API UCharacterDataAsset : public UObject
{
	GENERATED_BODY()

public:
	 void MakeProto(size_t& OutSize);

	 bool Parse(const uint8*& Buffer, size_t length);
	 bool Parse(void*& Buffer, size_t length);
	 bool Parse(std::string str);

	 bool ParseTest();
	 int32 Test();

public:
	 CharacterData data;
	
};
