// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HJInteractorComponent.h"
#include "Interface/HJInteractableInterface.h"
#include "Collision/HJCollision.h"
#include "GameFramework/Character.h"
#include "Game_Client.h"

// Sets default values for this component's properties
UHJInteractorComponent::UHJInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHJInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHJInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	PerformLineTrace();
}

void UHJInteractorComponent::TryInteract()
{
	if (FocusedActor)
	{
		IHJInteractableInterface* InteractableActor = CastChecked<IHJInteractableInterface>(FocusedActor);
		InteractableActor->ExecuteInteract(GetOwner());
	}
}

void UHJInteractorComponent::PerformLineTrace()
{
	FVector Start;
	FRotator Rot;
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		HJ_SUBLOG(LogHJDefault, Log, TEXT("%s"), TEXT("Failed"));
		return;
	}
	OwnerCharacter->GetController()->GetPlayerViewPoint(Start, Rot);
	FVector End = Start + Rot.Vector() * TraceDistance;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.27f);

	if (bHit && Hit.GetActor())
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor->Implements<UHJInteractableInterface>())
		{
			if (FocusedActor != HitActor)
			{
				// 이전 대상과 다르면 교체
				FocusedActor = HitActor;
				// TODO: 하이라이트 처리 (ex. Outline)
				HJ_SUBLOG(LogHJDefault, Log, TEXT("%s"), TEXT("Begin"));
			}
			return;
		}
	}

	// 감지 대상 없음
	FocusedActor = nullptr;
}
