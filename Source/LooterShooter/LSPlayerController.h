// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
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

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override; 
	virtual void PlayerTick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void SetupInputComponent() override;

	ULSHUDWidget* GetHUDWidget() const;

	void MonsterKill(ALSMonster* KilledMonster) const;	
	void OnGamePause(const FInputActionValue& Value);
	void OnInventoryOpen(const FInputActionValue& Value);

	void ChangeInputMode(bool bGameMode = true);

	void ShowResultUI();
	void ShowInventoryUI();

	bool GetIsAutoRunning() const;

	void SetIsAutoRunning(const bool bEnabled);

//////////////test///////
public:
	UPROPERTY(VisibleAnywhere, Category = TEST)
	UMaterialInstance* MI;
/////////////////////////

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<ULSHUDWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* GamePause;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<ULSGameplayWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<ULSGameplayResultWidget> ResultWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<ULSInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<ULSRoundProgressbar> RoundPBWidgetClass;

private:
	UPROPERTY()
	ULSHUDWidget* HUDWidget;

	UPROPERTY()
	ALSPlayerState* LSPlayerState;

	UPROPERTY()
	ULSGameplayWidget* MenuWidget;

	UPROPERTY()
	ULSGameplayResultWidget* ResultWidget;

	UPROPERTY()
	ULSInventoryWidget* InventoryWidget;

	UPROPERTY()
	ULSRoundProgressbar* RoundPBWidget;


	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

	bool bIsAutoRunning = false;
};
