// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "BattleWidget.h"

AMainPlayerController::AMainPlayerController()
{
	static ConstructorHelpers::FClassFinder<UBattleWidget> UI_BATTLE_C(TEXT("WidgetBlueprint'/Game/UI/UI_Battle.UI_Battle_C'"));
	if (UI_BATTLE_C.Succeeded())
	{
		BattleWidgetClass = UI_BATTLE_C.Class;
	}
}

void AMainPlayerController::BeginPlay()
{
	BattleWidget = CreateWidget<UBattleWidget>(this, BattleWidgetClass);
}

void AMainPlayerController::RunBattleState(bool IsBattle)
{
	if (IsBattle)
	{
		BattleWidget->AddToViewport();
	}
	else
	{

	}
}
