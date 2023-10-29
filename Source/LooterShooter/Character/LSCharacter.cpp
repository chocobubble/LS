// Fill out your copyright notice in the Description page of Project Settings.

#include "LSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "InputActionValue.h"
/** @deprecated: 지우기 */
#include "LSWeapon.h"
#include "LSCharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "LSCharacterWidget.h"
#include "LSAIController.h"
#include "LSAnimInstance.h"
#include "LSPlayerController.h"
#include "LSPlayerState.h"
#include "LSGameInstance.h"
#include "LSHUDWidget.h"
#include "LSGameMode.h"
#include "Math/RotationMatrix.h"
#include "LSResourceManageComponent.h"
#include "LSDefenseComponent.h"
#include "LSEquipmentComponent.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "LSTextPopup.h"
#include "LSAutoLootItem.h"
#include "LSWeaponInstance.h"
#include "LSInventoryComponent.h"
#include "LSItemBox.h"
#include "LSWeaponDefinition.h"

/** @TODO: 그래플링 훅 */
// #include "CableComponent.h"

ALSCharacter::ALSCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	// 카메라, 카메라의 SpringArm 컴포넌트 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// 캐릭터의 레벨, 경험치 등 저장되어야 하는 스탯 관리 컴포넌트
	CharacterStat = CreateDefaultSubobject<ULSCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	// 탄환 수, 골드량 등의 자원 관리 컴포넌트
	ResourceManager = CreateDefaultSubobject<ULSResourceManageComponent>(TEXT("RESOURCEMANAGER"));

	// HP, Shield, MP, 방어력 등 관리 컴포넌트
	DefenseManager = CreateDefaultSubobject<ULSDefenseComponent>(TEXT("DEFENSEMANAGER"));

	// 장착한 장비 아이템 관리 컴포넌트
	EquipmentManager = CreateDefaultSubobject<ULSEquipmentComponent>(TEXT("EQUIPMENT"));

	// 인벤토리 내 아이템 관리 컴포넌트
	InventoryManager = CreateDefaultSubobject<ULSInventoryComponent>(TEXT("INVENTORY"));

	// 그래플링 훅 구현을 위한 케이블 컴포넌트 
	// Cable = CreateDefaultSubobject<ULSCableComponent>(TEXT("CABLE"));
	
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));	

	SpringArm->SetupAttachment(GetCapsuleComponent());
	
	Camera->SetupAttachment(SpringArm);
	
	/** @TODO: 삭제 */
	HPBarWidget->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	ArmLengthTo = ArmLengthOnIdle;
	SpringArm->TargetArmLength = ArmLengthTo;  //400.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0.0f, 90.0f, 90.0f));
	GetCharacterMovement()->JumpZVelocity = 450.0f;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT_KBM(TEXT("/Game/LS/Input/IMC_Default_KBM.IMC_Default_KBM"));
	if ( IMC_DEFAULT_KBM.Succeeded())
	{
		InputMapping = IMC_DEFAULT_KBM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVE(TEXT("/Game/LS/Input/Actions/IA_Move.IA_Move"));
	if ( IA_MOVE.Succeeded())
	{
		MoveAction = IA_MOVE.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP(TEXT("/Game/LS/Input/Actions/IA_Jump.IA_Jump"));
	if ( IA_JUMP.Succeeded())
	{
		JumpAction = IA_JUMP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Game/LS/Input/Actions/IA_LOOK.IA_LOOK"));
	if ( IA_LOOK.Succeeded())
	{
		LookAction = IA_LOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SHOOT(TEXT("/Game/LS/Input/Actions/IA_SHOOT.IA_SHOOT"));
	if ( IA_SHOOT.Succeeded())
	{
		ShootAction = IA_SHOOT.Object;
		if (ShootAction->Triggers.Num() > 0)
		{
			TObjectPtr<UInputTriggerPulse> ShootInputTrigger = Cast<UInputTriggerPulse>(ShootAction->Triggers[0]);
			if (ShootInputTrigger)
			{
				// 연사 속도
				ShootInputTrigger->Interval = 0.1f;
			}
		}
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MELEE(TEXT("/Game/LS/Input/Actions/IA_MELEE.IA_MELEE"));
	if ( IA_MELEE.Succeeded())
	{
		MeleeAttackAction = IA_MELEE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_AUTO_RUN(TEXT("/Game/LS/Input/Actions/IA_Auto_Run.IA_Auto_Run"));
	if ( IA_AUTO_RUN.Succeeded())
	{
		AutoRunAction = IA_AUTO_RUN.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_AIM(TEXT("/Game/LS/Input/Actions/IA_Aim.IA_Aim"));
	if ( IA_AIM.Succeeded())
	{
		AimAction = IA_AIM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_GRAPPLING_HOOK(TEXT("/Game/LS/Input/Actions/IA_GrapplingHook.IA_GrapplingHook"));
	if ( IA_GRAPPLING_HOOK.Succeeded())
	{
		GrapplingHookAction = IA_GRAPPLING_HOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_RELOAD(TEXT("/Game/LS/Input/Actions/IA_Reload.IA_Reload"));
	if ( IA_RELOAD.Succeeded())
	{
		ReloadAction = IA_RELOAD.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_EQUIP_FIRST_WEAPON(TEXT("/Game/LS/Input/Actions/IA_FirstWeapon.IA_FirstWeapon"));
	if ( IA_EQUIP_FIRST_WEAPON.Succeeded())
	{
		EquipFirstWeaponAction = IA_EQUIP_FIRST_WEAPON.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_EQUIP_SECOND_WEAPON(TEXT("/Game/LS/Input/Actions/IA_SecondWeapon.IA_SecondWeapon"));
	if ( IA_EQUIP_SECOND_WEAPON.Succeeded())
	{
		EquipSecondWeaponAction = IA_EQUIP_SECOND_WEAPON.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_EQUIP_THIRD_WEAPON(TEXT("/Game/LS/Input/Actions/IA_ThirdWeapon.IA_ThirdWeapon"));
	if ( IA_EQUIP_THIRD_WEAPON.Succeeded())
	{
		EquipThirdWeaponAction = IA_EQUIP_THIRD_WEAPON.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_INTERACT(TEXT("/Game/LS/Input/Actions/IA_Interact.IA_Interact"));
	if ( IA_INTERACT.Succeeded())
	{
		InteractAction = IA_INTERACT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_TEST(TEXT("/Game/LS/Input/Actions/IA_TESTKEY.IA_TESTKEY"));
	if ( IA_TEST.Succeeded())
	{
		TestAction = IA_TEST.Object;
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LSCharacter"));

	/** @TODO: 삭제 */
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	/** @TODO: 삭제 */
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/LS/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	
	/** @TODO: 삭제 */
	AIControllerClass = ALSAIController::StaticClass();
	/** @TODO: 삭제 */
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bIsAttacking = false;

	SetActorHiddenInGame(true);
	/** @TODO: 삭제 */
	HPBarWidget->SetHiddenInGame(true);
	SetCanBeDamaged(false);
}

void ALSCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 구분하기
	bIsPlayer = IsPlayerControlled();
	if (bIsPlayer)
	{
		LSPlayerController = Cast<ALSPlayerController>(GetController());
		LSCHECK(nullptr != LSPlayerController);
	}
	else
	{
		LSAIController = Cast<ALSAIController>(GetController());
		LSCHECK(nullptr != LSAIController);
	}
	if (bIsPlayer)
	{
		auto LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
		LSCHECK(nullptr != LSPlayerState);
	}
	else
	{
	}
	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	CharacterAssetToLoad.SetPath(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn'"));
	LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());
	LSCHECK(nullptr != LSGameInstance);
	AssetStreamingHandle = LSGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ALSCharacter::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);

	DefenseManager->OnHPIsZero.AddUObject(this, &ALSCharacter::SetCharacterStateDead);
	LSCHECK(Camera != nullptr);
	ToAimDirection = FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X);
}

void ALSCharacter::SetCharacterState(ECharacterState NewState)
{
	LSCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	// 캐릭터 비동기 로딩 상태
	case ECharacterState::LOADING:
	{
		if (bIsPlayer)
		{
			DisableInput(LSPlayerController);
			LSPlayerController->GetHUDWidget()->BindDefenseComponent(DefenseManager);
			ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
			LSCHECK(nullptr != LSPlayerState);
			CharacterStat->SetNewLevel(LSPlayerState->GetCharacterLevel());
		}
		else
		{
			ALSGameMode* LSGameMode = Cast<ALSGameMode>(GetWorld()->GetAuthGameMode());
			LSCHECK(nullptr != LSGameMode);
			int32 CurrentPlayerLevel = LSGameMode->GetPlayerLevel();
			LSLOG(Warning, TEXT("New NPC Level : %d"), CurrentPlayerLevel);
			CharacterStat->SetNewLevel(CurrentPlayerLevel);
		}
		SetActorHiddenInGame(true);
		HPBarWidget->SetHiddenInGame(true);
		SetCanBeDamaged(false);
		break;
	}
	// 캐릭터 로딩이 완료되어 씬 상에 표현되고 동작 가능한 상태
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
		CharacterWidget->BindDefenseComponent(DefenseManager);

		if (bIsPlayer)
		{
			GetCharacterMovement()->MaxWalkSpeed = 510.0f;
			EnableInput(LSPlayerController);
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
			LSAIController->RunAI();
		}
		break;
	}
	// 캐릭터의 HP가 0 이하가 되어 죽은 상태
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		LSAnim->SetDeadAnim();
		SetCanBeDamaged(false);
		
		if (bIsPlayer)
		{
			DisableInput(LSPlayerController);
		}
		else
		{
			LSAIController->StopAI();
		}

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
			if (bIsPlayer)
			{
				LSPlayerController->ShowResultUI();
			}
			else
			{
				DropItem();
				Destroy();
			}
		}), DeadTimer, false);
	}
	}
}

ECharacterState ALSCharacter::GetCharacterState() const
{
	return CurrentState;
}

void ALSCharacter::Tick(float DeltaTime)
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

void ALSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController == nullptr) 
	{
		LSLOG(Warning, TEXT("PlayerController nullptr"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		LSLOG(Warning, TEXT("Subsystem nullptr"));
		return;
	}
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent == nullptr) 
	{
		LSLOG(Warning, TEXT("Enhanced Input Component nullptr"));
		return;
	}
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALSCharacter::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALSCharacter::Jump);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALSCharacter::Look);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ALSCharacter::Shoot);
	EnhancedInputComponent->BindAction(MeleeAttackAction, ETriggerEvent::Triggered, this, &ALSCharacter::MeleeAttack);
	EnhancedInputComponent->BindAction(AutoRunAction, ETriggerEvent::Started, this, &ALSCharacter::OnRunning);
	EnhancedInputComponent->BindAction(AutoRunAction, ETriggerEvent::Completed, this, &ALSCharacter::EndRunning);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ALSCharacter::OnAiming);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ALSCharacter::EndAiming);
	EnhancedInputComponent->BindAction(GrapplingHookAction, ETriggerEvent::Triggered, this, &ALSCharacter::GrapplingHook);
	EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ALSCharacter::Reload);
	EnhancedInputComponent->BindAction(EquipFirstWeaponAction, ETriggerEvent::Triggered, this, &ALSCharacter::EquipFirstWeapon);
	EnhancedInputComponent->BindAction(EquipSecondWeaponAction, ETriggerEvent::Triggered, this, &ALSCharacter::EquipSecondWeapon);
	EnhancedInputComponent->BindAction(EquipThirdWeaponAction, ETriggerEvent::Triggered, this, &ALSCharacter::EquipThirdWeapon);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ALSCharacter::Interact);
	EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ALSCharacter::TestAct);
}

void ALSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);//이동
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);//이동
}

void ALSCharacter::JumpAct(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump action input"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump action not input"));
	}
}

void ALSCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	else
	{
		LSLOG(Warning, TEXT("PlayerController is nullptr 1"));
	}
}

void ALSCharacter::Shoot(const FInputActionValue& Value)
{
	AttackCheck();
	LSLOG(Warning, TEXT("Shoot"));
}

void ALSCharacter::MeleeAttack(const FInputActionValue& Value)
{
	if (bIsAttacking) return;
	LSAnim->PlayAttackMontage();
	bIsAttacking = true;
}

void ALSCharacter::OnRunning(const FInputActionValue& Value)
{
	LSCHECK(nullptr != LSPlayerController);
	LSPlayerController->SetIsAutoRunning(!LSPlayerController->GetIsAutoRunning());
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
}

void ALSCharacter::EndRunning(const FInputActionValue& Value)
{
	LSCHECK(nullptr != LSPlayerController);
	LSPlayerController->SetIsAutoRunning(!LSPlayerController->GetIsAutoRunning());
	GetCharacterMovement()->MaxWalkSpeed = 510.f;
}

void ALSCharacter::OnAiming(const FInputActionValue& Value)
{
	LSCHECK(nullptr != SpringArm);
	LSLOG(Warning, TEXT("OnAiming"));
	ArmLengthTo = ArmLengthOnAiming;
	LSAnim->SetAimAnim(true);
	GetCharacterMovement()->MaxWalkSpeed = 240.f;
}

