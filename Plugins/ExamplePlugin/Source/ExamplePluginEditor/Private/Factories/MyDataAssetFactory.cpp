#include "MyDataAssetFactory.h"
#include "Containers/UnrealString.h"
#include "CharacterDataAsset.h"

UMyDataAssetFactory::UMyDataAssetFactory( const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{
    Formats.Add(FString(TEXT("knl;")) + NSLOCTEXT("UMyDataAssetFactory", "FormatData", "Compiled Data File").ToString());
    SupportedClass = UDataAsset::StaticClass();
    bCreateNew = false;
    bEditorImport = true;
}

UObject* UMyDataAssetFactory::FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext * Warn, bool & bOutOperationCanceled)
{
    UCharacterDataAsset* asset = nullptr;

    asset = NewObject<UCharacterDataAsset>(InParent, InClass, InName, Flags);
    bool success = asset->Parse(Buffer, BufferEnd - Buffer);

    if (success == true)
    {
        bOutOperationCanceled = false;
    }
    else
    {
        asset = nullptr;
        bOutOperationCanceled = true;
    }

    return asset;
}