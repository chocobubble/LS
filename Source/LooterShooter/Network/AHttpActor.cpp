// Fill out your copyright notice in the Description page of Project Settings.


#include "AHttpActor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Templates/SharedPointer.h"
#include "ExamplePlugin.h"
#include "CharacterDataAsset.h"
#include "CharacterData.pb.h"
//proto
//#include "CharacterData.pb.h"

// Sets default values
AAHttpActor::AAHttpActor()
{
	PrimaryActorTick.bCanEverTick = false;


}

void AAHttpActor::PutData()
{
}

void AAHttpActor::GetData()
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest = HttpModule.CreateRequest();
	GetRequest->OnProcessRequestComplete().BindUObject(this, &AAHttpActor::OnResponseReceived);
	GetRequest->SetVerb(TEXT("GET"));
	GetRequest->SetURL(TEXT("https://localhost:7058/Proto/ProtoTest1"));
	GetRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	GetRequest->SetHeader("Content-Type", TEXT("application/json"));
	GetRequest->ProcessRequest();

}

void AAHttpActor::GetData2()
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest = HttpModule.CreateRequest();
	GetRequest->OnProcessRequestComplete().BindUObject(this, &AAHttpActor::OnResponseReceived);
	GetRequest->SetVerb(TEXT("GET"));
	GetRequest->SetURL(TEXT("https://localhost:7058/Proto/ProtoTest2"));
	GetRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	GetRequest->SetHeader("Content-Type", TEXT("application/json"));
	GetRequest->ProcessRequest();
	LSLOG(Warning, TEXT("Get Data 2"));
}

void AAHttpActor::SaveData(CharacterData& CurrentData)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest = HttpModule.CreateRequest();
	GetRequest->OnProcessRequestComplete().BindUObject(this, &AAHttpActor::OnSaveResponseReceived);
	GetRequest->SetVerb(TEXT("POST"));
	GetRequest->SetURL(TEXT("https://localhost:7058/Data/SaveCharacterData?userName=1"));
	//GetRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	GetRequest->SetHeader("Content-Type", TEXT("application/json"));
	GetRequest->SetHeader(TEXT("accept"), TEXT("text/plain"));

	std::string str = "\"";
	str += base64_encode(CurrentData.SerializeAsString()) + "\"";
	FString temp = *FString(str.c_str());
	LSLOG(Warning, TEXT("%s"), *temp);
	GetRequest->SetContentAsString(temp);

	GetRequest->ProcessRequest();
	LSLOG(Warning, TEXT("Save Data"));
}

const CharacterData& AAHttpActor::LoadData()
{
	GetData2();

	return asset->data;
}

void AAHttpActor::OnResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Response->GetContentAsString());

	FString ResponseString = Response->GetContentAsString();
	std::string str = TCHAR_TO_ANSI(*ResponseString);
	std::string str2 = str.substr(1, str.size() - 2);
	std::string decodedString = base64_decode(str2);
	asset->Parse(decodedString);
	LSLOG(Warning, TEXT("%d"), asset->data.level());
}

void AAHttpActor::OnSaveResponseReceived(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Response->GetContentAsString());
}

void AAHttpActor::BeginPlay()
{
	Super::BeginPlay();

	asset = NewObject<UCharacterDataAsset>(this);/*
	LSLOG(Warning, TEXT("Get Data Start"));
	GetData();
	LSLOG(Warning, TEXT("Get Data End"));*/

	CharacterData characterData;
	WeaponSaveData weaponSaveData2;
	weaponSaveData2.set_weapontype(WeaponSaveData_WeaponType_EWT_RIFLE);
	weaponSaveData2.set_weaponlevel(2);
	weaponSaveData2.set_weaponenhancementlevel(3);
	characterData.set_level(3);
	characterData.set_exp(5);
	characterData.set_playername("player");
	characterData.set_gold(100);
	characterData.set_allocated_weaponsavedata(&weaponSaveData2);
	/*t.set_weaponenhancementlevel(3);
	t.set_weaponlevel(2);
	t.set_weapontype(WeaponSaveData_WeaponType_EWT_RIFLE);*/
	characterData.set_rifleammo(1000);



	characterData.unsafe_arena_release_weaponsavedata();

	//cout << str << endl;
	google::protobuf::ShutdownProtobufLibrary();

	SaveData(characterData);
}

void AAHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


