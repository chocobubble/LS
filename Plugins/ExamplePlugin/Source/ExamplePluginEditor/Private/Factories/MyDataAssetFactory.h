#pragma once

#include "Factories/Factory.h"
#include "UObject/ObjectMacros.h"
#include "MyDataAssetFactory.generated.h"

UCLASS(hidecategories=Object)
class UMyDataAssetFactory : public UFactory
{
    GENERATED_UCLASS_BODY()

public:

    virtual UObject * FactoryCreateBinary
    (
        UClass * InClass,
        UObject * InParent,
        FName InName,
        EObjectFlags Flags,
        UObject * Context,
        const TCHAR * Type,
        const uint8 *& Buffer,
        const uint8 * BufferEnd,
        FFeedbackContext * Warn,
        bool & bOutOperationCanceled
    ) override;
};