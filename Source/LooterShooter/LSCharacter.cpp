// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacter.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
ALSCharacter::ALSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// #include "Components/CapsuleComponent.h"
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);


	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -88.0f),
		FRotator(0.0f, -90.0f, 0.0f)
	);


	SpringArm->TargetArmLength = 400.0f;
	// SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_QUINN(TEXT("/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn"));
	if ( SKM_QUINN.Succeeded() )
	{
		GetMesh()->SetSkeletalMesh( SKM_QUINN.Object );
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// uaniminstace code..

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
}

// Called every frame
void ALSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALSCharacter::JumpAct);


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

void ALSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LSLOG_S(Warning);
}

void ALSCharacter::PossessedBy(AController * NewController)
{
	LSLOG_S(Warning);
	Super::PossessedBy(NewController);
}