// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpActor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Templates/SharedPointer.h"
#include "ExamplePlugin.h"
#include "CharacterDataAsset.h"
#include "Protocol.pb.h"
#include "HttpCommandAsset.h"
#include "LooterShooter/Character/LSPlayerState.h"

AHttpActor::AHttpActor()
{
	PrimaryActorTick.bCanEverTick = false;


}

void AHttpActor::Init(ALSPlayerState* LSPlayerState)
{
	PlayerState = LSPlayerState;
}

void AHttpActor::PutData()
{
}

void AHttpActor::GetData()
{
}

void AHttpActor::GetData2()
{
}

void AHttpActor::SynchronizeCharacterData(const FServerSaveData& SaveData)
{
	if (!asset)
	{
		return;
	}

	HttpCommandAsset->UserCharacterData.set_level(SaveData.CharacterLevel);
	HttpCommandAsset->UserCharacterData.set_exp(SaveData.CharacterExp);
	HttpCommandAsset->UserCharacterData.clear_playername();
	HttpCommandAsset->UserCharacterData.set_playername(TCHAR_TO_ANSI(*SaveData.PlayerName));
	HttpCommandAsset->UserCharacterData.set_gold(100);
	HttpCommandAsset->UserCharacterData.set_rifleammo(100);
	HttpCommandAsset->UserWeaponSaveData.set_weapontype(EWT_RIFLE);
	HttpCommandAsset->UserWeaponSaveData.set_weaponlevel(SaveData.WeaponLevel);
	HttpCommandAsset->UserWeaponSaveData.set_weaponenhancementlevel(SaveData.EnhancementLevel);
	HttpCommandAsset->LinkData();
}

void AHttpActor::LoadData()
{
	//if (!IsHttpRequestEnd)
	//{
	//	return;
	//}
	//IsHttpRequestEnd = false;
	//FHttpModule& HttpModule = FHttpModule::Get();
	//TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest = HttpModule.CreateRequest();
	//GetRequest->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnLoadResponseReceived);
	//GetRequest->SetVerb(TEXT("POST"));
	//GetRequest->SetURL(TEXT("https://localhost:7058/Data/LoadCharacterData"));
	//GetRequest->SetHeader(TEXT("accept"), TEXT("application/x-protobuf"));
	//GetRequest->SetHeader("Content-Type", TEXT("application/x-protobuf"));

	//	
	//HttpCommandAsset->UserCharacterDataLoadRequest.set_sessionid(TCHAR_TO_ANSI(*SessionId));
	//FString Request = HttpCommandAsset->UserCharacterDataLoadRequest.SerializeAsString().c_str();
	//GetRequest->SetContentAsString(Request);

	//LSLOG(Warning, TEXT("Login Request : %s"), *Request);
	//
	//GetRequest->ProcessRequest();
}

void AHttpActor::OnLoadResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful)
{
	//LSLOG(Warning, TEXT("Load Response Received"));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *Response->GetContentAsString());
	//TArray<uint8> buffer = Response->GetContent();
	//std::string StringFromByteArray(reinterpret_cast<const char*>(buffer.GetData()), buffer.Num());
	//FString ResponseString = Response->GetContentAsString();	

	//if (HttpCommandAsset->CharacterDataLoadResponseParse(StringFromByteArray))
	//{
	//	if (HttpCommandAsset->UserCharacterDataLoadResponse.apireturncode() == Success)
	//	{
	//		if (PlayerState)
	//		{
	//			FServerSaveData SaveData;
	//			SaveData.CharacterLevel = HttpCommandAsset->UserCharacterData.level();
	//			SaveData.CharacterExp = HttpCommandAsset->UserCharacterData.exp();
	//			SaveData.Gold = HttpCommandAsset->UserCharacterData.gold();
	//			SaveData.PlayerName = *FString(HttpCommandAsset->UserCharacterData.playername().c_str());
	//			
	//			SaveData.WeaponType = EWeaponType((int)HttpCommandAsset->UserWeaponSaveData.weapontype());
	//			SaveData.WeaponLevel = HttpCommandAsset->UserWeaponSaveData.weaponlevel();
	//			SaveData.EnhancementLevel = HttpCommandAsset->UserWeaponSaveData.weaponenhancementlevel();

	//			PlayerState->LoadDataFromServer(SaveData);
	//		}
	//		else
	//		{
	//			LSLOG(Error, TEXT("Player State is null"));
	//		}
	//	}
	//	else
	//	{
	//		LSLOG(Error, TEXT("Failt to Load"));
	//	}
	//}


	//IsHttpRequestEnd = true;
}

void AHttpActor::OnResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Response->GetContentAsString());
}


void AHttpActor::SaveData()
{
	//if (!IsHttpRequestEnd)
	//{
	//	return;
	//}
	//IsHttpRequestEnd = false;

	//FHttpModule& HttpModule = FHttpModule::Get();
	//TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest = HttpModule.CreateRequest();
	//GetRequest->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnSaveResponseReceived);
	//GetRequest->SetVerb(TEXT("POST"));
	//GetRequest->SetURL(TEXT("https://localhost:7058/Data/SaveCharacterData"));
	//GetRequest->SetHeader(TEXT("accept"), TEXT("application/x-protobuf"));
	//GetRequest->SetHeader("Content-Type", TEXT("application/x-protobuf"));



	//HttpCommandAsset->ResetCharacterDataSaveRequest();
	//HttpCommandAsset->UserCharacterDataSaveRequest.set_sessionid(TCHAR_TO_ANSI(*SessionId));
	//HttpCommandAsset->LinkSaveData();
	//FString Request(HttpCommandAsset->UserCharacterDataSaveRequest.SerializeAsString().c_str());
	//GetRequest->SetContentAsString(Request);

	//GetRequest->ProcessRequest();
	//LSLOG(Warning, TEXT("Save Data : %s"), *Request);
}


