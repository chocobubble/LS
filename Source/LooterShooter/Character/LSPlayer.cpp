// Fill out your copyright notice in the Description page of Project Settings.

#include "LSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "LooterShooter/Component/LSCharacterStatComponent.h"
#include "LooterShooter/Animation/LSPlayerAnimInstance.h"
#include "LSPlayerController.h"
#include "LSPlayerState.h"
#include "LooterShooter/System/LSGameInstance.h"
#include "LooterShooter/UI/LSHUDWidget.h"
#include "LooterShooter/Component/LSDefenseComponent.h"
#include "LooterShooter/Component/LSEquipmentComponent.h"
#include "Math/RotationMatrix.h"
#include "LooterShooter/UI/LSTextPopup.h"
#include "LooterShooter/Interaction/LSAutoLootItem.h"
#include "LooterShooter/Weapon/LSWeaponInstance.h"
#include "LooterShooter/Component/LSInventoryComponent.h"
#include "LooterShooter/Interaction/LSItemBox.h"
#include "LooterShooter/Weapon/LSWeaponDefinition.h"
#include "LooterShooter/Weapon/LSAmmo.h"
#include "DrawDebugHelpers.h"

ALSPlayer::ALSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<ULSCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	ResourceManager = CreateDefaultSubobject<ULSResourceManageComponent>(TEXT("RESOURCEMANAGER"));
	DefenseManager = CreateDefaultSubobject<ULSDefenseComponent>(TEXT("DEFENSEMANAGER"));
	EquipmentManager = CreateDefaultSubobject<ULSEquipmentComponent>(TEXT("EQUIPMENT"));
	InventoryManager = CreateDefaultSubobject<ULSInventoryComponent>(TEXT("INVENTORY"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	ArmLengthTo = ArmLengthOnIdle; // 450.0f
	SpringArm->TargetArmLength = ArmLengthTo;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0.0f, 45.0f, 90.0f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_MANNY(TEXT("/Game/LS/Meshes/SKM_Player.SKM_Player"));
	if (SKM_MANNY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SKM_MANNY.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_PLAYER(TEXT("/Game/LS/Animations/PlayerAnimBlueprint.PlayerAnimBlueprint_C"));
	if (ANIM_PLAYER.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_PLAYER.Class);
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LSCharacter"));
	SetActorHiddenInGame(true);
	SetCanBeDamaged(false);

	///////////////////////// Input ///////////////////////////////
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT_KBM(TEXT("/Game/LS/Input/IMC_Default_KBM.IMC_Default_KBM"));
	if (IMC_DEFAULT_KBM.Succeeded())
	{
		InputMapping = IMC_DEFAULT_KBM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVE(TEXT("/Game/LS/Input/Actions/IA_Move.IA_Move"));
	if (IA_MOVE.Succeeded())
	{
		MoveAction = IA_MOVE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP(TEXT("/Game/LS/Input/Actions/IA_Jump.IA_Jump"));
	if (IA_JUMP.Succeeded())
	{
		JumpAction = IA_JUMP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Game/LS/Input/Actions/IA_LOOK.IA_LOOK"));
	if (IA_LOOK.Succeeded())
	{
		LookAction = IA_LOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SHOOT(TEXT("/Game/LS/Input/Actions/IA_SHOOT.IA_SHOOT"));
	if (IA_SHOOT.Succeeded())
	{
		ShootAction = IA_SHOOT.Object;
		if (ShootAction->Triggers.Num() > 0)
		{
			ShootInputTriggerPulse = Cast<UInputTriggerPulse>(ShootAction->Triggers[0]);
			if (ShootInputTriggerPulse)
			{
				// TODO : 수정
				// fire rate
				//ShootInputTriggerPulse->Interval = 0.1f;
				SetShootInputInterval(0.2f); // default for debug
			}
		}
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MELEE(TEXT("/Game/LS/Input/Actions/IA_MELEE.IA_MELEE"));
	if (IA_MELEE.Succeeded())
	{
		MeleeAttackAction = IA_MELEE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_AUTO_RUN(TEXT("/Game/LS/Input/Actions/IA_Auto_Run.IA_Auto_Run"));
	if (IA_AUTO_RUN.Succeeded())
	{
		AutoRunAction = IA_AUTO_RUN.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_AIM(TEXT("/Game/LS/Input/Actions/IA_Aim.IA_Aim"));
	if (IA_AIM.Succeeded())
	{
		AimAction = IA_AIM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_GRAPPLING_HOOK(TEXT("/Game/LS/Input/Actions/IA_GrapplingHook.IA_GrapplingHook"));
	if (IA_GRAPPLING_HOOK.Succeeded())
	{
		GrapplingHookAction = IA_GRAPPLING_HOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_RELOAD(TEXT("/Game/LS/Input/Actions/IA_Reload.IA_Reload"));
	if (IA_RELOAD.Succeeded())
	{
		ReloadAction = IA_RELOAD.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_EQUIP_FIRST_WEAPON(TEXT("/Game/LS/Input/Actions/IA_FirstWeapon.IA_FirstWeapon"));
	if (IA_EQUIP_FIRST_WEAPON.Succeeded())
	{
		EquipFirstWeaponAction = IA_EQUIP_FIRST_WEAPON.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_EQUIP_SECOND_WEAPON(TEXT("/Game/LS/Input/Actions/IA_SecondWeapon.IA_SecondWeapon"));
	if (IA_EQUIP_SECOND_WEAPON.Succeeded())
	{
		EquipSecondWeaponAction = IA_EQUIP_SECOND_WEAPON.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_EQUIP_THIRD_WEAPON(TEXT("/Game/LS/Input/Actions/IA_ThirdWeapon.IA_ThirdWeapon"));
	if (IA_EQUIP_THIRD_WEAPON.Succeeded())
	{
		EquipThirdWeaponAction = IA_EQUIP_THIRD_WEAPON.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_INTERACT(TEXT("/Game/LS/Input/Actions/IA_Interact.IA_Interact"));
	if (IA_INTERACT.Succeeded())
	{
		InteractAction = IA_INTERACT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UCurveVector> CURVE_RECOIL(TEXT("/Game/LS/RecoilCurve.RecoilCurve"));
	if (CURVE_RECOIL.Succeeded())
	{
		RecoilCurve = CURVE_RECOIL.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_TEST(TEXT("/Game/LS/Input/Actions/IA_TESTKEY.IA_TESTKEY"));
	if (IA_TEST.Succeeded())
	{
		TestAction = IA_TEST.Object;
	}
	///////////////////////////////////////////
}

void ALSPlayer::BeginPlay()
{
	Super::BeginPlay();

	LSPlayerController = Cast<ALSPlayerController>(GetController());
	ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
	LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	CharacterAssetToLoad.SetPath(TEXT("/Game/LS/Meshes/SKM_Player.SKM_Player"));
	AssetStreamingHandle = LSGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ALSPlayer::OnAssetLoadCompleted));
	
	SetCharacterState(ECharacterState::LOADING);

	if (DefenseManager)
	{
		DefenseManager->OnHPIsZero.AddUObject(this, &ALSPlayer::SetCharacterStateDead);
	}

	if (Camera)
	{
		ToAimDirection = FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X);
	}
}

void ALSPlayer::SetCharacterState(ECharacterState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;

	switch (CurrentState)
	{
		// 캐릭터 비동기 로딩 상태
		case ECharacterState::LOADING:
		{
			DisableInput(LSPlayerController);
			LSPlayerController->GetHUDWidget()->BindDefenseComponent(DefenseManager);
			ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
			if(LSPlayerState != nullptr && CharacterStat != nullptr)
			{
				CharacterStat->SetNewLevel(LSPlayerState->GetCharacterLevel());
			}
			SetActorHiddenInGame(true);
			SetCanBeDamaged(false);
			break;
		}
		// 캐릭터 로딩이 완료되어 씬 상에 표현되고 동작 가능한 상태
		case ECharacterState::READY:
		{
			SetActorHiddenInGame(false);
			SetCanBeDamaged(true);
			/*
			CharacterStat->OnHPIsZero.AddLambda([this]() -> void { 
				SetCharacterState(ECharacterState::DEAD); });
			*/
			GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
			GetCharacterMovement()->JumpZVelocity = DefaultJumpHeight;
			EnableInput(LSPlayerController);
			break;
		}
		// 캐릭터의 HP가 0 이하가 되어 죽은 상태
		case ECharacterState::DEAD:
		{
			SetActorEnableCollision(false);
			GetMesh()->SetHiddenInGame(false);
			LSPlayerAnim->SetDeadAnim();
			SetCanBeDamaged(false);
			DisableInput(LSPlayerController);	

			GetWorld()->GetTimerManager().SetTimer(
				DeadTimerHandle,
				FTimerDelegate::CreateLambda([this]() -> void {LSPlayerController->ShowResultUI();}),
				DeadTimer,
				false
			);
		}
	}
}

void ALSPlayer::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
	if (AssetLoaded)
	{
		GetMesh()->SetSkeletalMesh(AssetLoaded);
	}
	SetCharacterState(ECharacterState::READY);
}

void ALSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthChangingSpeed);

	// TODO : 최적화하기
	// if(bIsInteracting) 같은 걸로
	InteractCheck();

	// 그래플링 훅 사용한 경우
	if (bIsGrappling)
	{
		LaunchCharacter(((GrappleToLocation - GetActorLocation()) + GetActorUpVector() * GrapplingHeightCorrection)* GrapplingMovementSpeed, true, true);
		if ((GrappleToLocation - GetActorLocation()).Size() < GrapplingStopRange)
		{
			bIsGrappling = false;
		}
	}

	/// test
	if (!(CurrentRemainElapsedTime < KINDA_SMALL_NUMBER))
	{
		float temp = FMath::FInterpTo(0, CurrentRecoilTest, DeltaTime, InterpolateSpeed);
		AddControllerPitchInput(temp);
		CurrentRemainElapsedTime -= DeltaTime;
		if (CurrentRemainElapsedTime < 0.3f)
		{
			CurrentRecoilTest = -RecoilTest;
			InterpolateSpeed = Acceleration / 2;
		}
	}

	// 반동 tick
	RecoilTick(DeltaTime);
}

void ALSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		return;
	}

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent == nullptr)
	{
		return;
	}

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALSPlayer::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALSPlayer::Jump);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALSPlayer::Look);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ALSPlayer::Shoot);
	EnhancedInputComponent->BindAction(MeleeAttackAction, ETriggerEvent::Triggered, this, &ALSPlayer::MeleeAttack);
	EnhancedInputComponent->BindAction(AutoRunAction, ETriggerEvent::Started, this, &ALSPlayer::OnRunning);
	EnhancedInputComponent->BindAction(AutoRunAction, ETriggerEvent::Completed, this, &ALSPlayer::EndRunning);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ALSPlayer::OnAiming);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ALSPlayer::EndAiming);
	EnhancedInputComponent->BindAction(GrapplingHookAction, ETriggerEvent::Triggered, this, &ALSPlayer::GrapplingHook);
	EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ALSPlayer::Reload);
	EnhancedInputComponent->BindAction(EquipFirstWeaponAction, ETriggerEvent::Triggered, this, &ALSPlayer::EquipFirstWeapon);
	EnhancedInputComponent->BindAction(EquipSecondWeaponAction, ETriggerEvent::Triggered, this, &ALSPlayer::EquipSecondWeapon);
	EnhancedInputComponent->BindAction(EquipThirdWeaponAction, ETriggerEvent::Triggered, this, &ALSPlayer::EquipThirdWeapon);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Ongoing, this, &ALSPlayer::InteractProgress);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ALSPlayer::Interact);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ALSPlayer::InteractEnd);
	EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ALSPlayer::TestAct);
}

void ALSPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ALSPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ALSPlayer::Shoot(const FInputActionValue& Value)
{	
	// TODO: CanAttack 으로 확인하기
	if (CurrentWeapon == nullptr)
	{
		return;
	}
	// TODO : ammo type 늘리기
	if (!CanShoot(EAmmoType::RIFLE))
	{
		return;
	}

	// 총알 생성 후 발사
	Ammo = GetWorld()->SpawnActor<ALSAmmo>(CurrentWeapon->GetTransform().GetLocation(), FRotator::ZeroRotator);
    if (Ammo == nullptr)
	{
		return;
	}
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	Ammo->Mesh->SetWorldRotation(Rotation);
	Ammo->Fire(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));

	// 반동 시작
	RecoilStart();

	const float FinalAttackRange = GetFinalAttackRange();
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalAttackRange)),
		ECollisionChannel::ECC_GameTraceChannel2,
		Params
	);

	// 사격 후 소지 총알 감소
	int32 CurrentRoundsRemaining = EquipmentManager->DecreaseRoundsRemaining();
	LSPlayerController = LSPlayerController ? LSPlayerController : Cast<ALSPlayerController>(GetController());
	if(LSPlayerController && LSPlayerController->GetPlayerState())
	{
		// TODO: EAmmoType 다양하게
		LSPlayerController->GetPlayerState()->SetCurrentAmmo(EAmmoType::RIFLE, CurrentRoundsRemaining);
	}
	
	
	// 사격 히트 한 경우
	if (bResult)
	{
		if (HitResult.HasValidHitObjectHandle())
		{
			// LSLOG(Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
			bool bIsWeakPoint = false;
			if (HitResult.BoneName == TEXT("head"))
			{
				// LSLOG(Warning, TEXT("hit %s"), *HitResult.BoneName.ToString());
				bIsWeakPoint = true;
			}
			const float FinalAttackDamage = GetFinalAttackDamage(bIsWeakPoint);
			
			// TODO: popup 부분 함수 다로 빼기
			const FVector PopupPosition = HitResult.ImpactPoint + (GetActorLocation() - HitResult.ImpactPoint).Normalize();
			TWeakObjectPtr<ALSTextPopup> Text = GetWorld()->SpawnActor<ALSTextPopup>(PopupPosition, FRotator::ZeroRotator);
			Text->SetPopupText(FinalAttackDamage);
			Text->SetTextRotation(HitResult.ImpactPoint, HitResult.TraceStart);
			
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(FinalAttackDamage, DamageEvent, GetController(), this);
		}
	}	
}

