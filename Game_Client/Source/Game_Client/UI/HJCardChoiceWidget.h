// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/HJCardUIInterface.h"
#include "HJCardChoiceWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJCardChoiceWidget : public UUserWidget, public IHJCardUIInterface
{
	GENERATED_BODY()
public:
	UHJCardChoiceWidget(const FObjectInitializer& ObjectInitializer);

public:
	void ClearCard();
	void AddCard(class UHJCardData* CardData);

public:
	UFUNCTION()
	void OnCardClicked(class UHJCardWidget* CardWidget);

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;



protected:
	UPROPERTY()
	TObjectPtr<class UHorizontalBox> CardBox;


protected:
	void UpdateEventCaller(class UHJCardWidget* CardWidget) override;
	UHJCardWidget* CardSelected = nullptr;


	UPROPERTY(EditAnywhere, Category = Data)
	TSubclassOf<UHJCardWidget> CardWidgetClass;

	TMap<UHJCardWidget*, UHJCardData*> CardDataMap;



};
