// Copyright Epic Games, Inc. All Rights Reserved.


#include "PoketmonLikeGameModeBase.h"
#include "MainPlayer.h"

APoketmonLikeGameModeBase::APoketmonLikeGameModeBase()
{
	DefaultPawnClass = AMainPlayer::StaticClass();
}
