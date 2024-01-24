// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameTitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "LooterShooter/Controller/LSTitleController.h"
#include "LooterShooter/Character/LSPlayerState.h"
#include "LooterShooter/Network/HttpActor.h"

void ULSGameTitleWidget::OnNewGameClicked()
{
	ALSTitleController* LSTitleController = Cast<ALSTitleController>(GetOwningPlayer());
	if (LSTitleController)
	{
		ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(LSTitleController->PlayerState);
		if (LSPlayerState)
		{
			if (LSPlayerState->GetSessionId() != "Default")
			{
				LSPlayerState->SaveSessionId();
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("LS_Level_1"));

			}
		}
	}
}

void ULSGameTitleWidget::OnCreateAccountClicked()
{
	ALSTitleController* LSTitleController = Cast<ALSTitleController>(GetOwningPlayer());
	if (LSTitleController)
	{
		ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(LSTitleController->PlayerState);
		if (LSPlayerState)
		{
			AHttpActor* HttpActor = LSPlayerState->GetHttpActor();
			if (HttpActor)
			{
				HttpActor->RequestCreateAccount("");
			}
		}
	}
}

void ULSGameTitleWidget::OnLoginClicked()
{
	ALSTitleController* LSTitleController = Cast<ALSTitleController>(GetOwningPlayer());
	if (LSTitleController)
	{
		ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(LSTitleController->PlayerState);
		if (LSPlayerState)
		{
			AHttpActor* HttpActor = LSPlayerState->GetHttpActor();
			if (HttpActor)
			{
				HttpActor->RequestLogin();
			}
		}
	}
}

void ULSGameTitleWidget::OnContinueClicked()
{
	ALSTitleController* LSTitleController = Cast<ALSTitleController>(GetOwningPlayer());
	if (LSTitleController)
	{
		ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(LSTitleController->PlayerState);
		if (LSPlayerState)
		{
			LSPlayerState->CreateNewSaveData();
			LSPlayerState->DataLoadRequestToServer();
		}
	}
}

void ULSGameTitleWidget::OnSaveClicked()
{
	ALSTitleController* LSTitleController = Cast<ALSTitleController>(GetOwningPlayer());
	if (LSTitleController)
	{
		ALSPlayerState* LSPlayerState = Cast<ALSPlayerState>(LSTitleController->PlayerState);
		if (LSPlayerState)
		{
			AHttpActor* HttpActor = LSPlayerState->GetHttpActor();
			if (HttpActor)
			{
				HttpActor->SaveData();
			}
		}
	}
}

void ULSGameTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNewGame")));
	CreateAccountButton = Cast<UButton>(GetWidgetFromName(TEXT("btnCreateAccount")));
	LoginButton = Cast<UButton>(GetWidgetFromName(TEXT("btnLogin")));
	NewGameButton->OnClicked.AddDynamic(this, &ULSGameTitleWidget::OnNewGameClicked);
	CreateAccountButton->OnClicked.AddDynamic(this, &ULSGameTitleWidget::OnCreateAccountClicked);
	LoginButton->OnClicked.AddDynamic(this, &ULSGameTitleWidget::OnLoginClicked);


	LoadButton = Cast<UButton>(GetWidgetFromName(TEXT("btnContinue")));
	LoadButton->OnClicked.AddDynamic(this, &ULSGameTitleWidget::OnContinueClicked);
	SaveButton = Cast<UButton>(GetWidgetFromName(TEXT("btnSave")));
	SaveButton->OnClicked.AddDynamic(this, &ULSGameTitleWidget::OnSaveClicked);

}