void ALSPlayer::MeleeAttack(const FInputActionValue& Value)
{
	if (bIsMeleeAttacking == false)
	{
		LSPlayerAnim = (LSPlayerAnim == nullptr) ? Cast<ULSPlayerAnimInstance>(GetMesh()->GetAnimInstance()) : LSPlayerAnim;
		if (LSPlayerAnim != nullptr)
		{
			LSPlayerAnim->PlayAttackMontage();
		}
		bIsMeleeAttacking = true;
	}
}

void ALSPlayer::OnRunning(const FInputActionValue& Value)
{
	LSPlayerController = (LSPlayerController == nullptr) ? Cast<ALSPlayerController>(GetController()) : LSPlayerController;
	if (LSPlayerController == nullptr)
	{
		return;
	}
	LSPlayerController->SetAutoRunning(!LSPlayerController->IsAutoRunning());
	GetCharacterMovement()->MaxWalkSpeed = DefaultRunningSpeed;
}

void ALSPlayer::EndRunning(const FInputActionValue& Value)
{
	LSPlayerController = (LSPlayerController == nullptr) ? Cast<ALSPlayerController>(GetController()) : LSPlayerController;
	if (LSPlayerController == nullptr)
	{
		return;
	}
	LSPlayerController->SetAutoRunning(!LSPlayerController->IsAutoRunning());
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void ALSPlayer::OnAiming(const FInputActionValue& Value)
{
	if (SpringArm != nullptr)
	{
		ArmLengthTo = ArmLengthOnAiming;
	}
	LSPlayerAnim = (LSPlayerAnim == nullptr) ? Cast<ULSPlayerAnimInstance>(GetMesh()->GetAnimInstance()) : LSPlayerAnim;
	if (LSPlayerAnim != nullptr)
	{
		LSPlayerAnim->SetAimAnim(true);
	}
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeedOnAiming; //240.f;
}

void ALSPlayer::EndAiming(const FInputActionValue& Value)
{
	if (SpringArm != nullptr)
	{
		ArmLengthTo = ArmLengthOnIdle;
	}
	
	LSPlayerAnim = (LSPlayerAnim == nullptr) ? Cast<ULSPlayerAnimInstance>(GetMesh()->GetAnimInstance()) : LSPlayerAnim;
	if (LSPlayerAnim != nullptr)
	{
		LSPlayerAnim->SetAimAnim(false);
	}

	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed; //510.f;
}

void ALSPlayer::GrapplingHook(const FInputActionValue& Value)
{
	if (bIsGrapplingCasting || bIsGrappling)
	{
		return;
	}

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * GrapplingHookRange)),
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);

