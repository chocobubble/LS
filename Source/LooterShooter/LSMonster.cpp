// Fill out your copyright notice in the Description page of Project Settings.

#include "LSMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
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
#include "LSPlayerController.h"

// Sets default values
ALSMonster::ALSMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	DefenseManager = CreateDefaultSubobject<ULSDefenseComponent>(TEXT("DEFENSEMANAGER"));
	CharacterStat = CreateDefaultSubobject<ULSCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_CharM_Ram(TEXT("/Game/LS/Meshes/SK_CharM_Ram.SK_CharM_Ram"));
	if ( SKM_CharM_Ram.Succeeded() )
	{
		GetMesh()->SetSkeletalMesh( SKM_CharM_Ram.Object );
	}
	else
	{
		LSLOG(Warning, TEXT("skeletalmesh desn't succeded"));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> MONSTER_ANIM(TEXT("/Game/LS/Animations/RifleAnimBlueprint.RifleAnimBlueprint_C"));
	if (MONSTER_ANIM.Succeeded())
	{
		LSCHECK(MONSTER_ANIM.Class != nullptr);
		GetMesh()->SetAnimInstanceClass(MONSTER_ANIM.Class);
	}

	LSWeaponInstanceClass = ALSWeapon::StaticClass();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LSCharacter"));
	
	HPBarWidget->SetupAttachment(GetMesh());	
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

	SetActorHiddenInGame(true);
	SetCanBeDamaged(false);
}

// Called when the game starts or when spawned
void ALSMonster::BeginPlay()
{
	Super::BeginPlay();

	LSAIController = Cast<ALSAIController>(GetController());
	LSCHECK(nullptr != LSAIController);

	CharacterAssetToLoad.SetPath(TEXT("/Game/LS/Meshes/SKM_Player2.SKM_Player2"));
	LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());
	LSCHECK(nullptr != LSGameInstance);
	AssetStreamingHandle = LSGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ALSMonster::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);

	// 나중에 async로 바꾸기
	MonsterWeapon = GetWorld()->SpawnActor<ALSWeapon>(FVector::ZeroVector, FRotator::ZeroRotator); 
    //MonsterWeapon->SetBaseWeaponDefinition(this);
	//MonsterWeapon->Init();
	SetWeapon();

	DefenseManager->OnHPIsZero.AddUObject(this, &ALSMonster::SetCharacterStateDead);
}

void ALSMonster::SetCharacterState(ECharacterState NewState)
{
	// LSCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{

		auto LSGameMode = Cast<ALSGameMode>(GetWorld()->GetAuthGameMode());
		LSCHECK(nullptr != LSGameMode);
		//int32 TargetLevel = FMath::CeilToInt(((float)LSGameMode->GetScore() * 0.8f));
		//int32 FinalLevel = FMath::Clamp<int32>(TargetLevel, 1, 20);
		int32 CurrentPlayerLevel = LSGameMode->GetPlayerLevel();
		LSLOG(Warning, TEXT("New NPC Level : %d"), CurrentPlayerLevel);
		CharacterStat->SetNewLevel(CurrentPlayerLevel);

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
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		LSAIController->RunAI();
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		LSMonsterAnim->SetDeadAnim();
		SetCanBeDamaged(false);

		LSAIController->StopAI();

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			DropItem();
			MonsterWeapon->Destroy();
			Destroy(); }),
			DeadTimer, false);
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
void ALSMonster::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALSMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LSLOG_S(Warning);

	LSCHECK(GetMesh()->GetAnimInstance() != nullptr);
	LSMonsterAnim = Cast<ULSAnimInstance>(GetMesh()->GetAnimInstance());
	LSCHECK(nullptr != LSMonsterAnim);

	// LSAnim->OnAttackHitCheck.AddUObject(this, &ALSMonster::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		LSLOG(Warning, TEXT("OnHPIsZero"));
		LSMonsterAnim->SetDeadAnim();
		SetActorEnableCollision(false);});

}