void ALSCharacter::EndAiming(const FInputActionValue& Value)
{
	LSCHECK(nullptr != SpringArm);
	LSLOG(Warning, TEXT("EndAiming"));
	ArmLengthTo = ArmLengthOnIdle;
	LSAnim->SetAimAnim(false);
	GetCharacterMovement()->MaxWalkSpeed = 510.f;
}

void ALSCharacter::GrapplingHook(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("GrapplingHook"));
	if (bIsGrapplingCasting||bIsGrappling)
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
			GetWorld()->GetTimerManager().SetTimer(GrapplingTimerHandle, this, &ALSCharacter::GrappleBegin, GrapplingCastingTime);
	GrappleToLocation = HitResult.Location;
			// 그래플링 훅 케이블
			// Cable->SetWorldLocation(GrappleToLocation);
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

void ALSCharacter::GrappleBegin()
{
	LaunchCharacter(GetActorUpVector() * GrapplingJumpHeight, false, false);
	bIsGrapplingCasting = false;
	bIsGrappling = true;
}

void ALSCharacter::Reload(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("Reloading Started"));
	if (bIsReloading)
	{
		return;
	}
	LSCHECK(nullptr != EquipmentManager->GetCurrentWeaponInstance());
	bIsReloading = true;
	LSAnim->SetReloadAnim(true);
	// TODO: 람다 식 나중에 빼서 구현
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
			bIsReloading = false;
			int32 CurrentRounds = EquipmentManager->GetRoundsRemaining();
			int32 ReloadRounds = FMath::Clamp(EquipmentManager->GetCurrentWeaponInstance()->GetMagazineCapacity() - CurrentRounds, 0, ResourceManager->GetCurrentAmmo(EAmmoType::RIFLE)); 
			EquipmentManager->SetRoundsRemaining(EquipmentManager->GetCurrentWeaponInstance()->GetMagazineCapacity());
			ResourceManager->SetCurrentAmmo(EAmmoType::RIFLE, -ReloadRounds);
			LSAnim->SetReloadAnim(false);
			LSLOG(Warning, TEXT("RELoading Completed"));
		}), EquipmentManager->GetCurrentWeaponInstance()->GetReloadTime(), false);

}