#if ENABLE_DRAW_DEBUG
	DrawDebugLine(
		GetWorld(),
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * GrapplingHookRange)), //AttackRange,
		bResult ? FColor::Green : FColor::White,
		false,
		1.0f,
		0,
		1.f
	);
#endif

	if (bResult)
	{
		if (HitResult.HasValidHitObjectHandle())
		{
			LSLOG(Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
			bIsGrapplingCasting = true;
			GetWorld()->GetTimerManager().SetTimer(
				GrapplingTimerHandle,
				this, 
				&ALSPlayer::GrappleBegin, 
				GrapplingCastingTime
			);
			GrappleToLocation = HitResult.Location;
			// 그래플링 훅 케이블
			// Cable->SetWorldLocation(GrappleToLocation);
		}
	}
}

void ALSPlayer::GrappleBegin()
{
	LaunchCharacter(GetActorUpVector() * GrapplingJumpHeight, false, false);
	bIsGrapplingCasting = false;
	bIsGrappling = true;
}

void ALSPlayer::Reload(const FInputActionValue& Value)
{
	if (bIsReloading || CurrentWeapon == nullptr)
	{
		return;
	}
	bIsReloading = true;

	LSPlayerAnim = (LSPlayerAnim == nullptr) ? Cast<ULSPlayerAnimInstance>(GetMesh()->GetAnimInstance()) : LSPlayerAnim;
	if (LSPlayerAnim != nullptr)
	{
		LSPlayerAnim->SetReloadAnim(true);
	}

	// TODO: 람다 식 나중에 빼서 구현
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&ALSPlayer::OnReloadComplete,
		CurrentWeapon->GetReloadTime(),
		false
	);

	OnReloadProgress.Broadcast(CurrentWeapon->GetReloadTime());
}

