// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/HJBaseCard.h"
#include "HJCardData.h"

UHJBaseCard::UHJBaseCard()
{
	Type = ECardType::Fire;
}

void UHJBaseCard::InitFromData(UHJCardData* InCardData)
{
	CardData = InCardData;
}

void UHJBaseCard::Use()
{
}

FName UHJBaseCard::GetName() const
{
	return CardData->CardName;
}
