// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HJPlayerController.h"
#include "HJPlayerController.h"

void AHJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
