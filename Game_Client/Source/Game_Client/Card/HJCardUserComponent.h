// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/HJCardUserInterface.h"
#include "HJCardUserComponent.generated.h"

class UHJBaseCard;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDeckAddedDelegate,     int32/*Deck*/, const UHJBaseCard&/*CardAdded*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDeckRemovedDelegate,   int32/*Deck*/, FName/*CardRemoved*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeckShuffleDelegate,    int32/*Deck*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTopDeckChangedDelegate, int32/*TopDeck*/);

USTRUCT(BlueprintType)
struct GAME_CLIENT_API FCardArray {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(Transient)
	TArray<TObjectPtr<class UHJBaseCard>> Deck;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_CLIENT_API UHJCardUserComponent : public UActorComponent, public IHJCardUserInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHJCardUserComponent();

	using TArrayCard = TArray<TObjectPtr<class UHJBaseCard>>;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Deck Control Section
public:
	void AddCard(TObjectPtr<class UHJBaseCard> NewCard, int32 DeckToAdd);
	void RemoveCard(int32 DeckToRemove, int32 CardIndexToRemove);
	void Shuffle(int32 DeckToShuffle);

	void SetCurrentDeck(int32 newCurrentDeck);
	int32 GetCurrentDeck()const { return CurrentDeck; }

protected:
	UPROPERTY(Transient)
	TArray<FCardArray> Decks;
	UPROPERTY(Transient)
	TArray<int32> CurrentTopDeckIndex;

	UPROPERTY(Transient)
	int32 CurrentDeck;
	//CardUserInterface Section
public:
	virtual void Fire(float BaseDamage) override;
	virtual void Discard(uint32 AmountDiscard) override;




	//Delegate Section
public:
	FOnDeckAddedDelegate OnDeckAdded;
	FOnDeckRemovedDelegate OnDeckRemoved;
	FOnDeckShuffleDelegate OnDeckShuffle;
		
};
