// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HJGameMode.h"
#include "HJGameMode.h"

AHJGameMode::AHJGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/Game_Client.HJPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
