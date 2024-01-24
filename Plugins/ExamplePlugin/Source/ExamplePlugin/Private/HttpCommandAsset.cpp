// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpCommandAsset.h"


bool UHttpCommandAsset::LoginRequestParse(const std::string& Str)
{
    if (UserLoginRequest.ParseFromString(Str))
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing success"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing failed"));
        return false;
    }
}

bool UHttpCommandAsset::LoginResponseParse(const std::string& Str)
{
    //if (UserLoginResponse.ParseFromString(Str))
    Response.Clear();
    if (Response.ParseFromString(Str))
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing success"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing failed"));
        return false;
    }
}

bool UHttpCommandAsset::CreateAccountResponseParse(const std::string& Str)
{
    Response.Clear();
    Response.set_allocated_createaccountresponse(&UserAccountCreateResponse);
    if (Response.ParseFromString(Str))
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing success. Success to Create Account"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing failed"));
        return false;
    }
}

bool UHttpCommandAsset::CharacterDataLoadResponseParse(const std::string& Str)
{
    if (UserCharacterDataLoadResponse.ParseFromString(Str))
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing success. Success to Load Character Data"));
        UserCharacterData = UserCharacterDataLoadResponse.characterdata();
        UserWeaponSaveData = UserCharacterDataLoadResponse.characterdata().weaponsavedata();
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing failed"));
        return false;
    }
}

bool UHttpCommandAsset::CharacterDataSaveResponseParse(const std::string& Str)
{
    if (UserCharacterDataSaveResponse.ParseFromString(Str))
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing success. Success to Save Character Data"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing failed"));
        return false;
    }
}

void UHttpCommandAsset::ResetLoginRequest()
{
   
    //UserAccountCreateRequest.Clear();
    //Request.clear_createaccountrequest();
    //Request.Clear();

    Request.Clear();
    UserLoginRequest.Clear();
    auto foo = Request.release_loginrequest();
   
}

void UHttpCommandAsset::ResetLoginResponse()
{
    UserLoginResponse.Clear();
    Response.Clear();
    auto foo = Response.release_loginresponse();
}

void UHttpCommandAsset::ResetCreateAccountRequest()
{
    UserAccountCreateRequest.Clear();
}

void UHttpCommandAsset::ResetCreateAccountResponse()
{
    UserAccountCreateResponse.Clear();
}

void UHttpCommandAsset::ResetCharacterDataSaveRequest()
{
    UserCharacterDataSaveRequest.Clear();
}

void UHttpCommandAsset::ResetCharacterDataSaveResponse()
{
    UserCharacterDataSaveResponse.Clear();
}

void UHttpCommandAsset::ResetCharacterDataLoadRequest()
{
    UserCharacterDataLoadRequest.Clear();
}

void UHttpCommandAsset::ResetCharacterDataLoadResponse()
{
    UserCharacterDataLoadResponse.Clear();
}

void UHttpCommandAsset::LinkData()
{
    UserCharacterData.set_allocated_weaponsavedata(&UserWeaponSaveData);
}

void UHttpCommandAsset::LinkSaveData()
{
    UserCharacterDataSaveRequest.set_allocated_characterdata(&UserCharacterData);
}

void UHttpCommandAsset::LinkCreateAccountRequest()
{
    Request.set_allocated_createaccountrequest(&UserAccountCreateRequest);
}

void UHttpCommandAsset::LinkCreateAccountResponse()
{
    Response.set_allocated_createaccountresponse(&UserAccountCreateResponse);
}

void UHttpCommandAsset::ReleaseCreateAccountRequest()
{
    //Request.release_createaccountrequest();
    UE_LOG(LogTemp, Warning, TEXT("before request id : %s, pwd : %s, sesId : %s"), &UserAccountCreateRequest.id(), &UserAccountCreateRequest.password(), &Request.sessionid());

    //UserAccountCreateRequest.Clear();
    //Request.clear_createaccountrequest();
    //Request.Clear();

    Request.Clear();
    auto foo = Request.release_createaccountrequest();
    UE_LOG(LogTemp, Warning, TEXT("after request id : %s, pwd : %s, sesId : %s"), &Request.createaccountrequest().id(), &UserAccountCreateRequest.password(), &Request.sessionid());

}

void UHttpCommandAsset::ReleaseCreateAccountResponse()
{
    //Response.release_createaccountresponse();
    //Response.clear_createaccountresponse();
    Response.Clear();
    auto foo = Response.release_createaccountresponse();
}

void UHttpCommandAsset::RequestParse(const std::string& Str)
{
}

bool UHttpCommandAsset::ResponseParse(const std::string& Str)
{
    if (Response.ParseFromString(Str))
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing success. Success to Response"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("parsing failed"));
        return false;
    }
}

void UHttpCommandAsset::ResetRequest()
{
    Request.Clear();
}

void UHttpCommandAsset::ResetResponse()
{
    Response.Clear();
}

void UHttpCommandAsset::LinkLoginRequest()
{
    Request.set_allocated_loginrequest(&UserLoginRequest);
}

void UHttpCommandAsset::LinkLoginResponse()
{
    Response.set_allocated_loginresponse(&UserLoginResponse);
}
