// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerController.h"
#include "LSHUDWidget.h"
#include "LSPlayerState.h"
//#include "LSCharacter.h"
#include "LSPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LSGameplayWidget.h"
#include "LSGameplayResultWidget.h"
#include "LSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "LSMonster.h"
#include "LSInventoryWidget.h"
#include "LSRoundProgressbar.h"

//test
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"


ALSPlayerController::ALSPlayerController()
{
    static ConstructorHelpers::FClassFinder<ULSHUDWidget> UI_HUD_C(TEXT("/Game/LS/UI/UI_HUD.UI_HUD_C"));
    if (UI_HUD_C.Succeeded())
    {
        HUDWidgetClass = UI_HUD_C.Class;
    }

    static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT_KBM(TEXT("/Game/LS/Input/IMC_DEFAULT_KBM.IMC_DEFAULT_KBM"));
	if ( IMC_DEFAULT_KBM.Succeeded())
	{
		InputMapping = IMC_DEFAULT_KBM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_GAMEPAUSE(TEXT("/Game/LS/Input/Actions/IA_GamePause.IA_GamePause"));
	if ( IA_GAMEPAUSE.Succeeded())
	{
		GamePause = IA_GAMEPAUSE.Object;
	}

    static ConstructorHelpers::FObjectFinder<UInputAction> IA_INVENTORY(TEXT("/Game/LS/Input/Actions/IA_Inventory.IA_Inventory"));
	if ( IA_INVENTORY.Succeeded())
	{
		OpenInventory = IA_INVENTORY.Object;
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

    static ConstructorHelpers::FClassFinder<ULSInventoryWidget> UI_INVENTORY_C(TEXT("/Game/LS/UI/UI_Inventory.UI_Inventory_C"));
    if (UI_INVENTORY_C.Succeeded())
    {
        InventoryWidgetClass = UI_INVENTORY_C.Class;
    }
    else
    {
        LSLOG_S(Error);
    }

    static ConstructorHelpers::FClassFinder<ULSRoundProgressbar> UI_ROUNDPB_C(TEXT("/Game/LS/UI/WB_RadialPB.WB_RadialPB_C"));
    if (UI_ROUNDPB_C.Succeeded())
    {
        RoundPBWidgetClass = UI_ROUNDPB_C.Class;
    }
    else
    {
        LSLOG_S(Error);
    }

///// test
    static ConstructorHelpers::FObjectFinder<UMaterialInstance> UI_MI(TEXT("/Game/LS/Materials/M_RoundProgressbar_Inst.M_RoundProgressbar_Inst"));
    if (UI_MI.Succeeded())
    {
        MI = UI_MI.Class;
    }
    else
    {
        LSLOG_S(Error);
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

void ALSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// AutoRun이 활성화 되었을 때
	if (GetIsAutoRunning())
	{
		if (APawn* CurrentPawn = GetPawn())
		{
			const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			CurrentPawn->AddMovementInput(MovementDirection, 1.0f);	
		}
	}    
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
    
    InventoryWidget = CreateWidget<ULSInventoryWidget>(this, InventoryWidgetClass);
    LSCHECK(nullptr != InventoryWidget);

    RoundPBWidget = CreateWidget<ULSRoundProgressbar>(this, RoundPBWidgetClass);
    LSCHECK(nullptr != RoundPBWidget);
    RoundPBWidget->AddToViewport(0);

/*
    HUDWidget->AddToViewport(1);
*/
    LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    // ALSPlayerState*  LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    //auto LSPlayerState = Cast<ALSPlayerState>(PlayerState);
    LSCHECK(nullptr != LSPlayerState);
    HUDWidget->BindPlayerState(LSPlayerState);
    LSPlayerState->OnPlayerStateChanged.Broadcast();  


    ALSPlayer* LSPlayer =  Cast<ALSPlayer>(GetCharacter());
    LSCHECK(nullptr != LSPlayer);
    HUDWidget->BindResourceManageComponent(LSPlayer->GetResourceManager());
    HUDWidget->BindEquipmentComponent(LSPlayer->GetEquipmentManager());
    HUDWidget->BindPlayer(LSPlayer);
/*
    ALSCharacter* LSCharacter =  Cast<ALSCharacter>(GetCharacter());
    LSCHECK(nullptr != LSCharacter);
*/
/*
    ResultWidget = CreateWidget<ULSGameplayResultWidget>(this, ResultWidgetClass);
    LSCHECK(nullptr != ResultWidget);
*/
}

ULSHUDWidget* ALSPlayerController::GetHUDWidget() const
{
    return HUDWidget;
}

void ALSPlayerController::NPCKill(ALSMonster* KilledNPC) const
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
	EnhancedInputComponent->BindAction(OpenInventory, ETriggerEvent::Triggered, this, &ALSPlayerController::OnInventoryOpen);

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

void ALSPlayerController::OnInventoryOpen(const FInputActionValue& Value)
{
    LSLOG(Warning, TEXT("Inventory Open"));
    ShowInventoryUI();
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

void ALSPlayerController::ShowInventoryUI()
{
    /*
    // #include "Kismet/GameplayStatics.h"
    ALSGameState* LSGameState = Cast<ALSGameState>(UGameplayStatics::GetGameState(this));
    LSCHECK(nullptr != LSGameState);
    ResultWidget->BindGameState(LSGameState);
*/
    InventoryWidget = CreateWidget<ULSInventoryWidget>(this, InventoryWidgetClass);
    LSCHECK(nullptr != InventoryWidget);
    InventoryWidget->Init(Cast<ALSPlayer>(GetPawn())->GetInventoryManager());
    InventoryWidget->AddToViewport();
    ChangeInputMode(false);
}

bool ALSPlayerController::GetIsAutoRunning() const
{
    return bIsAutoRunning;
}

void ALSPlayerController::SetIsAutoRunning(const bool bEnabled)
{
    bIsAutoRunning = bEnabled;
}