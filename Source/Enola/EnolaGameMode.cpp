// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "EnolaGameMode.h"
#include "EnolaHUD.h"
#include "EnolaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnolaGameMode::AEnolaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEnolaHUD::StaticClass();
}
