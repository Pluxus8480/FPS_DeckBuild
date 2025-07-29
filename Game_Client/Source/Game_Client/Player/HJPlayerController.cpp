// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HJPlayerController.h"
#include "HJPlayerController.h"
#include "../UI/HJCrosshairWidget.h"

AHJPlayerController::AHJPlayerController()
{
	//static ConstructorHelpers::FClassFinder<UHJCrosshairWidget> HJHUDWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C"));
	static ConstructorHelpers::FClassFinder<UHJCrosshairWidget> HJHUDWidgetRef(TEXT("/Game/UI/WBP_Crosshair.WBP_Crosshair_C"));
	if (HJHUDWidgetRef.Class)
	{
		HJHUDWidgetClass = HJHUDWidgetRef.Class;
	}
}

void AHJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);


	HJHUDWidget = CreateWidget<UHJCrosshairWidget>(this, HJHUDWidgetClass);
	if (HJHUDWidget)
	{
		HJHUDWidget->AddToViewport();
	}
}
