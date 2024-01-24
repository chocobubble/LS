// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "Templates/SharedPointer.h"
#include "GameFramework/Actor.h"
#include "Protocol.pb.h"
#include "base64.h"
#include "LooterShooter/Data/ServerSaveData.h"
#include "HttpActor.generated.h"

class IHttpRequest;
class IHttpResponse;
class UCharacterDataAsset;
class UHttpCommandAsset;
class ALSPlayerState;
struct FServerSaveData;

UCLASS()
class LOOTERSHOOTER_API AHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHttpActor();

	void Init(ALSPlayerState* LSPlayerState);

	void PutData();
	void GetData();
	void GetData2();
	void SynchronizeCharacterData(const FServerSaveData& SaveData);

	
	void LoadData();
	void OnLoadResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);


	void OnResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);

	void SaveData();
	void OnSaveResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);

	void RequestLogin();//(/LoginRequest UserLoginRequest);
	void OnLoginResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);

	void RequestCreateAccount(const FString& Str);
	void OnCreateAccountResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful);


protected:
	virtual void BeginPlay() override;	
	virtual void Tick(float DeltaTime) override;

private:
	UCharacterDataAsset* asset;

	UPROPERTY(VisibleAnywhere, Category = "Network")
	UHttpCommandAsset* HttpCommandAsset;

	UPROPERTY(VisibleAnywhere, Category = "Network")
	bool IsHttpRequestEnd = true;

	UPROPERTY(VisibleAnywhere, Category = "Network")
	FString SessionId = "Default";

	UPROPERTY(VisibleAnywhere, Category = "State")
	ALSPlayerState* PlayerState;

public:
	const FString GetSessionId()
	{
		return SessionId;
	}

	void SetSessionId(const FString& NewSessionId)
	{
		SessionId = NewSessionId;
	}
};
