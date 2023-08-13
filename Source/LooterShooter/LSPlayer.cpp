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
#include "LSCharacterStatComponent.h"
// #include "Components/WidgetComponent.h"
// #include "LSCharacterWidget.h"
#include "LSAnimInstance.h"
#include "LSPlayerController.h"
#include "LSPlayerState.h"
#include "LSGameInstance.h"
#include "LSHUDWidget.h"
#include "LSDefenseComponent.h"
#include "LSEquipmentComponent.h"
#include "Math/RotationMatrix.h"
#include "LSTextPopup.h"
#include "LSAutoLootItem.h"
#include "LSWeaponInstance.h"
#include "LSInventoryComponent.h"
#include "LSItemBox.h"
#include "LSWeaponDefinition.h"

#include "DrawDebugHelpers.h"

// Sets default values
ALSPlayer::ALSPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	ArmLengthTo = ArmLengthOnIdle; // 450.0f
	SpringArm->TargetArmLength = ArmLengthTo;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0.0f, 90.0f, 90.0f));

	// max jump height
	GetCharacterMovement()->JumpZVelocity = JumpHeight; // 450.0f

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_QUINN(TEXT("/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn"));
	if ( SKM_QUINN.Succeeded() )
	{
		GetMesh()->SetSkeletalMesh( SKM_QUINN.Object );
	}
	else
	{
		LSLOG_S(Error);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> RIFLE_ANIM(TEXT("/Game/LS/Animations/RifleAnimBlueprint.RifleAnimBlueprint_C"));
	if (RIFLE_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(RIFLE_ANIM.Class);
	}

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
		LSCHECK(ShootAction->Triggers.Num() > 0);
		TObjectPtr<UInputTriggerPulse> ShootInputTrigger = Cast<UInputTriggerPulse>(ShootAction->Triggers[0]);
		LSCHECK(nullptr != ShootInputTrigger);
		// fire rate
		ShootInputTrigger->Interval = 0.1f;
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

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_TEST(TEXT("/Game/LS/Input/Actions/IA_TESTKEY.IA_TESTKEY"));
	if (IA_TEST.Succeeded())
	{
		TestAction = IA_TEST.Object;
	}
	///////////////////////////////////////////

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LSCharacter"));
	SetActorHiddenInGame(true);
	SetCanBeDamaged(false);
}

// Called when the game starts or when spawned
void ALSPlayer::BeginPlay()
{
	Super::BeginPlay();
	LSPlayerController = Cast<ALSPlayerController>(GetController());
	LSCHECK(nullptr != LSPlayerController);

	ALSPlayerState *LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
	LSCHECK(nullptr != LSPlayerState);

	LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());
	LSCHECK(nullptr != LSGameInstance);

	CharacterAssetToLoad.SetPath(TEXT("/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn"));
	AssetStreamingHandle = LSGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ALSPlayer::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);

	DefenseManager->OnHPIsZero.AddUObject(this, &ALSPlayer::SetCharacterStateDead);
	LSCHECK(Camera != nullptr);

	ToAimDirection = FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X);
}

void ALSPlayer::SetCharacterState(ECharacterState NewState)
{
	LSCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	// 캐릭터 비동기 로딩 상태
	case ECharacterState::LOADING:
	{
		DisableInput(LSPlayerController);
		LSPlayerController->GetHUDWidget()->BindDefenseComponent(DefenseManager);
		ALSPlayerState *LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
		LSCHECK(nullptr != LSPlayerState);
		CharacterStat->SetNewLevel(LSPlayerState->GetCharacterLevel());
		SetActorHiddenInGame(true);
		SetCanBeDamaged(false);
		break;
	}
	// 캐릭터 로딩이 완료되어 씬 상에 표현되고 동작 가능한 상태
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		SetCanBeDamaged(true);
		CharacterStat->OnHPIsZero.AddLambda([this]() -> void { 
			SetCharacterState(ECharacterState::DEAD); });
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
		EnableInput(LSPlayerController);
		break;
	}
	// 캐릭터의 HP가 0 이하가 되어 죽은 상태
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		LSAnim->SetDeadAnim();
		SetCanBeDamaged(false);
		DisableInput(LSPlayerController);

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
			[this]() -> void { LSPlayerController->ShowResultUI(); }),
			DeadTimer, false);
	}
	}
}

void ALSPlayer::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
	LSCHECK(nullptr != AssetLoaded);
	GetMesh()->SetSkeletalMesh(AssetLoaded);
	SetCharacterState(ECharacterState::READY);
}

ECharacterState ALSPlayer::GetCharacterState() const
{
	return CurrentState;
}

void ALSPlayer::SetCharacterStateDead()
{
	SetCharacterState(ECharacterState::DEAD);
}

// Called every frame
void ALSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthChangingSpeed);

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
}

// Called to bind functionality to input
void ALSPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	LSCHECK (PlayerController != nullptr);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	LSCHECK (Subsystem != nullptr);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	LSCHECK(EnhancedInputComponent != nullptr); 

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
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ALSPlayer::Interact);
	EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ALSPlayer::TestAct);
}

void ALSPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);//이동
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);//이동
}

void ALSPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	LSCHECK(Controller != nullptr)

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ALSPlayer::Shoot(const FInputActionValue& Value)
{	
	//AttackCheck();
	LSCHECK(CurrentWeapon != nullptr);
	// TODO : ammo type 늘리기
	if(!CanShoot(EAmmoType::RIFLE))
	{
		LSLOG(Warning, TEXT("CANNOT Shoot"));
		return;
	}

	float FinalAttackRange = GetFinalAttackRange();
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalAttackRange)),
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);

#if ENABLE_DRAW_DEBUG
	DrawDebugLine(
		GetWorld(),
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalAttackRange)), //AttackRange,
		bResult ? FColor::Green : FColor::White,
		true,
		1.0f,
		0,
		1.f);
#endif

	FVector TempVector = CurrentWeapon->CalculateRecoil(
		FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X),
		CurrentWeapon->GetCurrentSpreadAngle());
	ShowDebugLine(TempVector);
	
	EquipmentManager->DecreaseRoundsRemaining();
	// 반동에 따른 조준점 이동
	GetController()->SetControlRotation(TempVector.Rotation());
	// 사격 히트
	if (bResult)
	{
		if (HitResult.HasValidHitObjectHandle())
		{
			LSLOG(Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
			float FinalAttackDamage = GetFinalAttackDamage();
			FVector PopupPosition = HitResult.ImpactPoint + (GetActorLocation() - HitResult.ImpactPoint).Normalize();
			TWeakObjectPtr<ALSTextPopup> Text = GetWorld()->SpawnActor<ALSTextPopup>(PopupPosition, FRotator::ZeroRotator);
			Text->SetPopupText(FinalAttackDamage);
			Text->SetTextRotation(HitResult.ImpactPoint , HitResult.TraceStart);
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(FinalAttackDamage, DamageEvent, GetController(), this);
		}
	}	
}

void ALSPlayer::MeleeAttack(const FInputActionValue& Value)
{
	if (bIsMeleeAttacking) return;
	LSAnim->PlayAttackMontage();
	bIsMeleeAttacking = true;
}

void ALSPlayer::OnRunning(const FInputActionValue& Value)
{
	LSCHECK(nullptr != LSPlayerController);
	LSPlayerController->SetIsAutoRunning(!LSPlayerController->GetIsAutoRunning());
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
}

void ALSPlayer::EndRunning(const FInputActionValue& Value)
{
	LSCHECK(nullptr != LSPlayerController);
	LSPlayerController->SetIsAutoRunning(!LSPlayerController->GetIsAutoRunning());
	GetCharacterMovement()->MaxWalkSpeed = 510.f;
}

void ALSPlayer::OnAiming(const FInputActionValue& Value)
{
	LSCHECK(nullptr != SpringArm);
	ArmLengthTo = ArmLengthOnAiming;
	LSAnim->SetAimAnim(true);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeedOnAiming; //240.f;
}

void ALSPlayer::EndAiming(const FInputActionValue& Value)
{
	LSCHECK(nullptr != SpringArm);
	ArmLengthTo = ArmLengthOnIdle;
	LSAnim->SetAimAnim(false);
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed; //510.f;
}

void ALSPlayer::GrapplingHook(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("GrapplingHook"));
	if(bIsGrapplingCasting||bIsGrappling)
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
			GetWorld()->GetTimerManager().SetTimer(GrapplingTimerHandle, this, &ALSPlayer::GrappleBegin, GrapplingCastingTime);
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
	LSLOG(Warning, TEXT("Reloading Started"));
	if(bIsReloading)
	{
		return;
	}
	LSCHECK(nullptr != CurrentWeapon);
	bIsReloading = true;
	LSAnim->SetReloadAnim(true);
	// TODO: 람다 식 나중에 빼서 구현
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
			bIsReloading = false;
			int32 CurrentRounds = EquipmentManager->GetRoundsRemaining();
			int32 ReloadRounds = FMath::Clamp(CurrentWeapon->GetMagazineCapacity() - CurrentRounds, 0, ResourceManager->GetCurrentAmmo(EAmmoType::RIFLE)); 
			EquipmentManager->SetRoundsRemaining(CurrentWeapon->GetMagazineCapacity());
			ResourceManager->SetCurrentAmmo(EAmmoType::RIFLE, -ReloadRounds);
			LSAnim->SetReloadAnim(false);
			LSLOG(Warning, TEXT("RELoading Completed"));
		}), CurrentWeapon->GetReloadTime(), false);
}

void ALSPlayer::EquipFirstWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipFirstWeapon"));
	LSCHECK(nullptr != EquipmentManager->GetWeaponInstance(0));
	SetWeapon(EquipmentManager->GetWeaponInstance(0));
	EquipmentManager->SetCurrentWeaponIndex(0);

	// for test later
	EquipmentManager->GetWeaponInstance(0)->OnAimDirChange.AddUObject(this, &ALSPlayer::ShowDebugLine);
}

