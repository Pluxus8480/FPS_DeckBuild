// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Card/HJBaseCard.h"
#include "HJCard_Fire.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJCard_Fire : public UHJBaseCard
{
	GENERATED_BODY()
public:
	UHJCard_Fire();
public:
	virtual void Use() override;
};
