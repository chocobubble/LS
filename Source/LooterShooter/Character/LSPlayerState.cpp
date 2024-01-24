// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerState.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/GameMode/LSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
#include "LooterShooter/Component/LSInventoryComponent.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Network/HttpActor.h"
#include "LooterShooter/Data/ServerSaveData.h"

ALSPlayerState::ALSPlayerState()
{
    SaveSlotName = TEXT("Player12345");
	CurrentAmmoMap.Add(EAmmoType::EAT_Rifle, 0);
	//SavedDelegate.BindUObject(this, &ALSPlayerState::SaveDataToServer);
}


void ALSPlayerState::CreateNewSaveData()
{
	LSLOG(Warning, TEXT("Create New Save Game"));
	LSSaveGame = GetMutableDefault<ULSSaveGame>();
	//LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSSaveGame::StaticClass()));
}

void ALSPlayerState::InitPlayerData()
{
	LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	if (LSSaveGame == nullptr)
	{
		CreateNewSaveData();
	}

	SessionId = LSSaveGame->GetSavedSessionId();
	if (HttpActor)
	{
		HttpActor->SetSessionId(SessionId);
	}

    SetPlayerName(LSSaveGame->GetSavedPlayerName());
    SetCharacterLevel(LSSaveGame->GetSavedCharacterLevel());
    CurrentExp = LSSaveGame->GetSavedCharacterExp();
	CurrentGold = LSSaveGame->GetSavedGold();
	CurrentOwnedWeapons = LSSaveGame->GetSavedOwnedWeapons();
	CurrentAmmoMap[EAmmoType::EAT_Rifle] = LSSaveGame->GetSavedAmmoMap()[EAmmoType::EAT_Rifle];

	LSLOG(Warning, TEXT("Init Player Data"));

    SavePlayerData();

	///////
	LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	//SavedDelegate.BindUObject(this, &ALSPlayerState::Test);
}

void ALSPlayerState::SavePlayerData()
{
    ULSSaveGame* NewPlayerData = NewObject<ULSSaveGame>();
    NewPlayerData->SavePlayerName(GetPlayerName());
    NewPlayerData->SaveCharacterLevel(CharacterLevel);
    NewPlayerData->SaveCharacterExp(CurrentExp);
	NewPlayerData->SaveGold(CurrentGold);
	NewPlayerData->SaveOwnedWeapons(CurrentOwnedWeapons);
	NewPlayerData->SaveAmmoMap(CurrentAmmoMap);

	
    /*if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
    {
        LSLOG_S(Error);
    }*/

	LSSaveGame = NewPlayerData;
	if (!UGameplayStatics::SaveGameToSlot(LSSaveGame, SaveSlotName, 0))
	{
		LSLOG_S(Error);
	}

	//UGameplayStatics::AsyncSaveGameToSlot(NewPlayerData, SaveSlotName, 0, SavedDelegate);
	LSLOG(Warning, TEXT("plyaer state weapon level - %d, enhance - %d"), CurrentOwnedWeapons[0].GetWeaponLevel(), CurrentOwnedWeapons[0].GetEnhancementLevel())
		LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
}

void ALSPlayerState::BindWithResourceManager(ULSResourceManageComponent* Target)
{
	if (Target)
	{
		Target->OnResourceChanged.AddUObject(this, &ALSPlayerState::UpdateResourceData);
		ResourceManger = Target;
	}
}

void ALSPlayerState::UpdateResourceData()
{
	if (ResourceManger == nullptr)
	{
		return;
	}
	CurrentGold = ResourceManger->GetGoldAmount();
	// CurrentAmmoMap 업데이트
	// TODO : 다른 타입 총알도 적용
	EAmmoType CurrentAmmoType = EAmmoType::EAT_Rifle;
	CurrentAmmoMap[CurrentAmmoType] = ResourceManger->GetCurrentAmmo(CurrentAmmoType);
	
	LSLOG(Warning, TEXT("Update REsource Data"));
	SavePlayerData();
	if (IsLogin)
	{
		//SaveDataToServer();
	}
}

