// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HJCharacterBase.h"
#include "Interface/HJCharacterAIInterface.h"
#include "HJCharacterMonster.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API AHJCharacterMonster : public AHJCharacterBase, public IHJCharacterAIInterface
{
	GENERATED_BODY()
	
public:
	AHJCharacterMonster();



//AIInterface Section
public:
	void SetAIAttackDelegate(const FHJCharacterAttackFinished& OnAttackFinishedDelegate) override;
	void AttackByAI() override;
	float GetAIDetectRange() override;
	float GetAIAttackRange() override;
	float GetAIAttackSpeed() override;
	float GetAIPatrolRadius() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float DetectRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float PatrolRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float Attack;

	FHJCharacterAttackFinished OnAttackFinished;

protected:
	void AttackSweep();



};
