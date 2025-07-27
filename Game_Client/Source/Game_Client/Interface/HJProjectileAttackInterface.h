// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HJProjectileAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHJProjectileAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_CLIENT_API IHJProjectileAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void FireProjectile() = 0;
	virtual TSubclassOf<class AHJProjectile> GetCurrentProjectile() const = 0;
};
