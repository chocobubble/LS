// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDataAsset.h"

void UCharacterDataAsset::MakeProto(size_t& OutSize)
{
    CharacterData characterData;
    WeaponSaveData weaponSaveData;
    weaponSaveData.set_weapontype(WeaponSaveData_WeaponType_EWT_RIFLE);
    weaponSaveData.set_weaponlevel(2);
    weaponSaveData.set_weaponenhancementlevel(3);
    characterData.set_level(3);
    characterData.set_exp(5);
    characterData.set_playername("palyer");
    characterData.set_gold(100);
    //characterData.CharacterData::
    WeaponSaveData t = characterData.weaponsavedata();
    t.set_weaponenhancementlevel(3);
    t.set_weaponlevel(2);
    t.set_weapontype(WeaponSaveData_WeaponType_EWT_RIFLE);
    characterData.set_rifleammo(1000);
    //byte[] bytes = Encoding.UTF8.GetBytes("prototo");
    
    //OutSize = characterData.ByteSizeLong();
    /*OutSize = 1000;
    void* buffer = malloc(OutSize);
    characterData.SerializeToArray(buffer, OutSize);*/

    //FString str = UTF8_TO_TCHAR(characterData.SerializeAsString().c_str());


    std::string str = characterData.SerializeAsString();
    UE_LOG(LogTemp, Warning, TEXT("data string : %s , size is : %d"), UTF8_TO_TCHAR(str.c_str()), str.size());
    UE_LOG(LogTemp, Warning, TEXT("%s"), &str);

    CharacterData secondData;
    secondData.ParseFromString(str);
    UE_LOG(LogTemp, Warning, TEXT("second data level : %d"), secondData.level());

    uint8 buffer[100];
    if (characterData.SerializeToArray(buffer, 100))
    {
        FString Result;
        for (int32 idx = 0; idx < 100; ++idx)
        {
            int8 value = buffer[idx];
            Result += TCHAR(value);

        }
        UE_LOG(LogTemp, Warning, TEXT("second serialize string : %s"), *Result);
    }


    // test
    /*CharacterData test;
    test.ParseFromArray(buffer, OutSize);
    UE_LOG(LogTemp, Warning, TEXT("OUtSize : %d"), OutSize);
    UE_LOG(LogTemp, Warning, TEXT("test - levle : %d"), test.level());
    
    free(buffer);*/
    //return buffer;
   
    google::protobuf::ShutdownProtobufLibrary();
}

bool UCharacterDataAsset::Parse(const uint8*& Buffer, size_t length)
{
    if (data.ParseFromArray(Buffer, length))
    {
        UE_LOG(LogTemp, Warning, TEXT("Kennel parsing success"));
        UE_LOG(LogTemp, Warning, TEXT("uint8 Parse Level : %d"), data.level());
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Kennel parsing failed"));
        return false;
    }
}

bool UCharacterDataAsset::Parse(void*& Buffer, size_t length)
{
    
    if (data.ParseFromArray((uint8*)Buffer, length))
    {
        UE_LOG(LogTemp, Warning, TEXT("Kennel parsing success"));

        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Kennel parsing failed"));
        return false;
    }
}

bool UCharacterDataAsset::Parse(std::string str)
{
    if (data.ParseFromString(str))
    {
        UE_LOG(LogTemp, Warning, TEXT("Kennel parsing success"));
        UE_LOG(LogTemp, Warning, TEXT("string Parse Level : %d"), data.level());

        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Kennel parsing failed"));
        return false;
    }
    return false;
}

bool UCharacterDataAsset::ParseTest()
{
    /*uint8 buffer[] = "CAMQBRoGcGFseWVyIGQqBAgCEAMw6Ac=";
    CharacterData _data;
    _data.ParseFromArray((void*)buffer, sizeof(buffer));
    data.ParseFromArray(buffer, 34);
    UE_LOG(LogTemp, Warning, TEXT("Parse Test _ Level : %d"), _data.level());*/


    std::string str = "COyIDRCd4UsaDHBhbHllMTI0MjE0ciBkKgQIAhADMOgH";
    //"CAMQBRoGcGFseWVyIGQqBAgCEAMw6Ac="
    CharacterData _data;
    _data.ParseFromString(str);
    UE_LOG(LogTemp, Warning, TEXT("Parse Test _ Level : %d"), _data.level());

    const uint8 buffer[] = "COyIDRCd4UsaDHBhbHllMTI0MjE0ciBkKgQIAhADMOgH";
    //"CAMQBRoGcGFseWVyIGQqBAgCEAMw6Ac="
    CharacterData _data2;
    _data2.ParseFromArray(buffer, sizeof(buffer));
    UE_LOG(LogTemp, Warning, TEXT("Parse Test _ Level : %d"), _data2.level());
    return false;
}

int32 UCharacterDataAsset::Test()
{

    return data.level();
}

