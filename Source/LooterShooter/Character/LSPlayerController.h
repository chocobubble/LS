// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter/LooterShooter.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "LSPlayerController.generated.h"

class ULSHUDWidget;
class ALSCharacter;
class ALSPlayerState;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class ULSGameplayWidget;
class ULSGameplayResultWidget;
class ALSMonster;
class ULSInventoryWidget;
class ULSRoundProgressbar;
class ULSEnhanceWidget;

///tset
class UMaterialInstance;
/**
 * 
 */
UCLASS()
class LOOTERSHOOTER_API ALSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALSPlayerController();

	void MonsterKill(ALSMonster* KilledMonster) const;	
	
	void OnGamePause(const FInputActionValue& Value);

	void OnInventoryOpen(const FInputActionValue& Value);

	void OnEnhanceUIOpen();

	void ChangeInputMode(bool bGameMode = true);

	void ShowResultUI();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* aPawn) override; 
	
	virtual void PlayerTick(float DeltaTime) override;
	
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* GamePause;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* OpenInventory;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	UInputAction* OpenEnhanceUI;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<ULSHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<ULSGameplayWidget> MenuWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<ULSGameplayResultWidget> ResultWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<ULSInventoryWidget> InventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<ULSRoundProgressbar> RoundPBWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<ULSEnhanceWidget> EnhanceWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	ULSHUDWidget* HUDWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	ULSGameplayWidget* MenuWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI");
	ULSGameplayResultWidget* ResultWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	ULSInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	ULSRoundProgressbar* RoundPBWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	ULSEnhanceWidget* EnhanceWidget;

	UPROPERTY(VisibleAnywhere, Category = "State")
	ALSPlayerState* LSPlayerState;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool bIsAutoRunning = false;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;


//////////////test///////
	UPROPERTY(VisibleAnywhere, Category = "TEST")
	UMaterialInstance* MI;
/////////////////////////

public:
	ULSHUDWidget* GetHUDWidget() const
	{
	    return HUDWidget;
	}

	bool IsAutoRunning() const
	{
		return bIsAutoRunning;
	}

	void SetAutoRunning(const bool bEnabled)
	{
		bIsAutoRunning = bEnabled;
	}
};
