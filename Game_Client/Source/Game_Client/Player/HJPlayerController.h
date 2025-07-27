// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HJPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API AHJPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	AHJPlayerController();
protected:
	virtual void BeginPlay() override;

// HUD Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UHJCrosshairWidget> HJHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UHJCrosshairWidget> HJHUDWidget;
};
