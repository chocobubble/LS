// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/PlayerController.h"
#include "LSPlayerController.generated.h"

class ULSHUDWidget;
class ALSCharacter;
class ALSPlayerState;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALSPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override; 

	ULSHUDWidget* GetHUDWidget() const;

	void NPCKill(ALSCharacter* KilledNPC) const;

	void AddGameScore() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<ULSHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
	ULSHUDWidget* HUDWidget;

	UPROPERTY()
	ALSPlayerState* LSPlayerState;
};
