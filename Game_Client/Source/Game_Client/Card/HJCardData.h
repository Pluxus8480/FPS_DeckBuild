// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HJCardData.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJCardData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = UI)
	TSoftObjectPtr<UTexture2D> UIImage;

	UPROPERTY(EditAnywhere, Category = UI)
	FName Description;
};
