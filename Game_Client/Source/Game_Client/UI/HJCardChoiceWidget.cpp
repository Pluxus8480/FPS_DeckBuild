// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HJCardChoiceWidget.h"
#include "HJCardWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"


UHJCardChoiceWidget::UHJCardChoiceWidget(const FObjectInitializer& ObjectInitializer):
	UUserWidget(ObjectInitializer)
{
}

void UHJCardChoiceWidget::NativeConstruct()
{
	//
	CardBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("Card_Box")));
	ensure(CardBox);
}

void UHJCardChoiceWidget::ClearCard()
{
	CardBox->ClearChildren();
}

void UHJCardChoiceWidget::AddCard(class UHJCardWidget* Card)
{
	UHorizontalBoxSlot* CardSlot = CardBox->AddChildToHorizontalBox(Card);

	CardSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); // Make the button fill available space
	CardSlot->SetPadding(FMargin(5.f)); // Add some padding
	CardSlot->SetHorizontalAlignment(HAlign_Center);
	CardSlot->SetVerticalAlignment(VAlign_Center);
}
