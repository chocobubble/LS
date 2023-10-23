// Copyright Epic Games, Inc. All Rights Reserved.

#include "LooterShooterGameMode.h"
#include "LooterShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALooterShooterGameMode::ALooterShooterGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
