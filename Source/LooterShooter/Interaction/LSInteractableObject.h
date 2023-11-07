// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSInteractableObject.generated.h"

class UBoxComponent;

DECLARE_MULTICAST_DELEGATE(FOnCompleteInteractionDelegate);

UCLASS()
class LOOTERSHOOTER_API ALSInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSInteractableObject();

	virtual void Interact();

	FOnCompleteInteractionDelegate OnCompleteInteraction;

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

private:

};
