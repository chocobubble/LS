// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LooterShooter.h"
#include "GameFramework/Character.h"
#include "LSMonster.generated.h"

class ULSCharacterStatComponent;
class ALSAIController;
class ULSDefenseComponent;
class UWidgetComponent;
class ULSGameInstance;
class ULSAnimInstance;
class ALSWeapon;
struct FStreamableHandle;

UCLASS()
class LOOTERSHOOTER_API ALSMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALSMonster();

	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);
	void Attack();
	void OnAssetLoadCompleted();

	void DropItem();

	void SetCharacterStateDead();

	void ShowDebugLine(FVector Dir);
	void SetWeapon(ALSWeapon* NewWeapon);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

	UPROPERTY(VisibleAnywhere)
	ALSAIController* LSAIController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	float DeadTimer;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	FVector ToAimDirection;

	UPROPERTY()
	ULSAnimInstance* LSAnim;

	FTimerHandle DeadTimerHandle = { };
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Defense)
	ULSDefenseComponent* DefenseManager;

	UPROPERTY(VisibleAnywhere, Category = UI)
	UWidgetComponent* HPBarWidget;

	UPROPERTY()
	ULSGameInstance* LSGameInstance;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	ULSCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	ALSWeapon* CurrentWeapon;

};
