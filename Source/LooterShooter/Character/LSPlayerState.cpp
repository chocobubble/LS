// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerState.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/GameMode/LSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
#include "LooterShooter/Component/LSInventoryComponent.h"
#include "LooterShooter/Character/LSPlayerController.h"
#include "LooterShooter/Network/AHttpActor.h"
#include "CharacterData.pb.h"

ALSPlayerState::ALSPlayerState()
{
    SaveSlotName = TEXT("Player");
	CurrentAmmoMap.Add(EAmmoType::EAT_Rifle, 0);
	//SavedDelegate.BindUObject(this, &ALSPlayerState::SaveDataToServer);
}

void ALSPlayerState::InitPlayerData()
{
    ULSSaveGame* LSSaveGame = Cast<ULSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    if (LSSaveGame == nullptr)
    {
        LSSaveGame = GetMutableDefault<ULSSaveGame>();
    }
    SetPlayerName(LSSaveGame->GetSavedPlayerName());
    SetCharacterLevel(LSSaveGame->GetSavedCharacterLevel());
    CurrentExp = LSSaveGame->GetSavedCharacterExp();
	CurrentGold = LSSaveGame->GetSavedGold();
	CurrentOwnedWeapons = LSSaveGame->GetSavedOwnedWeapons();
	CurrentAmmoMap[EAmmoType::EAT_Rifle] = LSSaveGame->GetSavedAmmoMap()[EAmmoType::EAT_Rifle];

    SavePlayerData();

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

	
    if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
    {
        LSLOG_S(Error);
    }

	//UGameplayStatics::AsyncSaveGameToSlot(NewPlayerData, SaveSlotName, 0, SavedDelegate);
	LSLOG(Warning, TEXT("plyaer state weapon level - %d, enhance - %d"), CurrentOwnedWeapons[0]->GetWeaponLevel(), CurrentOwnedWeapons[0]->GetEnhancementLevel())
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
	
	SavePlayerData();
}

void ALSPlayerState::UpdateOwnedWeaponData()
{
	SavePlayerData();
}

void ALSPlayerState::SaveDataToServer()//(const FString& SlotName, const int32 UserIndex, bool Value)
{
	LSLOG(Warning, TEXT("save delegate"));
	/*CharacterData CurrentCharacterData;
	WeaponSaveData CurrentWeaponData;*/
	CurrentWeaponData.set_weapontype(WeaponSaveData_WeaponType_EWT_RIFLE);
	CurrentWeaponData.set_weaponlevel(CurrentOwnedWeapons[0]->GetWeaponLevel());
	CurrentWeaponData.set_weaponenhancementlevel(CurrentOwnedWeapons[0]->GetEnhancementLevel());
	CurrentCharacterData.set_level(CharacterLevel);
	CurrentCharacterData.set_exp(CurrentExp);
	CurrentCharacterData.set_playername(TCHAR_TO_ANSI(*GetPlayerName()));
	CurrentCharacterData.set_gold(CurrentGold);
	CurrentCharacterData.set_allocated_weaponsavedata(&CurrentWeaponData);

	CurrentCharacterData.set_rifleammo(CurrentAmmoMap[EAmmoType::EAT_Rifle]);

	//CurrentCharacterData.release_weaponsavedata();

	if (HttpActor)
	{
		HttpActor->SaveData(CurrentCharacterData);
		LSLOG(Warning, TEXT(" 서버에 데이터를 저장하는 데 성공했습니다. "));
	}
}

void ALSPlayerState::LoadDataFromServer()
{
	if (HttpActor)
	{
		CurrentCharacterData = HttpActor->LoadData();
		LSLOG(Warning, TEXT(" 서버에서 데이터를 가져오는 데 성공했습니다. "));
	}
}

void ALSPlayerState::BeginPlay()
{
	FActorSpawnParameters SpawnParam;
	HttpActor = GetWorld()->SpawnActor<AAHttpActor>(AAHttpActor::StaticClass(), FTransform());
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
