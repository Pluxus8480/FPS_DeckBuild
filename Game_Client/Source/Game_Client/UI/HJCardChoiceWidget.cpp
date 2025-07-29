// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HJCardChoiceWidget.h"
#include "HJCardWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Interface/HJCardUserInterface.h"
#include "Card/HJCardData.h"

UHJCardChoiceWidget::UHJCardChoiceWidget(const FObjectInitializer& ObjectInitializer):
	UUserWidget(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UHJCardWidget> CardWidgetClassRef(TEXT("/Game/UI/WBP_Card.WBP_Card_C"));
	if (CardWidgetClassRef.Class)
		CardWidgetClass = CardWidgetClassRef.Class;
}

void UHJCardChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//
	CardBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("Card_Box")));
	ensure(CardBox);
}

FReply UHJCardChoiceWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if(PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
	RemoveFromParent();
	return FReply::Handled();
}

void UHJCardChoiceWidget::ClearCard()
{
	CardBox->ClearChildren();
	CardDataMap.Reset();
	CardDataMap.Shrink();
}

void UHJCardChoiceWidget::AddCard(class UHJCardData* CardData)
{
	UHJCardWidget* NewCard = CreateWidget<UHJCardWidget>(this, CardWidgetClass);
	CardDataMap.Add(NewCard, CardData);

	UHorizontalBoxSlot* CardSlot = CardBox->AddChildToHorizontalBox(NewCard);

	CardSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); // Make the button fill available space
	CardSlot->SetPadding(FMargin(5.f)); // Add some padding
	CardSlot->SetHorizontalAlignment(HAlign_Center);
	CardSlot->SetVerticalAlignment(VAlign_Center);
	NewCard->UpdateUIData(CardData);
	NewCard->OnClicked.BindUObject(this, &UHJCardChoiceWidget::OnCardClicked);
}

void UHJCardChoiceWidget::OnCardClicked(UHJCardWidget* CardWidget)
{
	if (CardWidget)
	{
		UHJCardData** CardDataPtr = CardDataMap.Find(CardWidget);
		if (CardDataPtr)
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController)
			{
				IHJCardUserInterface* Player = Cast<IHJCardUserInterface>(PlayerController->GetPawn());
				if (Player)
				{
					Player->TryAddCard(*CardDataPtr);
				}

			}

			CardWidget = nullptr;
		}
	}
}

void UHJCardChoiceWidget::UpdateEventCaller(UHJCardWidget* CardWidget)
{
	CardSelected = CardWidget;
}