float ALSMonster::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	LSLOG(Warning, TEXT("Actor %s took damage : %f"), *GetName(), FinalDamage);
	DefenseManager->SetDamage(FinalDamage);

	if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			LSLOG_S(Warning);
			ALSPlayerController* LSPC = Cast<ALSPlayerController>(EventInstigator);
			LSCHECK(nullptr != LSPC, 0.0f);
			LSPC->MonsterKill(this);
		}
	}
	return FinalDamage;
}

void ALSMonster::SetWeapon()
{
	FName WeaponSocket(TEXT("weapon_r_socket"));
	LSCHECK(nullptr != MonsterWeapon)
	MonsterWeapon->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		WeaponSocket);
	MonsterWeapon->SetOwner(this);
}

void ALSMonster::OnAssetLoadCompleted()
{
	USkeletalMesh *AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
	LSCHECK(nullptr != AssetLoaded);
	GetMesh()->SetSkeletalMesh(AssetLoaded);
	SetCharacterState(ECharacterState::READY);
	//MonsterWeapon = LSGameInstance->RifleWeaponMesh;
	//SetWeapon();
}

void ALSMonster::DropItem()
{
	float RandomNumber = FMath::FRandRange(0.0f, 1.0f);
	if (RandomNumber < 0.3f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::GOLD, 100);
	}
	else if (RandomNumber < 0.6f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::HP, 100);
	}
	else if (RandomNumber < 1.f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::RIFLEAMMO, 100);
	}
	/*
	if (RandomNumber < 0.1f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::GOLD, 100);
	}
	else if (RandomNumber < 0.2f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::HP, 100);
	}
	else if (RandomNumber < 0.4f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::MP, 100);
	}
	else if (RandomNumber < 0.6f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::RIFLEAMMO, 100);
	}
	else if (RandomNumber < 0.8f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::SHOTGUNAMMO, 100);
	}
	else if (RandomNumber <= 1.f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::PISTOLAMMO, 100);
	}
	*/
}

void ALSMonster::SetCharacterStateDead()
{
	LSLOG(Warning, TEXT("Monster is dead"));
	SetCharacterState(ECharacterState::DEAD);
}

void ALSMonster::ShowDebugLine(FVector Dir)
{
}

void ALSMonster::SetAttackTarget(APawn* TargetPawn)
{
	LSCHECK(TargetPawn != nullptr);
	AttackTarget = TargetPawn;
}

void ALSMonster::Attack()
{
	LSCHECK(AttackTarget != nullptr);
	FVector ShootDir = CalculateRecoil(AttackTarget->GetActorLocation() - GetActorLocation(), BulletSpreadAngle);

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		GetActorLocation(),
		(ShootDir * AttackRange) + GetActorLocation(),
		ECollisionChannel::ECC_GameTraceChannel1,
		Params);

#if ENABLE_DRAW_DEBUG

	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		(ShootDir * AttackRange) + GetActorLocation(),
		bResult ? FColor::Green : FColor::White,
		true,
		-1.0f,
		0.,
		5.f);

#endif

	if (bResult)
	{
		if (HitResult.HasValidHitObjectHandle())
		{
			LSLOG(Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
			float FinalAttackDamage = AttackDamage;
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(FinalAttackDamage, DamageEvent, GetController(), this);
		}
		else
		{
			LSLOG(Warning, TEXT("Actor nullptr"));
		}
	}
	else
	{
		LSLOG(Warning, TEXT("Didn't hit"));
	}
}

FVector ALSMonster::CalculateRecoil(FVector AimDir, const float SpreadAngle)
{
	const float RandomAngle = FMath::FRandRange(0.f, 1.f) * 360.0f;

	FRotator Rot = AimDir.Rotation();
	FQuat DirQuat(Rot);
	FQuat FromCenterQuat(FRotator(0.0f, SpreadAngle, 0.0f));
	FQuat AroundQuat(FRotator(0.0f, 0.0, RandomAngle));
	FQuat FinalDirectionQuat = DirQuat * AroundQuat * FromCenterQuat;
	FinalDirectionQuat.Normalize();
	return FinalDirectionQuat.RotateVector(FVector::ForwardVector);
}