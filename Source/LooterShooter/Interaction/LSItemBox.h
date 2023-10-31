// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSItemBox.generated.h"

class ULSWeaponDefinition;
class ALSPlayer;
class UParticleSystemComponent;
class UBoxComponent;

UCLASS()
class LOOTERSHOOTER_API ALSItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ALSItemBox();

	UFUNCTION()
	void OpenChest();

	ULSWeaponDefinition* GetWeaponItem();

	void SetWeaponItem(ALSPlayer* LSPlayer);
	
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex);
		
	UFUNCTION()
	void OnEffectFinished(UParticleSystemComponent* PSystem);

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Box")
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "Box")
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	UParticleSystemComponent* Effect;

	UPROPERTY(VisibleAnywhere, Category = "Box")
	TSubclassOf<ULSWeaponDefinition> WeaponItemClass;

	UPROPERTY(VisibleAnywhere, Category = "Box")
	TObjectPtr<ULSWeaponDefinition> WeaponItem;	

	UPROPERTY(VisibleAnywhere, Category = "Box")
	bool bIsDestroying = false;
};
