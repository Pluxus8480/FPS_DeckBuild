// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/HJBaseCard.h"
#include "HJCardData.h"

UHJBaseCard::UHJBaseCard()
{
	Type = ECardType::Fire;
}

void UHJBaseCard::Use(TScriptInterface<class IHJCardUserInterface> CardUser)
{
}

FName UHJBaseCard::GetName() const
{
	return CardData->CardName;
}
