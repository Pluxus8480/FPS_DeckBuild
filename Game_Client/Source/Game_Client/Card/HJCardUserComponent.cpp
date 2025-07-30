// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/HJCardUserComponent.h"
#include "HJBaseCard.h"
#include "Interface/HJCardUserInterface.h"
#include "HJCardUtils.h"

// Sets default values for this component's properties
UHJCardUserComponent::UHJCardUserComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...

	CurrentDeck = 0;
	if (0 == Decks.Num())
	{
		Decks.Add({});
		CurrentTopDeckIndex.Add({});
	}
}


// Called when the game starts
void UHJCardUserComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

//void UHJCardUserComponent::Fire(float BaseDamage)
//{
//	//
//
//
//	++CurrentTopDeckIndex[CurrentDeck];
//}
//
//void UHJCardUserComponent::Discard(uint32 AmountDiscard)
//{
//	int32 CurrentDeckSize = Decks[CurrentDeck].Deck.Num();
//	int32 NextTopDeck = CurrentTopDeckIndex[CurrentDeck] + (int32)AmountDiscard;
//	if (NextTopDeck > CurrentDeckSize)
//	{
//		Shuffle(CurrentDeck);
//		NextTopDeck = 0;
//	}
//	CurrentTopDeckIndex[CurrentDeck] = NextTopDeck;
//}

void UHJCardUserComponent::UseCard()
{
	IHJCardUserInterface* CardUser = Cast<IHJCardUserInterface>(GetOwner());
	if (CardUser)
	{
		CardUser->UseCard(Decks[CurrentDeck].Deck[CurrentTopDeckIndex[CurrentDeck]]);
	}
	NextCard();
}

void UHJCardUserComponent::AddCard(UHJBaseCard* NewCard, int32 DeckToAdd)
{
	ensure(DeckToAdd < Decks.Num());
	Decks[DeckToAdd].Deck.Add(NewCard);
	OnDeckAdded.Broadcast(DeckToAdd, *NewCard);
}

void UHJCardUserComponent::AddCard(UHJCardData* NewCardData, int32 DeckToAdd)
{
	AddCard(UHJCardUtils::CreateCard(this, NewCardData), DeckToAdd);
}

void UHJCardUserComponent::RemoveCard(int32 DeckToRemove, int32 CardIndexToRemove)
{
	ensure(DeckToRemove < Decks.Num() );
	TArrayCard& Deck = Decks[DeckToRemove].Deck;
	ensure(CardIndexToRemove < Deck.Num());
	Deck.Swap(Deck.Num() - 1, CardIndexToRemove);
	FName RemovedCardName = Deck[Deck.Num() - 1]->GetName();
	Deck.Pop();
	OnDeckRemoved.Broadcast(DeckToRemove, RemovedCardName);
}

void UHJCardUserComponent::Shuffle(int32 DeckToShuffle)
{
	ensure(DeckToShuffle < Decks.Num());
	TArrayCard& Deck = Decks[DeckToShuffle].Deck;
	int32 DeckSize = Deck.Num();
	for (int32 i = 0; i < DeckSize; ++i)
	{
		Deck.Swap(i, FMath::Rand() % DeckSize);
	}
	if(DeckSize > 0) OnDeckShuffle.Broadcast(DeckToShuffle);
}

void UHJCardUserComponent::SetCurrentDeck(int32 newCurrentDeck)
{
	CurrentDeck = FMath::Clamp(newCurrentDeck, 0, Decks.Num());
}

void UHJCardUserComponent::NextCard()
{
	++CurrentTopDeckIndex[CurrentDeck];
	if (Decks[CurrentDeck].Deck.Num() <= CurrentTopDeckIndex[CurrentDeck])
	{
		Shuffle(CurrentDeck);
		CurrentTopDeckIndex[CurrentDeck] = 0;
	}
}



// Called every frame
//void UHJCardUserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

