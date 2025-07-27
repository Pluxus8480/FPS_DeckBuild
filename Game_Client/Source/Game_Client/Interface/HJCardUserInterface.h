// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HJCardUserInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHJCardUserInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_CLIENT_API IHJCardUserInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UseCard(class UHJBaseCard* CardUsed) = 0;

	//virtual void Fire(float BaseDamage) = 0;
	//virtual void Discard(uint32 AmountDiscard) = 0;
	//TODO : 총구 위치나 크로스헤어 위치 받아올 수 있는 인터페이스
};