void AHttpActor::OnSaveResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful)
{
	//LSLOG(Warning, TEXT("Save Response Received"));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *Response->GetContentAsString());


	//FString ResponseString = Response->GetContentAsString();
	//std::string str = TCHAR_TO_ANSI(*ResponseString);

	//if (HttpCommandAsset->CharacterDataSaveResponseParse(str))
	//{
	//	if (HttpCommandAsset->UserCharacterDataSaveResponse.apireturncode() == Success)
	//	{
	//		LSLOG(Error, TEXT("Success to Save"));
	//	}
	//	else
	//	{
	//		LSLOG(Error, TEXT("Failt to Save"));
	//	}
	//}

	//IsHttpRequestEnd = true;
}

void AHttpActor::RequestLogin()
{
	if (!IsHttpRequestEnd)
	{
		return;
	}
	IsHttpRequestEnd = false;
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest = HttpModule.CreateRequest();
	GetRequest->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnLoginResponseReceived);
	GetRequest->SetVerb(TEXT("POST"));
	GetRequest->SetURL(TEXT("https://localhost:7058/Session/Login"));
	GetRequest->SetHeader(TEXT("accept"), TEXT("application/x-protobuf"));
	GetRequest->SetHeader("Content-Type", TEXT("application/x-protobuf"));

	HttpCommandAsset->ResetLoginRequest();
	HttpCommandAsset->UserLoginRequest.set_id("Id1");
	HttpCommandAsset->UserLoginRequest.set_password("Pwd1");
	HttpCommandAsset->Request.set_sessionid("DefaultSessionId");
	HttpCommandAsset->LinkLoginRequest();

	FString Request = HttpCommandAsset->Request.SerializeAsString().c_str();
	GetRequest->SetContentAsString(Request);
	GetRequest->ProcessRequest();
	LSLOG(Warning, TEXT("%s"), *Request);

	HttpCommandAsset->ResetLoginRequest();
}

void AHttpActor::OnLoginResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Response->GetContentAsString());

	FString ResponseString = Response->GetContentAsString();
	std::string str = TCHAR_TO_ANSI(*ResponseString);

	if (PlayerState)
	{
		PlayerState->InitPlayerData();
	}

	if (HttpCommandAsset->LoginResponseParse(str))
	{
		FString LogString = *FString(HttpCommandAsset->UserLoginResponse.sessionid().c_str());
		LSLOG(Warning, TEXT("%s"), *LogString);
		SessionId = LogString;

		if (PlayerState)
		{
			PlayerState->SaveSessionId();
		}
		else
		{
			LSLOG(Error, TEXT("Plyaer State null"));
		}
	}

	HttpCommandAsset->ResetLoginResponse();

	IsHttpRequestEnd = true;
}

void AHttpActor::RequestCreateAccount(const FString& Str)
{
	if (!IsHttpRequestEnd)
	{
		return;
	}
	IsHttpRequestEnd = false;
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest = HttpModule.CreateRequest();
	GetRequest->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnCreateAccountResponseReceived);
	GetRequest->SetVerb(TEXT("POST"));
	GetRequest->SetURL(TEXT("https://localhost:7058/AccountControllerSql/CreateAccountSql"));
	GetRequest->SetHeader("Content-Type", TEXT("application/x-protobuf"));
	GetRequest->SetHeader(TEXT("accept"), TEXT("application/x-protobuf"));

	HttpCommandAsset->Request.set_sessionid("DefaultSesId");
	HttpCommandAsset->UserAccountCreateRequest.set_id("Id5");
	HttpCommandAsset->UserAccountCreateRequest.set_password("Pwd5");
	HttpCommandAsset->LinkCreateAccountRequest();

	std::string str = HttpCommandAsset->Request.SerializeAsString();
	
	FString temp = *FString(str.c_str());
	LSLOG(Warning, TEXT("%s"), *temp);
	GetRequest->SetContentAsString(temp);

	GetRequest->ProcessRequest();

	// HttpCommandAsset->Request.release_createaccountrequest();
	HttpCommandAsset->ReleaseCreateAccountRequest();
}

void AHttpActor::OnCreateAccountResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful)
{
	LSLOG(Warning, TEXT("Create Account Response Received"));
	UE_LOG(LogTemp, Log, TEXT("%s"), *Response->GetContentAsString());

	FString ResponseString = Response->GetContentAsString();
	std::string str = TCHAR_TO_ANSI(*ResponseString);

	//HttpCommandAsset->CreateAccountResponseParse(str);
	//if (HttpCommandAsset->UserAccountCreateResponse.apireturncode() == Success)
	//HttpCommandAsset->ResponseParse(str);
	HttpCommandAsset->CreateAccountResponseParse(str);
	if (HttpCommandAsset->Response.apireturncode() == Success)
	{
		LSLOG(Warning, TEXT("Success to Create Account"));
	}
	else
	{
		LSLOG(Warning, TEXT("Fail to Create Account"));
	}
	HttpCommandAsset->ReleaseCreateAccountResponse();

	IsHttpRequestEnd = true;
}

void AHttpActor::BeginPlay()
{
	Super::BeginPlay();

	asset = NewObject<UCharacterDataAsset>(this);
	HttpCommandAsset = NewObject<UHttpCommandAsset>(this);
}

void AHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


