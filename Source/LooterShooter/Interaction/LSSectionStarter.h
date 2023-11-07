// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSInteractableObject.h"
#include "LSSectionStarter.generated.h"

class ALSPlayer;
class ALSSection;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSSectionStarter : public ALSInteractableObject
{
	GENERATED_BODY()

public:
	ALSSectionStarter();

	void Init(ALSSection* Section);

protected:
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override; 

	virtual void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void Interact() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Section")
	ALSSection* StartBattleSection;

	UPROPERTY(VisibleAnywhere, Category = "Section")
	bool bIsSectionReady = true;
};
