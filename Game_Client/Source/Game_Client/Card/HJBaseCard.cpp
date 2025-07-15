// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/HJBaseCard.h"

UHJBaseCard::UHJBaseCard()
{
	Type = ECardType::Fire;
}

void UHJBaseCard::Use(TScriptInterface<class IHJCardUserInterface> CardUser)
{
}
