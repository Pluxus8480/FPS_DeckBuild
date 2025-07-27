// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RotateToTarget.h"
#include "HJAI.h"
#include "Interface/HJCharacterAIInterface.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"


UBTTask_RotateToTarget::UBTTask_RotateToTarget()
{
}

EBTNodeResult::Type UBTTask_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ACharacter* Target = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}
	FVector Location = ControllingPawn->GetActorLocation();
	FVector ForwardVector = ControllingPawn->GetActorForwardVector();
	FVector TargetLocation = Target->GetActorLocation();
	FVector TargetVector = TargetLocation - Location;
	TargetVector.Z = 0.f;
	TargetVector.Normalize();

	FRotator CurrRotator = ControllingPawn->GetActorRotation();
	FRotator NewRotator = FRotationMatrix::MakeFromX(TargetVector).Rotator();
	ControllingPawn->SetActorRotation(FMath::RInterpTo(CurrRotator, NewRotator, GetWorld()->GetDeltaSeconds(), 2.f));

	return  EBTNodeResult::Succeeded;
}
