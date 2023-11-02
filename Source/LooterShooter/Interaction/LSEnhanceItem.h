// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSInteractableObject.h"
#include "LSEnhanceItem.generated.h"

class UBoxComponent;
class ALSPlayer;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSEnhanceItem : public ALSInteractableObject
{
	GENERATED_BODY()

public:
	ALSEnhanceItem();

	UFUNCTION()
	void OpenEnhanceUI();

	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex) override;

	virtual void Interact() override;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Character")
	ALSPlayer* OverlappedCharacter;
};
