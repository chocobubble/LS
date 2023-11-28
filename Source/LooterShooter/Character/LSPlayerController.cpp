// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPlayerController.h"
#include "LooterShooter/UI/LSHUDWidget.h"
#include "LSPlayerState.h"
#include "LSPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LooterShooter/UI/LSGameplayWidget.h"
#include "LooterShooter/UI/LSGameplayResultWidget.h"
#include "LooterShooter/GameMode/LSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "LSMonster.h"
#include "LooterShooter/UI/LSInventoryWidget.h"
#include "LooterShooter/UI/LSRoundProgressbar.h"
#include "LooterShooter/UI/LSEnhanceWidget.h"
#include "LooterShooter/Component/LSInventoryComponent.h"
#include "LooterShooter/Component/LSResourceManageComponent.h"
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
	if (IMC_DEFAULT_KBM.Succeeded())
	{
		InputMapping = IMC_DEFAULT_KBM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_GAMEPAUSE(TEXT("/Game/LS/Input/Actions/IA_GamePause.IA_GamePause"));
	if (IA_GAMEPAUSE.Succeeded())
	{
		GamePause = IA_GAMEPAUSE.Object;
	}

    static ConstructorHelpers::FObjectFinder<UInputAction> IA_INVENTORY(TEXT("/Game/LS/Input/Actions/IA_Inventory.IA_Inventory"));
	if (IA_INVENTORY.Succeeded())
	{
		OpenInventory = IA_INVENTORY.Object;
	}

    static ConstructorHelpers::FObjectFinder<UInputAction> IA_ENHANCE(TEXT("/Game/LS/Input/Actions/IA_Enhance.IA_Enhance"));
	if (IA_ENHANCE.Succeeded())
	{
		OpenEnhanceUI = IA_ENHANCE.Object;
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

    static ConstructorHelpers::FClassFinder<ULSEnhanceWidget> UI_ENHANCE_C(TEXT("/Game/LS/UI/UI_Enhancement.UI_Enhancement_C"));
    if (UI_ENHANCE_C.Succeeded())
    {
        EnhanceWidgetClass = UI_ENHANCE_C.Class;
    }

    static ConstructorHelpers::FClassFinder<ULSInventoryWidget> UI_INVENTORY_C(TEXT("/Game/LS/UI/UI_Inventory.UI_Inventory_C"));
    if (UI_INVENTORY_C.Succeeded())
    {
        InventoryWidgetClass = UI_INVENTORY_C.Class;
    }

    static ConstructorHelpers::FClassFinder<ULSRoundProgressbar> UI_ROUNDPB_C(TEXT("/Game/LS/UI/WB_RadialPB.WB_RadialPB_C"));
    if (UI_ROUNDPB_C.Succeeded())
    {
        RoundPBWidgetClass = UI_ROUNDPB_C.Class;
    }
}


void ALSPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();

}

void ALSPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);
}

void ALSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// AutoRun이 활성화 되었을 때
	if (IsAutoRunning())
	{
        APawn* CurrentPawn = GetPawn();
		if (CurrentPawn)
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

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
    ChangeInputMode(true);

    HUDWidget = CreateWidget<ULSHUDWidget>(this, HUDWidgetClass);
    if (HUDWidget)
    {
        HUDWidget->AddToViewport(3);
    }
    
    ResultWidget = CreateWidget<ULSGameplayResultWidget>(this, ResultWidgetClass);
    InventoryWidget = CreateWidget<ULSInventoryWidget>(this, InventoryWidgetClass);
    RoundPBWidget = CreateWidget<ULSRoundProgressbar>(this, RoundPBWidgetClass);
    if (RoundPBWidget)
    {
        RoundPBWidget->AddToViewport(0);
    }

    LSPlayerState = LSPlayerState ? LSPlayerState : Cast<ALSPlayerState>(PlayerState);
    if (LSPlayerState)
    {
        HUDWidget->BindPlayerState(LSPlayerState);
        LSPlayerState->OnPlayerStateChanged.Broadcast();
        LSPlayer = LSPlayer ? LSPlayer : Cast<ALSPlayer>(GetPawn());
    	if (LSPlayer && HUDWidget)
        {
            HUDWidget->BindResourceManageComponent(LSPlayer->GetResourceManager());
            HUDWidget->BindEquipmentComponent(LSPlayer->GetEquipmentManager());
            HUDWidget->BindPlayer(LSPlayer);
        }
    }

    LSPlayerState = LSPlayerState ? LSPlayerState : Cast<ALSPlayerState>(PlayerState);
    LSPlayer = LSPlayer ? LSPlayer : Cast<ALSPlayer>(GetPawn());
    if (LSPlayerState && LSPlayer)
    {
        ULSResourceManageComponent* ResourceManager = LSPlayer->GetResourceManager();
        if (ResourceManager)
        {
            LSPlayerState->BindWithResourceManager(ResourceManager);
            InitResourceManager(ResourceManager);
        }
    }
}


