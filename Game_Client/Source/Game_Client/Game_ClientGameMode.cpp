// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game_ClientGameMode.h"
#include "Game_ClientCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGame_ClientGameMode::AGame_ClientGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
