// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HJCardWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Card/HJCardData.h"


UHJCardWidget::UHJCardWidget(const FObjectInitializer& ObjectInitializer):
	UUserWidget(ObjectInitializer)
{
}

void UHJCardWidget::NativeConstruct()
{
	CardName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TXT_CardName")));
	ensure(CardName);

	CardDescription = Cast<UTextBlock>(GetWidgetFromName(TEXT("TXT_CardDescription")));
	ensure(CardDescription);
	BasePower = Cast<UTextBlock>(GetWidgetFromName(TEXT("TXT_BasePower")));
	ensure(BasePower);
	BaseMultiplier = Cast<UTextBlock>(GetWidgetFromName(TEXT("TXT_BaseMultiplier")));
	ensure(BaseMultiplier);
	Image_Card = Cast<UImage>(GetWidgetFromName(TEXT("IMG_Image_Card")));
	ensure(Image_Card);



	BasePower->SetText(FText::FromString(TEXT("Test")));
}

void UHJCardWidget::UpdateUIData(UHJCardData* CardData)
{
	CardName->SetText(FText::FromName(CardData->CardName));
	CardDescription->SetText(FText::FromName(CardData->Description));
	BasePower->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int32)CardData->BasePower)));
	BaseMultiplier->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int32)CardData->BaseMultiplier)));

	UTexture2D* UIImage;
	if (!CardData->UIImage.IsValid())
	{
		UIImage = CardData->UIImage.LoadSynchronous();
	}
	else
	{
		UIImage = CardData->UIImage.Get();
	}
	Image_Card->SetBrushFromTexture(UIImage, false);
}
