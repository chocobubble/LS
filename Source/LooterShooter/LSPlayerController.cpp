// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerController.h"
#include "LSHUDWidget.h"
#include "LSPlayerState.h"
#include "LSCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LSGameplayWidget.h"
#include "LSGameplayResultWidget.h"
#include "LSGameState.h"
#include "Kismet/GameplayStatics.h"


ALSPlayerController::ALSPlayerController()
{
    static ConstructorHelpers::FClassFinder<ULSHUDWidget> UI_HUD_C(TEXT("/Game/LS/UI/UI_HUD.UI_HUD_C"));
    if (UI_HUD_C.Succeeded())
    {
        HUDWidgetClass = UI_HUD_C.Class;
    }

    static ConstructorHelpers::FObjectFinder<UInputMappingContext> LS_CONTEXT(TEXT("/Game/LS/Input/LS_InputMappingContext.LS_InputMappingContext"));
	if ( LS_CONTEXT.Succeeded())
	{
		InputMapping = LS_CONTEXT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LS_GAMEPAUSE(TEXT("/Game/LS/Input/Actions/LS_GamePause.LS_GamePause"));
	if ( LS_GAMEPAUSE.Succeeded())
	{
		GamePause = LS_GAMEPAUSE.Object;
	}

    static ConstructorHelpers::FClassFinder<ULSGameplayWidget> UI_MENU_C(TEXT("/Game/LS/UI/UI_Menu.UI_Menu_C"));
    if (UI_MENU_C.Succeeded())
    {
        MenuWidgetClass = UI_MENU_C.Class;
    }

    static ConstructorHelpers::FClassFinder<ULSGameplayWidget> UI_RESULT_C(TEXT("/Game/LS/UI/UI_Result.UI_Result_C"));
    if (UI_RESULT_C.Succeeded())
    {
        ResultWidgetClass = UI_RESULT_C.Class;
    }
}


void ALSPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    LSLOG_S(Warning);
}

void ALSPlayerController::OnPossess(APawn* aPawn)
{
    LSLOG_S(Warning);
    Super::OnPossess(aPawn);
}

void ALSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    //    ChangeInputMode(true);

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);


    ChangeInputMode(true);

    HUDWidget  = CreateWidget<ULSHUDWidget>(this, HUDWidgetClass);
    LSCHECK(nullptr != HUDWidget);
    HUDWidget->AddToViewport(1);

    ResultWidget = CreateWidget<ULSGameplayResultWidget>(this, ResultWidgetClass);
    LSCHECK(nullptr != ResultWidget);

/*
    HUDWidget->AddToViewport(1);
*/
    LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    // ALSPlayerState*  LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    //auto LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    LSCHECK(nullptr != LSPlayerState);
    HUDWidget->BindPlayerState(LSPlayerState);
    LSPlayerState->OnPlayerStateChanged.Broadcast();  

/*
    ResultWidget = CreateWidget<ULSGameplayResultWidget>(this, ResultWidgetClass);
    LSCHECK(nullptr != ResultWidget);
*/
}

ULSHUDWidget* ALSPlayerController::GetHUDWidget() const
{
    return HUDWidget;
}

void ALSPlayerController::NPCKill(ALSCharacter* KilledNPC) const
{
    LSPlayerState->AddExp(KilledNPC->GetExp());
}

void ALSPlayerController::AddGameScore() const
{
    LSPlayerState->AddGameScore();
}

void ALSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    //APlayerController* PlayerController = GetController<APlayerController>();
	if (this == nullptr) 
	{
		LSLOG(Warning, TEXT("Controller nullptr"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		LSLOG(Warning, TEXT("Subsystem nullptr"));
		return;
	}

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	LSLOG_S(Warning);


	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if(EnhancedInputComponent == nullptr) 
	{
		LSLOG(Warning, TEXT("Enhanced Input Component nullptr"));
		return;
	}
	EnhancedInputComponent->BindAction(GamePause, ETriggerEvent::Triggered, this, &ALSPlayerController::OnGamePause);
}

void ALSPlayerController::OnGamePause(const FInputActionValue& Value)
{
    LSLOG(Warning, TEXT("Game Pause"));
    MenuWidget = CreateWidget<ULSGameplayWidget>(this, MenuWidgetClass);
    LSCHECK(nullptr != MenuWidget);
    MenuWidget->AddToViewport(3);

    SetPause(true);
    ChangeInputMode(false);
}

void ALSPlayerController::ChangeInputMode(bool bGameMode)
{
    if (bGameMode)
    {
        SetInputMode(GameInputMode);
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(UIInputMode);
        bShowMouseCursor = true;
    }
}

void ALSPlayerController::ShowResultUI()
{
    // #include "Kismet/GameplayStatics.h"
    ALSGameState* LSGameState = Cast<ALSGameState>(UGameplayStatics::GetGameState(this));
    LSCHECK(nullptr != LSGameState);
    ResultWidget->BindGameState(LSGameState);

    ResultWidget->AddToViewport();
    ChangeInputMode(false);
}