void ALSPlayerState::UpdateOwnedWeaponData()
{
	SavePlayerData();
}

void ALSPlayerState::SaveDataToServer()//(const FString& SlotName, const int32 UserIndex, bool Value)
{
	LSLOG(Warning, TEXT("save delegate"));
	/*CurrentWeaponData.set_weapontype(EWT_RIFLE);
	CurrentWeaponData.set_weaponlevel(CurrentOwnedWeapons[0]->GetWeaponLevel());
	CurrentWeaponData.set_weaponenhancementlevel(CurrentOwnedWeapons[0]->GetEnhancementLevel());
	CurrentCharacterData.set_level(CharacterLevel);
	CurrentCharacterData.set_exp(CurrentExp);
	CurrentCharacterData.set_playername(TCHAR_TO_ANSI(*GetPlayerName()));
	CurrentCharacterData.set_gold(CurrentGold);
	CurrentCharacterData.set_allocated_weaponsavedata(&CurrentWeaponData);

	CurrentCharacterData.set_rifleammo(CurrentAmmoMap[EAmmoType::EAT_Rifle]);*/

	FServerSaveData SaveData;
	SaveData.CharacterLevel = CharacterLevel;
	SaveData.CharacterExp = CurrentExp;
	SaveData.PlayerName = TCHAR_TO_ANSI(*GetPlayerName());
	SaveData.Gold = CurrentGold;
	SaveData.RifleAmmo = CurrentAmmoMap[EAmmoType::EAT_Rifle];
	SaveData.WeaponType = EWeaponType::EWT_Rifle;
	SaveData.WeaponLevel = CurrentOwnedWeapons[0].GetWeaponLevel();
	SaveData.EnhancementLevel = CurrentOwnedWeapons[0].GetEnhancementLevel();

	LSLOG(Warning, TEXT("CharacterLevel : %d \n Exp : %d \n PlayerName %s \n GOld : %d \n WeaponType : %d \n Weapon Level : %d \n Ammo : %d"),
		SaveData.CharacterLevel, SaveData.CharacterExp, *SaveData.PlayerName, SaveData.Gold, SaveData.WeaponType, SaveData.WeaponLevel,
		SaveData.EnhancementLevel, SaveData.RifleAmmo);

	if (HttpActor)
	{
		HttpActor->SetSessionId(SessionId);
		HttpActor->SynchronizeCharacterData(SaveData);
		HttpActor->SaveData();
		// LSLOG(Warning, TEXT(" 서버에 데이터를 저장하는 데 성공했습니다. "));
	}
}

void ALSPlayerState::DataLoadRequestToServer()
{
	if (HttpActor)
	{
		HttpActor->SetSessionId(SessionId);
		HttpActor->LoadData();
	}
}

void ALSPlayerState::LoadDataFromServer(const FServerSaveData& LoadData)
{
	//CharacterLevel = LoadData.CharacterLevel;
	//CurrentExp = LoadData.CharacterExp;
	////SetPlayerName()
	//CurrentGold = LoadData.Gold;
	//CurrentAmmoMap[EAmmoType::EAT_Rifle] = LoadData.RifleAmmo;
	////SaveData.WeaponType = EWeaponType::EWT_Rifle;
	//CurrentOwnedWeapons[0]->SetWeaponLevel(LoadData.WeaponLevel);
	//CurrentOwnedWeapons[0]->SetEnhancementLevel(LoadData.EnhancementLevel);
	//SavePlayerData();

	ULSSaveGame* NewPlayerData = NewObject<ULSSaveGame>();
	NewPlayerData->SavePlayerName(GetPlayerName());
	NewPlayerData->SaveCharacterLevel(LoadData.CharacterLevel);
	NewPlayerData->SaveCharacterExp(LoadData.CharacterExp);
	NewPlayerData->SaveGold(LoadData.Gold);
	if (CurrentOwnedWeapons.Num() == 0)
	{
		CurrentOwnedWeapons.Add(FWeaponSaveData());
	}
	CurrentOwnedWeapons[0].EnhancementLevel = LoadData.EnhancementLevel;
	CurrentOwnedWeapons[0].WeaponLevel = LoadData.WeaponLevel;
	CurrentOwnedWeapons[0].WeaponType = EWeaponType((int)LoadData.WeaponType);
	NewPlayerData->SaveOwnedWeapons(CurrentOwnedWeapons);
	CurrentAmmoMap[EAmmoType::EAT_Rifle] = LoadData.RifleAmmo;
	NewPlayerData->SaveAmmoMap(CurrentAmmoMap);


	/*if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		LSLOG_S(Error);
	}*/

	LSSaveGame = NewPlayerData;
	if (!UGameplayStatics::SaveGameToSlot(LSSaveGame, SaveSlotName, 0))
	{
		LSLOG_S(Error);
	}

	LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
}

