// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HJGun.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogHJGun, Log, All);

UCLASS()
class GAME_CLIENT_API AHJGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHJGun();
    void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
    TObjectPtr<class UStaticMeshComponent> const GetMeshComponent() { return GunMeshComponent; }

 protected:
    // 총기 메쉬 (1인칭용)
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UStaticMeshComponent> GunMeshComponent;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    TObjectPtr <class UStaticMesh> GunMesh;

    UPROPERTY(EditAnywhere)
    FName GunTypeTag = TEXT("GunType");

    // 총구에서 이펙트와 탄환이 나가는 위치
    UPROPERTY(EditAnywhere)
    FName MuzzleSocketName = TEXT("MuzzleFlashSocket");

    // 이펙트 & 사운드
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UParticleSystem> GunEffect;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USoundBase> FireSound;

    AController* GetOwnerController() const;


};