void ALSPlayer::OnReloadComplete()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}	
	bIsReloading = false;
	EAmmoType CurrentAmmoType = CurrentWeapon->GetAmmoType();
	int32 CurrentAmmo = ResourceManager->GetCurrentAmmo(CurrentAmmoType);
	int32 CurrentRounds = EquipmentManager->GetRoundsRemaining();
	int32 ReloadRounds = FMath::Clamp(CurrentWeapon->GetMagazineCapacity() - CurrentRounds,	0, CurrentAmmo); 
	CurrentAmmo = CurrentAmmo - ReloadRounds;
	EquipmentManager->SetRoundsRemaining(CurrentWeapon->GetMagazineCapacity());
	ResourceManager->SetCurrentAmmo(CurrentAmmoType, CurrentAmmo);
	LSPlayerAnim = (LSPlayerAnim == nullptr) ? Cast<ULSPlayerAnimInstance>(GetMesh()->GetAnimInstance()) : LSPlayerAnim;
	if (LSPlayerAnim != nullptr)
	{
		LSPlayerAnim->SetReloadAnim(false);
	}
	
}

// TODO: equip 1,2,3 합치기
void ALSPlayer::EquipFirstWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipFirstWeapon"));
	if (EquipmentManager->GetWeaponInstance(0) == nullptr)
	{
		return;
	}
	SetWeapon(EquipmentManager->GetWeaponInstance(0));
	EquipmentManager->SetCurrentWeaponIndex(0);
	// for test later
	// EquipmentManager->GetWeaponInstance(0)->OnAimDirChange.AddUObject(this, &ALSPlayer::ShowDebugLine);
}

