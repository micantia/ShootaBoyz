// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootaGameModeBase.h"
#include "Player/ShootaBaseCharacter.h"
#include "Player/ShootaPlayerController.h"

AShootaGameModeBase::AShootaGameModeBase() {
	DefaultPawnClass = AShootaBaseCharacter::StaticClass();
	PlayerControllerClass = AShootaPlayerController::StaticClass();
}