void ALSCharacter::EquipFirstWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipFirstWeapon"));
	LSCHECK(nullptr != EquipmentManager->GetWeaponInstance(0));
	SetWeapon(EquipmentManager->GetWeaponInstance(0));
	EquipmentManager->SetCurrentWeaponIndex(0);

	// 테스트용
	EquipmentManager->GetWeaponInstance(0)->OnAimDirChange.AddUObject(this, &ALSCharacter::ShowDebugLine);
}

void ALSCharacter::EquipSecondWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipSecondWeapon"));
	LSCHECK(nullptr != EquipmentManager->GetWeaponInstance(1));
	SetWeapon(EquipmentManager->GetWeaponInstance(1));
	EquipmentManager->SetCurrentWeaponIndex(1);
}

void ALSCharacter::EquipThirdWeapon(const FInputActionValue& Value)
{
	LSLOG(Warning, TEXT("EquipThirdWeapon"));
	LSCHECK(nullptr != EquipmentManager->GetWeaponInstance(2));
	SetWeapon(EquipmentManager->GetWeaponInstance(2));
	EquipmentManager->SetCurrentWeaponIndex(2);
}

void ALSCharacter::Interact(const FInputActionValue& Value)
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

	if (bResult)
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

void ALSCharacter::TestAct(const FInputActionValue& Value)
{
	InventoryManager->SetDefaultWeapon();
}

void ALSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LSLOG_S(Warning);

	LSAnim = Cast<ULSAnimInstance>(GetMesh()->GetAnimInstance());
	LSCHECK(nullptr != LSAnim);

	LSAnim->OnAttackHitCheck.AddUObject(this, &ALSCharacter::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		LSLOG(Warning, TEXT("OnHPIsZero"));
		LSAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	});

	ULSAnimInstance* AnimInstance = Cast<ULSAnimInstance>(GetMesh()->GetAnimInstance());
	LSCHECK(nullptr != AnimInstance);
	AnimInstance->OnMontageEnded.AddDynamic(this, &ALSCharacter::OnAttackMontageEnded);

	InventoryManager->SetEquipmentComponent(EquipmentManager);
}

void ALSCharacter::PossessedBy(AController * NewController)
{
	LSLOG_S(Warning);
	Super::PossessedBy(NewController);
}

void ALSCharacter::AttackCheck()
{
	LSCHECK(EquipmentManager->GetCurrentWeaponInstance() != nullptr);
	LSLOG_S(Warning);
	if (!CanShoot(EAmmoType::RIFLE))
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

	LSCHECK(EquipmentManager->GetCurrentWeaponInstance());
	// TODO: 가독성 있게 쪼개기
	FVector TempVector = EquipmentManager->GetCurrentWeaponInstance()->CalculateRecoil((FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X)), EquipmentManager->GetCurrentWeaponInstance()->GetCurrentSpreadAngle());
	ShowDebugLine(TempVector);

	EquipmentManager->DecreaseRoundsRemaining();

	GetController()->SetControlRotation(TempVector.Rotation());

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
			// #include "Engine/DamageEvents.h"
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

bool ALSCharacter::CanShoot(EAmmoType AmmoType)
{
	if (bIsReloading)
	{
		LSLOG(Warning, TEXT("IsReloading"));
		return false;
	}
	//  TODO: weapon 의 magazine ammo로 바꾸기
	LSCHECK(EquipmentManager->WeaponInstanceList.Num() > 0 &&
			EquipmentManager->CurrentWeaponInstance != nullptr ,false);
	if (EquipmentManager->GetRoundsRemaining() == 0)
	{
		LSLOG(Warning, TEXT("No Ammo"));
	 	return false;
	}
	return true;
}

float ALSCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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

bool ALSCharacter::CanSetWeapon()
{
	// TODO: (nullptr == CurrentWeapon);
	return true; 
}

void ALSCharacter::SetWeapon(ALSWeaponInstance* NewWeapon)
{
	LSCHECK(nullptr != NewWeapon);
	LSLOG_S(Warning);
	if (nullptr != EquipmentManager->GetCurrentWeaponInstance())
	{
		// TODO: 무기 장착 해제 관련 메서드 호출
	}
	
	FName WeaponSocket(TEXT("weapon_r_socket"));
	if (nullptr == RootComponent)
	{
		LSLOG(Warning, TEXT("No RootComponent"));
	}
	if (nullptr == GetMesh())
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

void ALSCharacter::Attack()
{
	LSLOG(Warning, TEXT("Attack"));
	if (bIsAttacking) return;
	LSAnim->PlayAttackMontage();
	bIsAttacking = true;
}

void ALSCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	LSCHECK(bIsAttacking);
	bIsAttacking = false;

	OnAttackEnd.Broadcast();
}

void ALSCharacter::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
	LSCHECK(nullptr != AssetLoaded);
	GetMesh()->SetSkeletalMesh(AssetLoaded);
	SetCharacterState(ECharacterState::READY);
}

float ALSCharacter::GetFinalAttackDamage() const
{
	if (EquipmentManager == nullptr || EquipmentManager->GetCurrentWeaponInstance() == nullptr)
	{
		return 0;
	}
	else
	{
		return EquipmentManager->GetCurrentWeaponInstance()->GetFinalDamage();
	}
}

void ALSCharacter::InteractCheck()
{
	if (!bIsNearInteractableObject)
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

	if (bResult)
	{
		LSLOG(Warning, TEXT("HIT BOx"));
	}
}

void ALSCharacter::DropItem()
{
	float RandomNumber = FMath::FRandRange(0.0f, 1.0f);
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
}

void ALSCharacter::SetCharacterStateDead()
{
	SetCharacterState(ECharacterState::DEAD);
}

void ALSCharacter::ShowDebugLine(FVector Dir)
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