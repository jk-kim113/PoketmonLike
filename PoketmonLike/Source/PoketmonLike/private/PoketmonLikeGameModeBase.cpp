// Copyright Epic Games, Inc. All Rights Reserved.


#include "PoketmonLikeGameModeBase.h"
#include "MainPlayer.h"
#include "MainPlayerController.h"

APoketmonLikeGameModeBase::APoketmonLikeGameModeBase()
{
	DefaultPawnClass = AMainPlayer::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
}