void ALSPlayerController::MonsterKill(ALSMonster* KilledMonster) const
{
    LSPlayerState->AddExp(KilledMonster->GetExp());
}

void ALSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent) 
	{
		EnhancedInputComponent->BindAction(GamePause, ETriggerEvent::Triggered, this, &ALSPlayerController::OnGamePause);
		EnhancedInputComponent->BindAction(OpenInventory, ETriggerEvent::Triggered, this, &ALSPlayerController::OnInventoryOpen);
   	    EnhancedInputComponent->BindAction(OpenEnhanceUI, ETriggerEvent::Triggered, this, &ALSPlayerController::OnEnhanceUIOpen);
	}
}

void ALSPlayerController::OnGamePause(const FInputActionValue& Value)
{
    MenuWidget = CreateWidget<ULSGameplayWidget>(this, MenuWidgetClass);
    if (MenuWidget == nullptr)
	{
		return;
	}
    MenuWidget->AddToViewport(0);
    SetPause(true);
    ChangeInputMode(false);
}

void ALSPlayerController::OnInventoryOpen(const FInputActionValue& Value)
{
   	InventoryWidget = CreateWidget<ULSInventoryWidget>(this, InventoryWidgetClass);
    if (InventoryWidget == nullptr)
	{
		return;
	}
	if (Cast<ALSPlayer>(GetPawn()) && Cast<ALSPlayer>(GetPawn())->GetInventoryManager())
	{
    	InventoryWidget->Init(Cast<ALSPlayer>(GetPawn())->GetInventoryManager());
    	InventoryWidget->AddToViewport();
	}
    SetPause(true);
    ChangeInputMode(false);
}

void ALSPlayerController::OnEnhanceUIOpen()
{
    EnhanceWidget = CreateWidget<ULSEnhanceWidget>(this, EnhanceWidgetClass);
    if (EnhanceWidget == nullptr)
	{
		return;
	}
    LSPlayer = LSPlayer ? LSPlayer : Cast<ALSPlayer>(GetPawn());
	if (LSPlayer && LSPlayer->GetInventoryManager() && LSPlayer->GetInventoryManager()->GetWeaponDefinitionInList(0) && LSPlayer->GetResourceManager())
	{
    	EnhanceWidget->Init(LSPlayer->GetInventoryManager()->GetWeaponDefinitionInList(0), LSPlayer->GetResourceManager());
	}
    EnhanceWidget->AddToViewport(10);
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
    //ALSGameState* LSGameState = Cast<ALSGameState>(UGameplayStatics::GetGameState(this));
    //ResultWidget->BindGameState(LSGameState);

    if (ResultWidget)
    {
        ResultWidget->AddToViewport(0);
    }
    ChangeInputMode(false);
}

void ALSPlayerController::InitResourceManager(ULSResourceManageComponent* ResourceManager)
{
	if (LSPlayerState && ResourceManager)
	{
        ResourceManager->SetGoldAmount(LSPlayerState->GetCurrentGold());
        ResourceManager->SetCurrentAmmo(LSPlayerState->GetAmmoMap());
        LSLOG(Warning, TEXT("Init ResourceManager"));
	}
}
