// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HJCardUtils.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJCardUtils : public UObject
{
	GENERATED_BODY()
	
public:
	static class UHJBaseCard* CreateCard(UObject* Outer, class UHJCardData* CardData);
};
