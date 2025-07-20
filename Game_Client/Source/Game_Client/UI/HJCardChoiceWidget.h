// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HJCardChoiceWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJCardChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHJCardChoiceWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	void ClearCard();
	void AddCard(class UHJCardWidget* Card);

protected:
	UPROPERTY()
	TObjectPtr<class UHorizontalBox> CardBox;

};
