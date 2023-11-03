// Fill out your copyright notice in the Description page of Project Settings.

#include "LooterShooter/Character/LSMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/WidgetComponent.h"
#include "LSAIController.h"
#include "LooterShooter/Animation/LSAnimInstance.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/UI/LSHUDWidget.h"
#include "Math/RotationMatrix.h"
#include "LooterShooter/Component/LSDefenseComponent.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "LooterShooter/Component/LSCharacterStatComponent.h"
#include "LooterShooter/UI/LSCharacterWidget.h"
#include "LooterShooter/Weapon/LSWeapon.h"
#include "LooterShooter/GameMode/LSGameMode.h"
#include "LSPlayerController.h"

ALSMonster::ALSMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	DefenseManager = CreateDefaultSubobject<ULSDefenseComponent>(TEXT("DEFENSEMANAGER"));
	CharacterStat = CreateDefaultSubobject<ULSCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_CharM_Ram(TEXT("/Game/LS/Meshes/SK_CharM_Ram.SK_CharM_Ram"));
	if (SKM_CharM_Ram.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SKM_CharM_Ram.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> MONSTER_ANIM(TEXT("/Game/LS/Animations/RifleAnimBlueprint.RifleAnimBlueprint_C"));
	if (MONSTER_ANIM.Succeeded())
	{
		if (MONSTER_ANIM.Class)
		{
			GetMesh()->SetAnimInstanceClass(MONSTER_ANIM.Class);
		}
	}

	LSWeaponInstanceClass = ALSWeapon::StaticClass();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LSCharacter"));
	
	if (HPBarWidget)
	{
		HPBarWidget->SetupAttachment(GetMesh());	
		HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
		HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
		static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/LS/UI/UI_HPBar.UI_HPBar_C"));
		if (UI_HUD.Succeeded())
		{
			HPBarWidget->SetWidgetClass(UI_HUD.Class);
			HPBarWidget->SetDrawSize(FVector2D(100.0f, 50.0f));
		}
	}

	AIControllerClass = ALSAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SetActorHiddenInGame(true);
	SetCanBeDamaged(false);
}

void ALSMonster::BeginPlay()
{
	Super::BeginPlay();

	LSAIController = Cast<ALSAIController>(GetController());
	LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	CharacterAssetToLoad.SetPath(TEXT("/Game/LS/Meshes/SKM_Player2.SKM_Player2"));
	AssetStreamingHandle = LSGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ALSMonster::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::ECS_Loading);

	// TODO : default 로 생성되게 바꾸기
	MonsterWeapon = GetWorld()->SpawnActor<ALSWeapon>(FVector::ZeroVector, FRotator::ZeroRotator); 
	EquipWeapon();

	if (DefenseManager)
	{
		DefenseManager->OnHPIsZero.AddUObject(this, &ALSMonster::SetCharacterStateDead);
	}
}

void ALSMonster::SetCharacterState(ECharacterState NewState)
{
	CurrentState = NewState;

	switch (CurrentState)
	{
		case ECharacterState::ECS_Loading:
		{
			SetActorHiddenInGame(true);
			HPBarWidget->SetHiddenInGame(true);
			SetCanBeDamaged(false);
			break;
		}
		case ECharacterState::ECS_Ready:
		{
			SetActorHiddenInGame(false);
			HPBarWidget->SetHiddenInGame(false);
			SetCanBeDamaged(true);
			ULSCharacterWidget* CharacterWidget = Cast<ULSCharacterWidget>(HPBarWidget->GetUserWidgetObject());
			if (CharacterWidget && DefenseManager)
			{				
				CharacterWidget->BindDefenseComponent(DefenseManager);
				CharacterWidget->SetMonsterLevel(MonsterLevel);
			}
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
			LSAIController->RunAI();
			break;
		}
		case ECharacterState::ECS_Dead:
		{
			SetActorEnableCollision(false);
			GetMesh()->SetHiddenInGame(false);
			HPBarWidget->SetHiddenInGame(true);
			LSMonsterAnim->SetDeadAnim();
			SetCanBeDamaged(false);

			LSAIController->StopAI();

			GetWorld()->GetTimerManager().SetTimer(
				DeadTimerHandle,
				FTimerDelegate::CreateLambda([this]() -> void {
					DropItem();
					MonsterWeapon->Destroy();
					Destroy(); }),
				DeadTimer,
				false
			);
		}
	}
}

void ALSMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALSMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetMesh() && GetMesh()->GetAnimInstance())
	{
		LSMonsterAnim = Cast<ULSAnimInstance>(GetMesh()->GetAnimInstance());
	}
}

void ALSMonster::Init(const int32 Level)
{
	SetMonsterLevel(Level);
	if (LSGameInstance)
	{
		FLSMonsterData* LSMonsterData = LSGameInstance->GetLSMonsterData(MonsterLevel);
		if (DefenseManager && LSMonsterData)
		{
			DefenseManager->SetMaxHP(LSMonsterData->MaxHP);
			DefenseManager->SetMaxShield(LSMonsterData->MaxShield);
		}
	}
}

float ALSMonster::TakeDamage(const float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DefenseManager)
	{
		DefenseManager->SetDamage(FinalDamage);
	}

	if (CurrentState == ECharacterState::ECS_Dead)
	{
		if (EventInstigator->IsPlayerController())
		{
			ALSPlayerController* LSPlayerController = Cast<ALSPlayerController>(EventInstigator);
			if (LSPlayerController)
			{
				LSPlayerController->MonsterKill(this);	
			}
		}
	}
	return FinalDamage;
}

void ALSMonster::EquipWeapon()
{
	FName WeaponSocket(TEXT("weapon_r_socket"));
	if (MonsterWeapon)
	{
		MonsterWeapon->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
		MonsterWeapon->SetOwner(this);
	}
}

void ALSMonster::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
	if (AssetLoaded)
	{
		GetMesh()->SetSkeletalMesh(AssetLoaded);
		SetCharacterState(ECharacterState::ECS_Ready);	
	}
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
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::ELIT_HP, 100);
	}
	else if (RandomNumber < 1.0f)
	{
		LSGameInstance->SpawnAutoLootItem(GetActorLocation(), ELootItemType::ELIT_RifleAmmo, 100);
	}
}

void ALSMonster::SetCharacterStateDead()
{
	SetCharacterState(ECharacterState::ECS_Dead);
}

void ALSMonster::SetAttackTarget(APawn* TargetPawn)
{
	if (TargetPawn)
	{
		AttackTarget = TargetPawn;
	}
}

void ALSMonster::Attack()
{
	if (AttackTarget == nullptr)
	{
		return;
	}
	FVector ShootDir = CalculateRecoil(AttackTarget->GetActorLocation() - GetActorLocation(), BulletSpreadAngle);
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		GetActorLocation(),
		(ShootDir * AttackRange) + GetActorLocation(),
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);

#if ENABLE_DRAW_DEBUG
	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		(ShootDir * AttackRange) + GetActorLocation(),
		bResult ? FColor::Green : FColor::White,
		false,
		0.5f,
		0.0f,
		2.0f
	);
#endif

	if (bResult)
	{
		if (HitResult.HasValidHitObjectHandle())
		{
			float FinalAttackDamage = AttackDamage;
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(FinalAttackDamage, DamageEvent, GetController(), this);
		}
	}
}

FVector ALSMonster::CalculateRecoil(const FVector& AimDir, const float SpreadAngle)
{
	const float RandomAngle = FMath::FRandRange(0.0f, 1.0f) * 360.0f;
	FRotator Rot = AimDir.Rotation();
	FQuat DirQuat(Rot);
	FQuat FromCenterQuat(FRotator(0.0f, SpreadAngle, 0.0f));
	FQuat AroundQuat(FRotator(0.0f, 0.0f, RandomAngle));
	FQuat FinalDirectionQuat = DirQuat * AroundQuat * FromCenterQuat;
	FinalDirectionQuat.Normalize();
	return FinalDirectionQuat.RotateVector(FVector::ForwardVector);
}