void ALSPlayer::EquipSecondWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipSecondWeapon"));
	if (EquipmentManager->GetWeaponInstance(1) == nullptr)
	{
		return;
	}
	SetWeapon(EquipmentManager->GetWeaponInstance(1));
	EquipmentManager->SetCurrentWeaponIndex(1);
}

void ALSPlayer::EquipThirdWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipThirdWeapon"));
	if (EquipmentManager->GetWeaponInstance(2) == nullptr)
	{
		return;
	}
	SetWeapon(EquipmentManager->GetWeaponInstance(2));
	EquipmentManager->SetCurrentWeaponIndex(2);
}

void ALSPlayer::Interact(const FInputActionValue& Value)
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * InteractRange)),
		ECollisionChannel::ECC_GameTraceChannel4,
		Params
	);

	if (bResult)
	{
		ALSItemBox* ItemBox = Cast<ALSItemBox>(HitResult.GetActor());
		if (ItemBox)
		{
			WeaponDefinition = ItemBox->GetWeaponItem();
			InventoryManager->AddWeaponToInventory(WeaponDefinition);
		}
	}
}

void ALSPlayer::InteractProgress(const FInputActionInstance& ActionInstance)
{
	if (!bIsNearInteractableObject)
	{
		return;
	}
	SetInteractionElapsedTime(ActionInstance.GetElapsedTime());
}

void ALSPlayer::SetInteractionElapsedTime(float ElapsedTime)
{
	InteractionElapsedTime = ElapsedTime;
	// Interact Progress Bar 업데이트 함수 호출
	OnInteractProgress.Broadcast(GetInteractionElapsedRatio());
}

void ALSPlayer::InteractEnd(const FInputActionValue& Value)
{
}

void ALSPlayer::TestAct(const FInputActionValue& Value)
{
	if (InventoryManager != nullptr)
	{
		InventoryManager->SetDefaultWeapon();
	}
	RecoilStart();
}

void ALSPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InventoryManager->SetEquipmentComponent(EquipmentManager);

	LSPlayerAnim = Cast<ULSPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (LSPlayerAnim != nullptr)
	{
		if (DefenseManager != nullptr)
		{
			DefenseManager->OnHPIsZero.AddLambda([this]() -> void {
				LSPlayerAnim->SetDeadAnim();
				SetActorEnableCollision(false);
			});
		}
		// LSPlayerAnim->OnAttackHitCheck.AddUObject(this, &ALSPlayer::AttackCheck);
		LSPlayerAnim->OnMontageEnded.AddDynamic(this, &ALSPlayer::OnAttackMontageEnded);
	}
}

bool ALSPlayer::CanShoot(EAmmoType AmmoType)
{
	if (bIsReloading)
	{
		return false;
	}

	if (EquipmentManager == nullptr)
	{
		return false;
	}

	//  TODO: weapon 의 magazine ammo로 바꾸기
	if (EquipmentManager->WeaponInstanceList.Num() <= 0 || EquipmentManager->CurrentWeaponInstance == nullptr)
	{
		return false;
	}

	if (EquipmentManager->GetRoundsRemaining() == 0)
	{
	 	return false;
	}

	return true;
}

