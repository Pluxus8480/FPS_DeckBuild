// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HJCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJCardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHJCardWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UTextBlock> CardName;
	UPROPERTY()
	TObjectPtr<class UTextBlock> CardDescription;
	UPROPERTY()
	TObjectPtr<class UTextBlock> BasePower;
	UPROPERTY()
	TObjectPtr<class UTextBlock> BaseMultiplier;
	UPROPERTY()
	TObjectPtr<class UImage> Image_Card;
	
};
