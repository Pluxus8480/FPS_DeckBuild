// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HJInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHJInteractionWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateInteractionKey(FKey NewKey);


protected:
	UPROPERTY()
	TObjectPtr<class UEditableTextBox> Key;

};
