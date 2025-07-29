// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HJCharacterAIInterface.generated.h"


DECLARE_DELEGATE(FHJCharacterAttackFinished)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHJCharacterAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_CLIENT_API IHJCharacterAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetAIAttackDelegate(const FHJCharacterAttackFinished& OnAttackFinishedDelegate) = 0;
	virtual void AttackByAI() = 0;
	virtual float GetAIDetectRange() = 0;
	virtual float GetAIAttackRange() = 0;
	virtual float GetAIAttackSpeed() = 0;
	virtual float GetAIPatrolRadius() = 0;
};
