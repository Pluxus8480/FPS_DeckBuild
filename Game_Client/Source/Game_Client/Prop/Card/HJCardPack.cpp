// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Card/HJCardPack.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Collision/HJCollision.h"

// Sets default values
AHJCardPack::AHJCardPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_HJTRIGGER);
	Trigger->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AHJCardPack::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHJCardPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AHJCardPack::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
//void AHJCardPack::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

