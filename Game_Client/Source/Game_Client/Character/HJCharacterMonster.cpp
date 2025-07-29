// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HJCharacterMonster.h"
#include "Components/CapsuleComponent.h"
#include "Collision/HJCollision.h"
#include "Engine/DamageEvents.h"
#include "AI/HJAIController_Monster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Card/HJCardUserComponent.h"
#include "Card/HJBaseCard.h"
#include "Card/HJCardData.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h" 


AHJCharacterMonster::AHJCharacterMonster()
{
	bUseControllerRotationYaw = false;

	AIControllerClass = AHJAIController_Monster::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	DetectRange = 800.f;
	AttackRange = 250.f;
	AttackSpeed = 1.f;
	PatrolRadius = 1000.f;
	Attack = 1.f;
	GetCharacterMovement()->RotationRate = FRotator(360.0f, 360.0f, 360.0f);
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/HJProject/Animation/Monster/ABP_Monster.ABP_Monster_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageClassRef(TEXT("/Script/Engine.AnimMontage'/Game/HJProject/Animation/Monster/AM_MonsterAttack.AM_MonsterAttack'"));
	if (AttackMontageClassRef.Object)
	{
		AttackMontage = AttackMontageClassRef.Object;
	}

	CardUser = CreateDefaultSubobject<UHJCardUserComponent>(TEXT("CardUser"));

}

void AHJCharacterMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AHJCharacterMonster::AttackFinished);
}

void AHJCharacterMonster::UseCard(UHJBaseCard* CardUsed)
{
	const UHJCardData* CardData = CardUsed->GetCardData();
	if (!CardData->Effect.IsValid())
	{
		CardData->Effect.LoadSynchronous();
	}
	UNiagaraSystem* CardEffect = CardData->Effect.Get();
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		CardEffect,                          // NiagaraSystem*
		GetMesh(),                           // USceneComponent* AttachToComponent
		TEXT("RightHand"),                   // FName AttachPointName (소켓 이름)
		FVector::ZeroVector,                 // Location offset
		FRotator::ZeroRotator,              // Rotation offset
		EAttachLocation::SnapToTarget,      // AttachLocationType
		true                                // bAutoDestroy
	);

}

UHJCardUserComponent* AHJCharacterMonster::GetCardUser()
{
	return CardUser;
}

void AHJCharacterMonster::TryAddCard(UHJCardData* CardData)
{
	
}


void AHJCharacterMonster::SetAIAttackDelegate(const FHJCharacterAttackFinished& OnAttackFinishedDelegate)
{	
	OnAttackFinished = OnAttackFinishedDelegate;
}

void AHJCharacterMonster::AttackByAI()
{
	GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AHJCharacterMonster::AttackFinished);

	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate, AttackMontage);
	AttackSweep();
}

float AHJCharacterMonster::GetAIDetectRange()
{
	return DetectRange;
}

float AHJCharacterMonster::GetAIAttackRange()
{
	return AttackRange;
}

float AHJCharacterMonster::GetAIAttackSpeed()
{
	return AttackSpeed;
}

float AHJCharacterMonster::GetAIPatrolRadius()
{
	return PatrolRadius;
}

void AHJCharacterMonster::AttackFinished(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	OnAttackFinished.ExecuteIfBound();
}

void AHJCharacterMonster::AttackSweep()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	//const float AttackRange = GetAIAttackRange();
	const float AttackRadius = 50.f;
	const float AttackDamage = Attack;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_HJACTION, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}
