// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Protocol.pb.h"

#include "HttpCommandAsset.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEPLUGIN_API UHttpCommandAsset : public UObject
{
	GENERATED_BODY()
	friend class AHttpActor;

public:
	bool LoginRequestParse(const std::string& Str);
	bool LoginResponseParse(const std::string& Str);
	bool CreateAccountResponseParse(const std::string& Str);
	bool CharacterDataLoadResponseParse(const std::string& Str);
	bool CharacterDataSaveResponseParse(const std::string& Str);
	void ResetLoginRequest();
	void ResetLoginResponse();
	void ResetCreateAccountRequest();
	void ResetCreateAccountResponse();
	void ResetCharacterDataSaveRequest();
	void ResetCharacterDataSaveResponse();
	void ResetCharacterDataLoadRequest();
	void ResetCharacterDataLoadResponse();
	void LinkData();
	void LinkSaveData();

	void LinkCreateAccountRequest();
	void LinkCreateAccountResponse();
	void ReleaseCreateAccountRequest();
	void ReleaseCreateAccountResponse();

	void RequestParse(const std::string& Str);
	bool ResponseParse(const std::string& Str);
	void ResetRequest();
	void ResetResponse();


	void LinkLoginRequest();
	void LinkLoginResponse();

private:
	std::string SessionId = "DefaultSessionId";
	CreateAccountRequest UserAccountCreateRequest;
	CreateAccountResponse UserAccountCreateResponse;
	LoginRequest UserLoginRequest;
	LoginResponse UserLoginResponse;
	CharacterDataSaveRequest UserCharacterDataSaveRequest;
	CharacterDataSaveResponse UserCharacterDataSaveResponse;
	CharacterDataLoadRequest UserCharacterDataLoadRequest;
	CharacterDataLoadResponse UserCharacterDataLoadResponse;
	CharacterData UserCharacterData;
	WeaponSaveData UserWeaponSaveData;

	BaseRequest Request;
	BaseResponse Response;
};