void ALSPlayer::EquipSecondWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipSecondWeapon"));
	LSCHECK(nullptr != EquipmentManager->GetWeaponInstance(1));
	SetWeapon(EquipmentManager->GetWeaponInstance(1));
	EquipmentManager->SetCurrentWeaponIndex(1);
}

void ALSPlayer::EquipThirdWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipThirdWeapon"));
	LSCHECK(nullptr != EquipmentManager->GetWeaponInstance(2));
	SetWeapon(EquipmentManager->GetWeaponInstance(2));
	EquipmentManager->SetCurrentWeaponIndex(2);
}

void ALSPlayer::Interact(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("Interact"));

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * InteractRange)),
		ECollisionChannel::ECC_GameTraceChannel4,
		Params
	);

	if(bResult)
	{
		LSLOG(Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
		LSLOG(Warning, TEXT("Hit TraceChannel3 -> ItemBox"));
		ALSItemBox* ItemBox = Cast<ALSItemBox>(HitResult.GetActor());
		LSCHECK(ItemBox != nullptr);
		LSLOG(Warning, TEXT("Cast Complete"));
		//ItemBox->SetWeaponItem(this);
		LSLOG(Warning, TEXT("Set Weapon complete"));
		// ULSWeaponDefinition* WeaponDefinition = ItemBox->GetWeaponItem();
		WeaponDefinition = ItemBox->GetWeaponItem();
		LSLOG(Warning, TEXT("WeaponDefinite"));
		InventoryManager->AddWeaponToInventory(WeaponDefinition);
	}

}

void ALSPlayer::TestAct(const FInputActionValue& Value)
{
	InventoryManager->SetDefaultWeapon();
}

void ALSPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InventoryManager->SetEquipmentComponent(EquipmentManager);

	LSAnim = Cast<ULSAnimInstance>(GetMesh()->GetAnimInstance());
	LSCHECK(nullptr != LSAnim);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		LSLOG(Warning, TEXT("OnHPIsZero"));
		LSAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	});

	// LSAnim->OnAttackHitCheck.AddUObject(this, &ALSPlayer::AttackCheck);
	LSAnim->OnMontageEnded.AddDynamic(this, &ALSPlayer::OnAttackMontageEnded);
}

bool ALSPlayer::CanShoot(EAmmoType AmmoType)
{
	if(bIsReloading)
	{
		LSLOG(Warning, TEXT("IsReloading"));
		return false;
	}
	//  TODO: weapon 의 magazine ammo로 바꾸기
	LSCHECK(EquipmentManager->WeaponInstanceList.Num() > 0 &&
			EquipmentManager->CurrentWeaponInstance != nullptr, false);
	if(EquipmentManager->GetRoundsRemaining() == 0)
	{
		LSLOG(Warning, TEXT("No Ammo"));
	 	return false;
	}
	return true;
}

float ALSPlayer::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	LSLOG(Warning, TEXT("Actor %s took damage : %f"), *GetName(), FinalDamage);
	
	DefenseManager->SetDamage(FinalDamage);

	if (CurrentState == ECharacterState::DEAD)
	{
		// TODO
	}

	return FinalDamage;
}

bool ALSPlayer::CanSetWeapon()
{
	// TODO: (nullptr == CurrentWeapon);
	return true; 
}

void ALSPlayer::SetWeapon(ALSWeaponInstance* NewWeapon)
{
	LSCHECK(nullptr != NewWeapon);
	if (nullptr != CurrentWeapon)
	{
		// TODO: 무기 장착 해제 관련 메서드 호출
	}
	
	FName WeaponSocket(TEXT("weapon_r_socket"));
	LSCHECK(nullptr != RootComponent);
	LSCHECK(nullptr != GetMesh());
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
}

// montage test 
void ALSPlayer::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	LSCHECK(bIsMeleeAttacking);
	bIsMeleeAttacking = false;

	OnAttackEnd.Broadcast();
}

/*
int32 ALSPlayer::GetExp() const
{
	// TODO: 몬스터 -> GetExp();
	return 5;
}
*/

float ALSPlayer::GetFinalAttackRange() const
{
	LSCHECK(nullptr != CurrentWeapon, 1000.f);
	return CurrentWeapon->GetMaxRange();
}

float ALSPlayer::GetFinalInteractRange() const
{
	return InteractRange;
}

float ALSPlayer::GetFinalAttackDamage() const
{
	LSCHECK(nullptr != CurrentWeapon, -1.f);
	float AttackDamage = CurrentWeapon->GetFinalDamage();
	return AttackDamage; 
}

void ALSPlayer::InteractCheck()
{
	// TODO: 1. interact UI popup, 2. interact progress

	if(!bIsNearInteractableObject)
	{
		return;
	}
	float FinalInteractRange = GetFinalInteractRange();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalInteractRange)),
		ECollisionChannel::ECC_GameTraceChannel3,
		Params
	);	

	if(bResult)
	{
		LSLOG(Warning, TEXT("HIT Box"));
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