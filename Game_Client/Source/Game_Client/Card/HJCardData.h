// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HJCardData.generated.h"

/**
 * 
 */
UENUM()
enum class ECardTypeData : uint8
{
	Projectile = 0,
	Slash,
};


UCLASS()
class GAME_CLIENT_API UHJCardData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("HJCardData", GetFName());
	}
	
public:
	UPROPERTY(EditAnywhere, Category = UI)
	TSoftObjectPtr<UTexture2D> UIImage;

	UPROPERTY(EditAnywhere, Category = UI)
	FName CardName;
	UPROPERTY(EditAnywhere, Category = UI)
	FName Description;
	UPROPERTY(EditAnywhere, Category = UI)
	FName FlavorText;

	UPROPERTY(EditAnywhere, Category = Stat)
	float BasePower;

	UPROPERTY(EditAnywhere, Category = Stat)
	float BaseMultiplier;

	UPROPERTY(EditAnywhere, Category = Stat)
	float BaseCastSpeed;

	UPROPERTY(EditAnywhere, Category = Character)
	FName MotionTag;

	UPROPERTY(EditAnywhere, Category = CardType)
	ECardTypeData CardTypeData;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, Category = Effect)
	TSubclassOf<class AHJAttackObject> AttackObject;


	UPROPERTY(EditAnywhere, Category = Effect)
	TSoftObjectPtr<class UNiagaraSystem> Effect;
	UPROPERTY(EditAnywhere, Category = Effect)
	TSoftObjectPtr<class UNiagaraSystem> DisappearingEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CardClass)
	TSubclassOf<class UHJBaseCard> CardClass;
};
