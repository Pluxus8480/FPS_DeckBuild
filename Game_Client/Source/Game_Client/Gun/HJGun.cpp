// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/HJGun.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "../Character/HJCharacterPlayer.h"


DEFINE_LOG_CATEGORY(LogHJGun);

// Sets default values
AHJGun::AHJGun()
{
    PrimaryActorTick.bCanEverTick = false;

    GunMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    RootComponent = GunMeshComponent;

}

// Called when the game starts or when spawned
void AHJGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHJGun::Fire()
{

 

    // 이펙트 및 사운드
    if (GunEffect)
        UGameplayStatics::SpawnEmitterAttached(GunEffect, GunMeshComponent, MuzzleSocketName);

    if (FireSound)
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

    AHJCharacterPlayer* OwnerCharacter = Cast<AHJCharacterPlayer>(GetOwner());
    if (OwnerCharacter)
    {
   /*     UE_LOG(LogHJGun, Warning, TEXT("Gun Fired"));*/
        OwnerCharacter->PlayFireMontage();
    }
}

AController* AHJGun::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr) return nullptr;

    return OwnerPawn->GetController();
}
