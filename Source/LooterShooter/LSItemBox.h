// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Actor.h"
#include "LSItemBox.generated.h"

UCLASS()
class LOOTERSHOOTER_API ALSItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Box)
	class UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	class UParticleSystemComponent* Effect;

	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class ALSWeapon> WeaponItemClass;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);
};
