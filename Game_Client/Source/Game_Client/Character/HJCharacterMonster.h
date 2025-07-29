// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HJCharacterBase.h"
#include "Interface/HJCharacterAIInterface.h"
#include "Interface/HJCardUserInterface.h"
#include "HJCharacterMonster.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API AHJCharacterMonster : public AHJCharacterBase, public IHJCharacterAIInterface, public IHJCardUserInterface
{
	GENERATED_BODY()
	
public:
	AHJCharacterMonster();

protected:
	virtual void PostInitializeComponents() override;

//CardUserInterface Section
public:
	virtual void UseCard(class UHJBaseCard* CardUsed) override;
	virtual class UHJCardUserComponent* GetCardUser() override;
	virtual void TryAddCard(class UHJCardData* CardData) override;
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

protected:
	FHJCharacterAttackFinished OnAttackFinished;
	void AttackFinished(UAnimMontage* TargetMontage, bool IsProperlyEnded);

protected:
	void AttackSweep();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Card, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHJCardUserComponent> CardUser;

};