float ALSPlayer::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	//LSLOG(Warning, TEXT("Actor %s took damage : %f"), *GetName(), FinalDamage);
	
	if (DefenseManager != nullptr)
	{
		DefenseManager->SetDamage(FinalDamage);
	}

	if (CurrentState == ECharacterState::DEAD)
	{
		// TODO
	}

	return FinalDamage;
}

void ALSPlayer::SetWeapon(ALSWeaponInstance* NewWeapon)
{
	if (NewWeapon == nullptr)
	{
		return;
	}
	if (CurrentWeapon != nullptr)
	{
		// TODO: 무기 장착 해제 관련 메서드 호출
		CurrentWeapon->SetActorHiddenInGame(true);
	}
	
	FName WeaponSocket(TEXT("weapon_r_socket"));
	if (RootComponent && GetMesh())
	{
		NewWeapon->SetActorHiddenInGame(false);
		NewWeapon->AttachToComponent(
			GetMesh(), 
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
			WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
		// fire rate 설정
		SetShootInputInterval(0.2f);//(CurrentWeapon->GetFireRate() / 1800.f);

		LSPlayerAnim = Cast<ULSPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (LSPlayerAnim && CurrentWeapon->GetBaseWeaponDefinition())
		{
			LSPlayerAnim->SetWeaponType(CurrentWeapon->GetBaseWeaponDefinition()->GetWeaponType());
		}
	}
}

// montage test 
void ALSPlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsMeleeAttacking = false;
	OnAttackEnd.Broadcast();
}

float ALSPlayer::GetFinalAttackDamage(bool bIsWeakPoint) const
{
	if (CurrentWeapon == nullptr)
	{
		return 0;
	}
	float AttackDamage = CurrentWeapon->GetFinalDamage();
	// 치명타인 경우 약점 공격으로 인한 데미지 증가가 없음
	float RandValue = FMath::FRandRange(0.0f, 1.0f);
	float CriticalHitChance = CurrentWeapon->GetCriticalHitChance();
	if (RandValue <= CriticalHitChance)
	{
		AttackDamage *= CurrentWeapon->GetCriticalHitMultiplier();
	}
	// 약점 공격시
	else if (bIsWeakPoint)
	{
		// TODO : 수치 변수로 빼기
		AttackDamage *= 1.2f;
	}

	return AttackDamage; 
}

void ALSPlayer::InteractCheck()
{
	// TODO: 1. interact UI 팝업, 2. interact progress bar 구현
	if (!bIsNearInteractableObject)
	{
		return;
	}
	const float FinalInteractRange = GetFinalInteractRange();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalInteractRange)),
		ECollisionChannel::ECC_GameTraceChannel3,
		Params
	);	

	if (bResult)
	{
		
	}
}

void ALSPlayer::ShowDebugLine(FVector Dir)
{
	DrawDebugLine(
		GetWorld(),
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + Dir * 1000.f), //AttackRange,
		FColor::Red,
		false,
		1.0f,
		0,
		1.f
	);	
}

void ALSPlayer::SetIsNearInteractableObject(bool Value)
{
	// LSLOG(Warning, TEXT("Player is overlapping with interactable object"));
	// TODO: 두 개 이상의 상호작용 물체와 겹치고 있는 경우 고려하기
	bIsNearInteractableObject = Value;
	OnEnableToInteract.Broadcast(bIsNearInteractableObject);
}


void ALSPlayer::RecoilStart()
{
	if (RecoilCurve == nullptr)
	{
		return;
	}
	// rotator 변수 초기화 - 반동 시작
	PlayerDeltaRot = FRotator(0.0f, 0.0f, 0.0f);
	RecoilDeltaRot = FRotator(0.0f, 0.0f, 0.0f);
	Del = FRotator(0.0f, 0.0f, 0.0f);
	LSPlayerController = (LSPlayerController == nullptr) ? Cast<ALSPlayerController>(GetController()) : LSPlayerController;
	if (LSPlayerController != nullptr)
	{
		RecoilStartRot = LSPlayerController->GetControlRotation();
	}
	bIsFiring = true;
	bRecoil = true;
	bRecoilRecovery = false;

	// 반동 중단 타이머
	// TODO : 우선 10초로 잡아 뒀으니 나중에 총기 스탯이랑 연계하기	
	GetWorld()->GetTimerManager().SetTimer(
		FireTimer, 
		this, 
		&ALSPlayer::RecoilTimerFunction, 
		10.0f, 
		false
	);
}

