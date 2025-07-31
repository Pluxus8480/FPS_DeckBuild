// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HJInteractionWidget.h"
#include "Components/EditableTextBox.h"

UHJInteractionWidget::UHJInteractionWidget(const FObjectInitializer& ObjectInitializer):
	UUserWidget(ObjectInitializer)
{
}

void UHJInteractionWidget::NativeConstruct()
{
	Key = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Txt_Key")));
	ensure(Key);

}

void UHJInteractionWidget::UpdateInteractionKey(FKey NewKey)
{
	Key->SetText(FText::FromString(NewKey.ToString()));
}
