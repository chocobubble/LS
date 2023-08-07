// Fill out your copyright notice in the Description page of Project Settings.


#include "LSMonster.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/WidgetComponent.h"
#include "LSAIController.h"
#include "LSAnimInstance.h"
#include "LSGameInstance.h"
#include "LSHUDWidget.h"
#include "Math/RotationMatrix.h"
#include "LSDefenseComponent.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "LSCharacterStatComponent.h"
#include "LSCharacterWidget.h"
#include "LSWeapon.h"
#include "LSGameMode.h"

// Sets default values
ALSMonster::ALSMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	DefenseManager = CreateDefaultSubobject<ULSDefenseComponent>(TEXT("DEFENSEMANAGER"));
	CharacterStat = CreateDefaultSubobject<ULSCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -88.0f),
		FRotator(0.0f, -90.0f, 0.0f)
	);

	HPBarWidget->SetupAttachment(GetMesh());

/*
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_QUINN(TEXT("/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn"));
	if ( SKM_QUINN.Succeeded() )
	{
		GetMesh()->SetSkeletalMesh( SKM_QUINN.Object );
	}
	else
	{
		LSLOG(Warning, TEXT("skeletalmesh desn't succeded"));
	}
*/

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// uaniminstace code..
	static ConstructorHelpers::FClassFinder<UAnimInstance> RIFLE_ANIM(TEXT("/Game/LS/Animations/RifleAnimBlueprint.RifleAnimBlueprint_C"));
	//
	if (RIFLE_ANIM.Succeeded() )
	{
		GetMesh()->SetAnimInstanceClass(RIFLE_ANIM.Class);
	}
	else
	{
		LSLOG(Warning, TEXT("Rifle anim desn't succeded"));
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LSCharacter"));

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/LS/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	AIControllerClass = ALSAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ALSMonster::BeginPlay()
{
	Super::BeginPlay();
	
	LSAIController = Cast<ALSAIController>(GetController());
	LSCHECK(nullptr != LSAIController);

	CharacterAssetToLoad.SetPath(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn'"));
	LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());
	LSCHECK(nullptr != LSGameInstance);
	AssetStreamingHandle = LSGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ALSMonster::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);

	DefenseManager->OnHPIsZero.AddUObject(this, &ALSMonster::SetCharacterStateDead);
}

void ALSMonster::SetCharacterState(ECharacterState NewState)
{
	LSCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{
		
		auto LSGameMode = Cast<ALSGameMode>(GetWorld()->GetAuthGameMode());
		LSCHECK(nullptr != LSGameMode);
		int32 TargetLevel = FMath::CeilToInt(((float)LSGameMode->GetScore() * 0.8f));
		int32 FinalLevel = FMath::Clamp<int32>(TargetLevel, 1, 20);
		LSLOG(Warning, TEXT("New NPC Level : %d"), FinalLevel);
		CharacterStat->SetNewLevel(FinalLevel);

		SetActorHiddenInGame(true);
		HPBarWidget->SetHiddenInGame(true);
		SetCanBeDamaged(false);
		break;
	}
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(false);
		SetCanBeDamaged(true);

		CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
			SetCharacterState(ECharacterState::DEAD);
		});
		
		auto CharacterWidget = Cast<ULSCharacterWidget>(HPBarWidget->GetUserWidgetObject());
		LSCHECK(nullptr != CharacterWidget);
		// CharacterWidget->BindCharacterStat(CharacterStat);
		CharacterWidget->BindDefenseComponent(DefenseManager);
			
		//SetControlMode(EControlMode::NPC);
		LSAIController->RunAI();
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		LSAnim->SetDeadAnim();
		SetCanBeDamaged(false);
		
		LSAIController->StopAI();
		

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
			DropItem();
			Destroy();
		}), DeadTimer, false);
	}
	}
}

ECharacterState ALSMonster::GetCharacterState() const
{
	return CurrentState;
}

// Called every frame
void ALSMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALSMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALSMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LSLOG_S(Warning);

	LSAnim = Cast<ULSAnimInstance>(GetMesh()->GetAnimInstance());
	LSCHECK(nullptr != LSAnim);

	//LSAnim->OnAttackHitCheck.AddUObject(this, &ALSMonster::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		LSLOG(Warning, TEXT("OnHPIsZero"));
		LSAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	});
/*
	ULSAnimInstance* AnimInstance = Cast<ULSAnimInstance>(GetMesh()->GetAnimInstance());
	LSCHECK(nullptr != AnimInstance);
*/
}

float ALSMonster::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	LSLOG(Warning, TEXT("Actor %s took damage : %f"), *GetName(), FinalDamage);
	
	DefenseManager->SetDamage(FinalDamage);
	
	// CharacterStat->SetDamage(FinalDamage);

	if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			LSLOG_S(Warning);
			/*
			ALSPlayerController* LSPC = Cast<ALSPlayerController>(EventInstigator);
			LSCHECK(nullptr != LSPC, 0.0f);
			LSPC->NPCKill(this);
			*/
		}
	}

	return FinalDamage;
}

void ALSMonster::SetWeapon(ALSWeapon* NewWeapon)
{
	/*
	LSCHECK(nullptr != NewWeapon);// && nullptr == CurrentWeapon);
	LSLOG_S(Warning);
	if (nullptr != EquipmentManager->GetCurrentWeaponInstance())
	{
		
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
		
	}
	*/
	
	
	FName WeaponSocket(TEXT("weapon_r_socket"));
	if(nullptr == RootComponent)
	{
		LSLOG(Warning, TEXT("No RootComponent"));
	}
	if(nullptr == GetMesh())
	{
		LSLOG(Warning, TEXT("no mesh"));
		return;
	}
	if (nullptr != NewWeapon)
	{
		LSLOG(Warning, TEXT("Attach to socket"));
		NewWeapon->SetActorHiddenInGame(false);
		NewWeapon->AttachToComponent(
			GetMesh(), 
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
			WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
	else
	{
		LSLOG(Warning, TEXT("CurWeapon is nullptr"));
	}
}

void ALSMonster::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
/*
	if(nullptr != AssetLoaded)
	{
		GetMesh()->SetSkeletalMesh(AssetLoaded);
	}
*/
	LSCHECK(nullptr != AssetLoaded);
	GetMesh()->SetSkeletalMesh(AssetLoaded);
	SetCharacterState(ECharacterState::READY);
}

void ALSMonster::DropItem()
{
	float RandomNumber = FMath::FRandRange(0.0f, 1.0f);
	if(RandomNumber < 0.1f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::GOLD, 100);
	}
	else if(RandomNumber < 0.2f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::HP, 100);
	}
	else if(RandomNumber < 0.4f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::MP, 100);
	}
	else if(RandomNumber < 0.6f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::RIFLEAMMO, 100);
	}
	else if(RandomNumber < 0.8f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::SHOTGUNAMMO, 100);
	}
	else if(RandomNumber <= 1.f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::PISTOLAMMO, 100);
	}

}

void ALSMonster::SetCharacterStateDead()
{
	SetCharacterState(ECharacterState::DEAD);
}

void ALSMonster::ShowDebugLine(FVector Dir)
{
}