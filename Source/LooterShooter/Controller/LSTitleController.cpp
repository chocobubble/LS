// Fill out your copyright notice in the Description page of Project Settings.


#include "LSTitleController.h"
#include "LooterShooter/UI/LSGameTitleWidget.h"

ALSTitleController::ALSTitleController()
{
	static ConstructorHelpers::FClassFinder<ULSGameTitleWidget> UI_TITLE_C(TEXT("/Game/LS/UI/UI_Title.UI_Title_C"));
	if (UI_TITLE_C.Succeeded())
	{
		TitleWidgetClass = UI_TITLE_C.Class;
	}
	else
	{
		LSLOG(Warning, TEXT("Cannot find class finder"));
	}
}

void ALSTitleController::BeginPlay()
{
	Super::BeginPlay();

	/*GameTitleWidget = CreateWidget<ULSGameTitleWidget>(this, ULSGameTitleWidget::StaticClass());
	if (GameTitleWidget)
	{
		GameTitleWidget->AddToViewport(0);
	}*/

	if (TitleWidgetClass)
	{
		GameTitleWidget = CreateWidget<ULSGameTitleWidget>(this, TitleWidgetClass);
		if (GameTitleWidget)
		{
			GameTitleWidget->AddToViewport(0);
		}
		else
		{
			LSLOG(Warning, TEXT("Fail to Create Game Title Widget"));
		}
	}
	else
	{
		LSLOG(Warning, TEXT("Title Widget Class is null"));
	}
}
