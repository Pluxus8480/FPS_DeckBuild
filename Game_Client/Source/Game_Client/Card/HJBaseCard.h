// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HJBaseCard.generated.h"

UENUM(BlueprintType)
enum class ECardType : uint8
{
	Fire = 0,
	Util,
	Joker,
};

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJBaseCard : public UObject
{
	GENERATED_BODY()
public:
	UHJBaseCard();

public:
	virtual void InitFromData(class UHJCardData* InCardData);
	
	virtual void Use();
	FName GetName() const;
	const class UHJCardData* GetCardData() { return CardData; };



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	ECardType Type;

	UPROPERTY()
	TObjectPtr<class UHJCardData> CardData;
};
