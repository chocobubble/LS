// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Templates/SharedPointer.h"
#include "GameFramework/Actor.h"
#include "CharacterData.pb.h"
#include "base64.h"
#include "AHttpActor.generated.h"

class IHttpRequest;
class IHttpResponse;
class UCharacterDataAsset;

UCLASS()
class LOOTERSHOOTER_API AAHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAHttpActor();

	void PutData();
	void GetData();
	void GetData2();

	void SaveData(CharacterData& CurrentData);
	const CharacterData& LoadData();

	void OnResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);
	void OnSaveResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);


protected:
	virtual void BeginPlay() override;	
	virtual void Tick(float DeltaTime) override;

private:
	UCharacterDataAsset* asset;


};
