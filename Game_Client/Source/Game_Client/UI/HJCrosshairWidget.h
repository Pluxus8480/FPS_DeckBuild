// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HJCrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void SetCrosshairPosition(const FVector2D& ScreenPosition);
	void ResetCrossharPosition();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CrosshairImage;

private:
	FVector2D ViewportCenterOffset = {};

};
