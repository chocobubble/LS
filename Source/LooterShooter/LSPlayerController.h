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
	//virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void SetupInputComponent() override;

	ULSHUDWidget* GetHUDWidget() const;

	void NPCKill(ALSCharacter* KilledNPC) const;

	void AddGameScore() const;

	
	void OnGamePause(const FInputActionValue& Value);

	void ChangeInputMode(bool bGameMode = true);

	void ShowResultUI();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<ULSHUDWidget> HUDWidgetClass;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* GamePause;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<ULSGameplayWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<ULSGameplayResultWidget> ResultWidgetClass;

private:
	UPROPERTY()
	ULSHUDWidget* HUDWidget;

	UPROPERTY()
	ALSPlayerState* LSPlayerState;

	UPROPERTY()
	ULSGameplayWidget* MenuWidget;

	UPROPERTY()
	ULSGameplayResultWidget* ResultWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};
