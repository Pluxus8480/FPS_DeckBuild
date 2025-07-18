// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HJGunData.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API UHJGunData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("HJGunData", GetFName());
	}

public:

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<USkeletalMesh> PlayerMesh;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class UAnimInstance> PlayerAnimInstance;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<class UAnimMontage> GunFireMontage;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class AHJGun> GunClass;


};
