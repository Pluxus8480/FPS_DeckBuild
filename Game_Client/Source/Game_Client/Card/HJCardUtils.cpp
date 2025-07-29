// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/HJCardUtils.h"
#include "HJCardData.h"
#include "HJBaseCard.h"

UHJBaseCard* UHJCardUtils::CreateCard(UObject* Outer, UHJCardData* CardData)
{
	UHJBaseCard* NewCard = NewObject<UHJBaseCard>(Outer, CardData->CardClass);
	NewCard->InitFromData(CardData);
	return NewCard;
}
