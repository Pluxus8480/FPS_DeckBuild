// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HJInteractorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_CLIENT_API UHJInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHJInteractorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 인터랙션 키 바인딩
	UFUNCTION()
	void TryInteract();

protected:
	// 감지된 대상
	UPROPERTY()
	AActor* FocusedActor;

	// 감지 및 하이라이트 처리
	void PerformLineTrace();

	// 감지 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", Meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 500.f;


};
