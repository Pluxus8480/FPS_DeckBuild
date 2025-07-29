// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HJCardWidget.generated.h"


DECLARE_DELEGATE_OneParam(FOnCardWidgetClicked, class UHJCardWidget* /*Caller*/);

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
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void UpdateUIData(class UHJCardData* CardData);

public:
	FOnCardWidgetClicked OnClicked;

protected:
	UPROPERTY()
	TObjectPtr<class UEditableTextBox> CardName;
	UPROPERTY()
	TObjectPtr<class UMultiLineEditableTextBox> CardDescription;
	UPROPERTY()
	TObjectPtr<class UEditableTextBox> BasePower;
	UPROPERTY()
	TObjectPtr<class UEditableTextBox> BaseMultiplier;
	UPROPERTY()
	TObjectPtr<class UImage> Image_Card;
	

};
