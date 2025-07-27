// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HJPlayerTPSAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UHJPlayerTPSAnimInstance::UHJPlayerTPSAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
}

void UHJPlayerTPSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UHJPlayerTPSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);


		if (!Owner)
			return;
		FVector MovementDir = Velocity.GetSafeNormal2D();
		FVector Forward = Owner->GetActorForwardVector();
		FVector Right = Owner->GetActorRightVector();


		float ForwardDot = FVector::DotProduct(MovementDir, Forward);
		float RightDot = FVector::DotProduct(MovementDir, Right);

		if (ForwardDot > 0.6f)
			MoveDirection = EPlayerMoveDirection::Forward;
		else if (ForwardDot < -0.7f)
			MoveDirection = EPlayerMoveDirection::Backward;
		else if (RightDot > 0.1f)
			MoveDirection = EPlayerMoveDirection::Right;
		else if (RightDot < -0.1f)
			MoveDirection = EPlayerMoveDirection::Left;
		else
			MoveDirection = EPlayerMoveDirection::None;
	}
}
