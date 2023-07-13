// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacter.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

#include "Engine/DamageEvents.h"

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
//#include "Animation/AnimInstance.h"


// Sets default values
ALSCharacter::ALSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

/*
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	// #include "GameFramework/CharacterMovementComponent.h"
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
*/
 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<ULSCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	//#include "Components/WidgetComponent.h"
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));


	// #include "Components/CapsuleComponent.h"
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	HPBarWidget->SetupAttachment(GetMesh());


	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -88.0f),
		FRotator(0.0f, -90.0f, 0.0f)
	);


	ArmLengthTo = ArmLengthOnIdle;
	SpringArm->TargetArmLength = ArmLengthTo;  //400.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0.0f, 90.0f, 90.0f));

	// max jump height
	GetCharacterMovement()->JumpZVelocity = 450.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_QUINN(TEXT("/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn"));
	if ( SKM_QUINN.Succeeded() )
	{
		GetMesh()->SetSkeletalMesh( SKM_QUINN.Object );
	}
	else
	{
		LSLOG(Warning, TEXT("skeletalmesh desn't succeded"));
	}

	


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// uaniminstace code..
	static ConstructorHelpers::FClassFinder<UAnimInstance> RIFLE_ANIM(TEXT("/Game/LS/Animations/RifleAnimBlueprint.RifleAnimBlueprint_C"));//(TEXT("/Game/LS/Animations/text.text_C"));
	//
	if (RIFLE_ANIM.Succeeded() )
	{
		GetMesh()->SetAnimInstanceClass(RIFLE_ANIM.Class);
	}
	else
	{
		LSLOG(Warning, TEXT("Rifle anim desn't succeded"));
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> LS_CONTEXT(TEXT("/Game/LS/Input/LS_InputMappingContext.LS_InputMappingContext"));
	if ( LS_CONTEXT.Succeeded())
	{
		InputMapping = LS_CONTEXT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LS_MOVE(TEXT("/Game/LS/Input/Actions/LS_Move.LS_Move"));
	if ( LS_MOVE.Succeeded())
	{
		MoveAction = LS_MOVE.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> LS_JUMP(TEXT("/Game/LS/Input/Actions/LS_Jump.LS_Jump"));
	if ( LS_JUMP.Succeeded())
	{
		JumpAction = LS_JUMP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LS_LOOK(TEXT("/Game/LS/Input/Actions/LS_LOOK.LS_LOOK"));
	if ( LS_LOOK.Succeeded())
	{
		LookAction = LS_LOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LS_SHOOT(TEXT("/Game/LS/Input/Actions/LS_SHOOT.LS_SHOOT"));
	if ( LS_SHOOT.Succeeded())
	{
		ShootAction = LS_SHOOT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LS_MELEE(TEXT("/Game/LS/Input/Actions/LS_MELEE.LS_MELEE"));
	if ( LS_MELEE.Succeeded())
	{
		MeleeAttackAction = LS_MELEE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LS_AUTO_RUN(TEXT("/Game/LS/Input/Actions/LS_Auto_Run.LS_Auto_Run"));
	if ( LS_AUTO_RUN.Succeeded())
	{
		AutoRunAction = LS_AUTO_RUN.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LS_AIM(TEXT("/Game/LS/Input/Actions/LS_Aim.LS_Aim"));
	if ( LS_AIM.Succeeded())
	{
		AimAction = LS_AIM.Object;
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LSCharacter"));

	AttackRange = 1000.0f;

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

	bIsAttacking = false;

	SetActorHiddenInGame(true);
	HPBarWidget->SetHiddenInGame(true);
	SetCanBeDamaged(false);

	DeadTimer = 5.0f;

}

// Called when the game starts or when spawned
void ALSCharacter::BeginPlay()
{
	Super::BeginPlay();
/*
	//APlayerController* PlayerController = Cast<APlayerController>(GetController());
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
	Subsystem->AddMappingContext(InputMapping, 0);
*/

/*

	FName WeaponSocket(TEXT("weapon_r_socket"));
	ALSWeapon* CurWeapon = GetWorld()->SpawnActor<ALSWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon)
	{
		CurWeapon->AttachToComponent(
			GetMesh(), 
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
			WeaponSocket);
	}
	else
	{
		LSLOG(Warning, TEXT("CurWeapon is nullptr"));
	}
*/
/*
	ULSCharacterWidget* CharacterWidget = Cast<ULSCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
*/
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

	// auto DefaultSetting = GetDefault<ULSCharacterSetting>();

	if (bIsPlayer)
	{
		//AssetIndex = 4;
		auto LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
		LSCHECK(nullptr != LSPlayerState);
		//AssetIndex = LSPlayerState->GetCharacterIndex();
	}
	else
	{
		//AssetIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
	}

	//CharacterAssetToLoad = DefaultSetting->CharacterAssets[AssetIndex];
	CharacterAssetToLoad.SetPath(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn'"));
	auto LSGameInstance = Cast<ULSGameInstance>(GetGameInstance());
	LSCHECK(nullptr != LSGameInstance);
	AssetStreamingHandle = LSGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ALSCharacter::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);
}

void ALSCharacter::SetCharacterState(ECharacterState NewState)
{
	LSCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{
		if(bIsPlayer)
		{
			DisableInput(LSPlayerController);

			LSPlayerController->GetHUDWidget()->BindCharacterStat(CharacterStat);

			auto LSPlayerState = Cast<ALSPlayerState>(GetPlayerState());
			LSCHECK(nullptr != LSPlayerState);
			CharacterStat->SetNewLevel(LSPlayerState->GetCharacterLevel());
		}
		else
		{
			auto LSGameMode = Cast<ALSGameMode>(GetWorld()->GetAuthGameMode());
			LSCHECK(nullptr != LSGameMode);
			int32 TargetLevel = FMath::CeilToInt(((float)LSGameMode->GetScore() * 0.8f));
			int32 FinalLevel = FMath::Clamp<int32>(TargetLevel, 1, 20);
			LSLOG(Warning, TEXT("New NPC Level : %d"), FinalLevel);
			CharacterStat->SetNewLevel(FinalLevel);
		}

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
		CharacterWidget->BindCharacterStat(CharacterStat);

		if (bIsPlayer)
		{
			//SetControlMode(EControlMode::DIABLO);
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
			EnableInput(LSPlayerController);
		}
		else
		{
			//SetControlMode(EControlMode::NPC);
			GetCharacterMovement()->MaxWalkSpeed = 400.0f;
			LSAIController->RunAI();
		}
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		LSAnim->SetDeadAnim();
		SetCanBeDamaged(false);
		
		if(bIsPlayer)
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
				//LSPlayerController->RestartLevel();
				LSPlayerController->ShowResultUI();
			}
			else
			{
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

// Called every frame
void ALSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthChangingSpeed);

	InteractCheck();
}

// Called to bind functionality to input
void ALSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
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

	LSLOG_S(Warning);


	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent == nullptr) 
	{
		LSLOG(Warning, TEXT("Enhanced Input Component nullptr"));
		return;
	}
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALSCharacter::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALSCharacter::Jump);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALSCharacter::Look);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ALSCharacter::Shoot);
	EnhancedInputComponent->BindAction(MeleeAttackAction, ETriggerEvent::Triggered, this, &ALSCharacter::MeleeAttack);
	EnhancedInputComponent->BindAction(AutoRunAction, ETriggerEvent::Triggered, this, &ALSCharacter::AutoRun);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ALSCharacter::OnAiming);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ALSCharacter::EndAiming);


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
	if(Value.Get<bool>())
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
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
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

void ALSCharacter::AutoRun(const FInputActionValue& Value)
{
	LSCHECK(nullptr != LSPlayerController);
	LSPlayerController->SetIsAutoRunning(!LSPlayerController->GetIsAutoRunning());
}

void ALSCharacter::OnAiming(const FInputActionValue& Value)
{
	LSCHECK(nullptr != SpringArm);
	LSLOG(Warning, TEXT("OnAiming"));
	ArmLengthTo = ArmLengthOnAiming;
	LSAnim->SetAimAnim(true);
}

void ALSCharacter::EndAiming(const FInputActionValue& Value)
{
	LSCHECK(nullptr != SpringArm);
	LSLOG(Warning, TEXT("EndAiming"));
	ArmLengthTo = ArmLengthOnIdle;
	LSAnim->SetAimAnim(false);
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
}

void ALSCharacter::PossessedBy(AController * NewController)
{
	LSLOG_S(Warning);
	Super::PossessedBy(NewController);
}

void ALSCharacter::AttackCheck()
{
	float FinalAttackRange = GetFinalAttackRange();
/*
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * FinalAttackRange, //AttackRange,
		ECollisionChannel::ECC_GameTraceChannel2,
		Params
	);
*/
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalAttackRange)),
		ECollisionChannel::ECC_GameTraceChannel4,
		Params
	);


