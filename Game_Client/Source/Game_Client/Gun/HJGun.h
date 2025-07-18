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
    // �ѱ� �޽� (1��Ī��)
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UStaticMeshComponent> GunMeshComponent;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    TObjectPtr <class UStaticMesh> GunMesh;

    UPROPERTY(EditAnywhere)
    FName GunTypeTag = TEXT("GunType");

    // �ѱ����� ����Ʈ�� źȯ�� ������ ��ġ
    UPROPERTY(EditAnywhere)
    FName MuzzleSocketName = TEXT("MuzzleFlashSocket");

    // ����Ʈ & ����
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UParticleSystem> GunEffect;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USoundBase> FireSound;

    AController* GetOwnerController() const;


};
