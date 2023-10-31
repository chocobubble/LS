// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSInteractableObejct.generated.h"

class UBoxComponent;

UCLASS()
class LOOTERSHOOTER_API ALSInteractableObejct : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSInteractableObejct();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

	UFUNCTION()
	virtual	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex) {}
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Loot")
	UBoxComponent* Trigger;
};
