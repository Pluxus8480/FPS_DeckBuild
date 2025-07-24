// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HJAIController_Monster.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API AHJAIController_Monster : public AAIController
{
	GENERATED_BODY()
public:
	AHJAIController_Monster();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void SetupBlackBoard(class IHJCharacterAIInterface* AIPawn);

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
