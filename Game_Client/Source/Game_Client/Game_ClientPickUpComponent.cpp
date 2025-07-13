// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game_ClientPickUpComponent.h"

UGame_ClientPickUpComponent::UGame_ClientPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UGame_ClientPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UGame_ClientPickUpComponent::OnSphereBeginOverlap);
}

void UGame_ClientPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AGame_ClientCharacter* Character = Cast<AGame_ClientCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