void ALSPlayer::RecoilStop()
{
	bIsFiring = false;
	// GetWorld()->GetTimerManager().SetTimer(RecoveryTimer, this, &ALSPlayer::RecoveryTimerFunction, 1.0f, false);
}

void ALSPlayer::RecoveryStart()
{
	LSPlayerController = (LSPlayerController == nullptr) ? Cast<ALSPlayerController>(GetController()) : LSPlayerController;
	if (LSPlayerController == nullptr)
	{
		return;
	}
 	if (LSPlayerController->GetControlRotation().Pitch > RecoilStartRot.Pitch)
	{
		bRecoilRecovery = true;
		GetWorld()->GetTimerManager().SetTimer(
			RecoveryTimer, 
			this, 
			&ALSPlayer::RecoveryTimerFunction, 
			RecoveryTime, 
			false
		);
    }
}

void ALSPlayer::RecoveryTimerFunction()
{
	bRecoilRecovery = false;
}

void ALSPlayer::RecoilTimerFunction()
{
	bRecoil = false;
	GetWorld()->GetTimerManager().PauseTimer(FireTimer);
}

void ALSPlayer::RecoilTick(float DeltaTime)
{
	FVector RecoilVec;
	if (bRecoil)
	{
	  	// 회전 계산
		Recoiltime = GetWorld()->GetTimerManager().GetTimerElapsed(FireTimer);
		RecoilVec = RecoilCurve->GetVectorValue(Recoiltime);
		Del.Roll = 0;
		Del.Pitch = (RecoilVec.Y);
		Del.Yaw = (RecoilVec.Z);
		PlayerDeltaRot = LSPlayerController->GetControlRotation() - RecoilStartRot - RecoilDeltaRot;
		LSPlayerController->SetControlRotation(RecoilStartRot + PlayerDeltaRot + Del);
		RecoilDeltaRot = Del;

		if (bIsFiring)// (!bIsFiring)
		{
			// 반동 시작되고 나서 시간이 탄창 내 탄약을 모두 소비하는 시간 보다 더 지난 경우
			if (Recoiltime > FireRate)
			{
				GetWorld()->GetTimerManager().ClearTimer(FireTimer);
				RecoilStop();
				bRecoil = false;
				RecoveryStart();
			}
		}
	}
	else if (bRecoilRecovery)
	{
	    //Recoil resetting
		FRotator TempRot = LSPlayerController->GetControlRotation();
		if (TempRot.Pitch >= RecoilStartRot.Pitch)
		{
			LSPlayerController->SetControlRotation(UKismetMathLibrary::RInterpTo(GetControlRotation(), GetControlRotation() - RecoilDeltaRot, DeltaTime, 10.0f));
			RecoilDeltaRot = RecoilDeltaRot + (GetControlRotation() - TempRot);
		}
		else
		{
			RecoveryTimer.Invalidate();
		}
	}
}

float ALSPlayer::GetFinalAttackRange() const
{
	return CurrentWeapon ? CurrentWeapon->GetMaxRange() : DefaultAttackRange;
}

void ALSPlayer::SetShootInputInterval(const float InputInterval)
{
	if(ShootInputTriggerPulse)
	{
		ShootInputTriggerPulse->Interval = InputInterval;
	}
}

/*
void ALSPlayer::SetShootInputInterval(float InputInterval)
{
	LSCHECK(ShootInputTriggerPulse != nullptr);
	ShootInputTriggerPulse->Interval = InputInterval;
	LSLOG(Warning, TEXT("Shoot Input Interval : %f"), ShootInputTriggerPulse->Interval);
}*/