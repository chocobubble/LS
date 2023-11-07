// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSSection.h"
#include "LSStartBattleSection.generated.h"

/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSStartBattleSection : public ALSSection
{
	GENERATED_BODY()

	virtual void BattleStart() override;

protected:
	virtual void BeginPlay() override;

	
	virtual void SectionClear() override;

};