#if ENABLE_DRAW_DEBUG

	// #include "DrawDebugHelpers.h"
/*
	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + GetActorForwardVector(),
		GetActorLocation() + GetActorForwardVector() * FinalAttackRange, //AttackRange,
		bResult ? FColor::Green : FColor::Red,
		true,
		1.0f,
		0,
		1.f
	);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + FVector(0.0f, 0.0f, 30.0f),
		//	#include "Math/RotationMatrix.h"
		GetActorLocation() + (SpringArm->GetComponentLocation() + (FRotationMatrix(SpringArm->GetComponentRotation()).GetUnitAxis(EAxis::X)* FinalAttackRange) - GetActorLocation()), //AttackRange,
		bResult ? FColor::Green : FColor::Yellow,
		true,
		1.0f,
		0,
		1.f
	);

	DrawDebugLine(
		GetWorld(),
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(SpringArm->GetComponentRotation()).GetUnitAxis(EAxis::X)* FinalAttackRange) ), //AttackRange,
		bResult ? FColor::Green : FColor::Purple,
		true,
		1.0f,
		0,
		1.f
	);
*/
	DrawDebugLine(
		GetWorld(),
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalAttackRange)), //AttackRange,
		bResult ? FColor::Green : FColor::White,
		true,
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

			// #include "Engine/DamageEvents.h"
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(GetFianlAttackDamage(), DamageEvent, GetController(), this);
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

float ALSCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	LSLOG(Warning, TEXT("Actor %s took damage : %f"), *GetName(), FinalDamage);

	CharacterStat->SetDamage(FinalDamage);

	if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			ALSPlayerController* LSPC = Cast<ALSPlayerController>(EventInstigator);
			LSCHECK(nullptr != LSPC, 0.0f);
			LSPC->NPCKill(this);
		}
	}

	return FinalDamage;
}

bool ALSCharacter::CanSetWeapon()
{
	return true; //(nullptr == CurrentWeapon);
}

void ALSCharacter::SetWeapon(ALSWeapon* NewWeapon)
{
	LSCHECK(nullptr != NewWeapon);// && nullptr == CurrentWeapon);

	if (nullptr != CurrentWeapon)
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}
	
	
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

int32 ALSCharacter::GetExp() const
{
	return CharacterStat->GetDropExp();
}

float ALSCharacter::GetFinalAttackRange() const
{
	return (nullptr != CurrentWeapon) ? CurrentWeapon->GetAttackRange() : AttackRange;
}

float ALSCharacter::GetFinalInteractRange() const
{
	return InteractRange;
}

float ALSCharacter::GetFianlAttackDamage() const
{
	float AttackDamage = (nullptr != CurrentWeapon) ? (CharacterStat->GetAttack() + CurrentWeapon->GetAttackDamage())
		: CharacterStat->GetAttack();
	float AttackModifier = (nullptr != CurrentWeapon) ? CurrentWeapon->GetAttackModifier() : 1.0f;
	return AttackDamage * AttackModifier;
}

void ALSCharacter::InteractCheck()
{
	float FinalInteractRange = GetFinalInteractRange();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		SpringArm->GetComponentLocation(),
		(SpringArm->GetComponentLocation() + (FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X) * FinalInteractRange)),
		ECollisionChannel::ECC_GameTraceChannel4,
		Params
	);	

	if(bResult)
	{
		LSLOG(Warning, TEXT("HIT BOx"));
	}
}