void ALSPlayerState::BeginPlay()
{
	FActorSpawnParameters SpawnParam;
	HttpActor = GetWorld()->SpawnActor<AHttpActor>(AHttpActor::StaticClass(), FTransform());
	HttpActor->Init(this);
}

int32 ALSPlayerState::GetNextExp() 
{
	LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
	if (LSGameInstance)
	{
		PlayerStatData = LSGameInstance->GetLSPlayerData(CharacterLevel);
		if (PlayerStatData)
		{
			return PlayerStatData->NextExp;
		}
	}
	return -1;
}

float ALSPlayerState::GetExpRatio() 
{
    LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
	if (LSGameInstance)
	{
		PlayerStatData = LSGameInstance->GetLSPlayerData(CharacterLevel);
		if (PlayerStatData)
		{
			// 0 나눗셈 에러 방지
    		if (PlayerStatData->NextExp <= KINDA_SMALL_NUMBER)
   		 	{
   	    	 	return 0.0f;
	    	}
			return (float)CurrentExp / PlayerStatData->NextExp;
		}
	}
    return 0.0f;
}

bool ALSPlayerState::AddExp(int32 IncomeExp)
{
	LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
	if (LSGameInstance == nullptr)
	{
		return false;
	}
	PlayerStatData = LSGameInstance->GetLSPlayerData(CharacterLevel);
	if (PlayerStatData == nullptr || PlayerStatData->NextExp == -1)
	{
		return false;
	}

    bool bDidLevelUp = false;
    CurrentExp += IncomeExp;
    if (CurrentExp >= PlayerStatData->NextExp)
    {
        CurrentExp -= PlayerStatData->NextExp;
        SetCharacterLevel(CharacterLevel + 1);
        bDidLevelUp = true;
    }

    OnPlayerStateChanged.Broadcast();

    SavePlayerData();

    return bDidLevelUp;
}

void ALSPlayerState::SaveSessionId()
{
	if (HttpActor)
	{
		SessionId = HttpActor->GetSessionId();
	}

	//ULSSaveGame* NewPlayerData = NewObject<ULSSaveGame>();
	//NewPlayerData->SaveSessionId(SessionId);
	LSSaveGame->SaveSessionId(SessionId);

	if (!UGameplayStatics::SaveGameToSlot(LSSaveGame, SaveSlotName, 0))
	{
		LSLOG_S(Error);
	}
}

void ALSPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
    LSGameInstance = LSGameInstance ? LSGameInstance : Cast<ULSGameInstance>(GetGameInstance());
    if (LSGameInstance)
	{
		PlayerStatData = LSGameInstance->GetLSPlayerData(NewCharacterLevel);
	}
	CharacterLevel = NewCharacterLevel;
}

void ALSPlayerState::SetCurrentAmmo(const TMap<EAmmoType, int32>& AmmoMap)
{
	if (ResourceManger)
	{
		ResourceManger->SetCurrentAmmo(AmmoMap);
	}
}
