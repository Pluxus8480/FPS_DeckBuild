// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HJCharacterPlayerTPS.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Animation/HJPlayerTPSAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Projectile/HJProjectile.h"
#include "Card/HJCardUserComponent.h"
#include "../Card/HJBaseCard.h"
#include "../Card/HJCardData.h"
#include "../Projectile/HJAttackObject.h"
#include "Interface/HJLockonAbleTargetInterface.h"
#include "../UI/HJCrosshairWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"  // 꼭 있어야 합니다!

DEFINE_LOG_CATEGORY(LogHJCharacterPlayerTPS);
AHJCharacterPlayerTPS::AHJCharacterPlayerTPS()
{		
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Move
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// UI
	static ConstructorHelpers::FClassFinder<UHJCrosshairWidget> HJHUDWidgetRef(TEXT("/Game/UI/WBP_Crosshair.WBP_Crosshair_C"));
	if (HJHUDWidgetRef.Class)
	{
		HJCrosshairWidgetClass = HJHUDWidgetRef.Class;
	}

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/HJProject/Input/IMC_TPS.IMC_TPS'"));
	if (nullptr != InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
		JumpAction = InputActionJumpRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRunRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Sprint.IA_Sprint'"));
	if (nullptr != InputActionRunRef.Object)

		SprintAction = InputActionRunRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Attack.IA_Attack'"));
	if (nullptr != AttackActionMoveRef.Object)
		AttackAction = AttackActionMoveRef.Object;


	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef(TEXT("/Game/HJProject/Animation/MagicianPlayer/AM_Magic_Attack_1.AM_Magic_Attack_1"));
	if (nullptr != AttackMontageRef.Object)
		AttackMontage = AttackMontageRef.Object;

	//CardUser
	CardUser = CreateDefaultSubobject<UHJCardUserComponent>(TEXT("CardUser"));
}
void AHJCharacterPlayerTPS::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC && HJCrosshairWidgetClass)
	{
		HJCrosshiarWidget = CreateWidget<UHJCrosshairWidget>(PC, HJCrosshairWidgetClass);
		if (HJCrosshiarWidget)
		{
			HJCrosshiarWidget->AddToViewport();
		}
	}

}
void AHJCharacterPlayerTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCrosshairTarget();
	FVector InputVec = GetLastMovementInputVector();
	// 입력 없을 때 스프린트 끄기
	if (CurrnetMovementType == EPlayerState::SPRINT && InputVec.SizeSquared() < SprintStopThreshold * SprintStopThreshold)
	{
		CurrnetMovementType = EPlayerState::WALK_FRONT;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	if(InputVec.SizeSquared() < SprintStopThreshold * SprintStopThreshold)
		CheckKeyInput(false);
	else
		CheckKeyInput(true);
}
void AHJCharacterPlayerTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayerTPS::TPSMove);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayerTPS::TPSLook);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayerTPS::TPSToggleSprint);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayerTPS::TPSAttack);
}

void AHJCharacterPlayerTPS::FireProjectile()
{
	UWorld* World = Owner->GetWorld();
	if (!World) return;
	// 소켓 위치
	FVector ProjectileLocation = GetMesh()->GetSocketLocation("MagicAttack1Socket");
	FRotator ProjectileRotation = GetMesh()->GetSocketRotation("MagicAttack1Socket");

	// 투사체 스폰
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Owner->GetInstigator();


	if (CurrentProjectile)
	{
		AHJProjectile* Projectile = World->SpawnActor<AHJProjectile>(
			CurrentProjectile,
			ProjectileLocation,
			ProjectileRotation,
			SpawnParams
		);

		// 발사 방향 세팅
		if (Projectile)
		{
			//FVector Direction = FollowCamera->GetForwardVector();
			//FVector FireDirection = ProjectileRotation.Vector();
			Projectile->FireInDirection(AimDirection);
			
		}
	}
	CurrentProjectile = nullptr;
}

void AHJCharacterPlayerTPS::TPSMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

	// 방향 분석
	FVector MovementInput = ForwardDirection * MovementVector.X + RightDirection * MovementVector.Y;

	if (MovementInput.IsNearlyZero())
	{
		SetMovementState(EPlayerState::WALK_FRONT);
	}
	else 
	{
		FVector InputDir = MovementInput.GetSafeNormal();
		float ForwardDot = FVector::DotProduct(InputDir, GetActorForwardVector());
		float RightDot = FVector::DotProduct(InputDir, GetActorRightVector());

		if (ForwardDot > 0.7f && CurrnetMovementType != EPlayerState::SPRINT)
		{
			SetMovementDirection(EPlayerMovementDirection::WALK_F);
			SetMovementState(EPlayerState::WALK_FRONT);
		}
		else if (ForwardDot < -0.7f)
		{
			SetMovementDirection(EPlayerMovementDirection::WALK_B);
			SetMovementState(EPlayerState::SIDEWALK);
		}
		else if (RightDot > 0.1f)
		{
			SetMovementDirection(EPlayerMovementDirection::WALK_R);
			SetMovementState(EPlayerState::SIDEWALK);
		}
		else if (RightDot < -0.1f)
		{
			SetMovementDirection(EPlayerMovementDirection::WALK_L);
			SetMovementState(EPlayerState::SIDEWALK);
		}
	}
}

void AHJCharacterPlayerTPS::TPSLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AHJCharacterPlayerTPS::TPSToggleSprint()
{
	if (CurrnetMovementType == EPlayerState::SPRINT)
	{
		SetMovementState(EPlayerState::WALK_FRONT);
	}
	else if (CurrnetMovementType == EPlayerState::SIDEWALK)
	{
		
	}
	else if(CurrnetMovementType != EPlayerState::SPRINT)
	{
		SetMovementState(EPlayerState::SPRINT);
	}
}

void AHJCharacterPlayerTPS::TPSAttack(const FInputActionValue& Value)
{

	if (AttackMontage)
	{
	/*UE_LOG(LogHJCharacterPlayerTPS, Warning, TEXT("Montage In Call"));*/
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(AttackMontage))
		{
		/*	UE_LOG(LogHJCharacterPlayerTPS, Warning, TEXT("Montage Play"));*/
			AnimInstance->Montage_Play(AttackMontage);
		}
	}
}

void AHJCharacterPlayerTPS::CheckKeyInput(bool IsInput)
{
	UHJPlayerTPSAnimInstance* Anim = Cast<UHJPlayerTPSAnimInstance>(GetMesh()->GetAnimInstance());
	if (Anim)
	{
		Anim->SetKeyInput(IsInput);
	}
}

void AHJCharacterPlayerTPS::SetMovementState(EPlayerState NewType)
{
	CurrnetMovementType = NewType;

	switch (NewType)
	{
	case EPlayerState::WALK_FRONT:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;
	case EPlayerState::SPRINT:
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		break;
	case EPlayerState::SIDEWALK:
		GetCharacterMovement()->MaxWalkSpeed = SideWalkSpeed;
		break;
	}
}

void AHJCharacterPlayerTPS::SetMovementDirection(EPlayerMovementDirection NewType)
{
	CurrnetMovementDirection = NewType;
	
}

void AHJCharacterPlayerTPS::UpdateCrosshairTarget()
{
	FVector Start = FollowCamera->GetComponentLocation();
	FVector ForwardVector = FollowCamera->GetForwardVector();
	FVector End = Start + (ForwardVector * 5000.f); // 길이는 필요에 따라 조절

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Hit,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(15.f),
		Params
	);
	FVector2D ScreenPos;
	if (bHit && Hit.GetActor()->Implements<UHJLockonAbleTargetInterface>())
	{

		AActor* TargetActor = Hit.GetActor();
		APlayerController* PC = Cast<APlayerController>(GetController());

		if (TargetActor && PC)
		{
			// 액터의 바운딩 박스 중심 구하기
			FVector Origin;
			FVector BoxExtent;
			TargetActor->GetActorBounds(true, Origin, BoxExtent);
			
			// 중심 위치를 스크린 좌표로 변환
			if (PC->ProjectWorldLocationToScreen(Origin, ScreenPos, true))
			{
				AimDirection = (Origin - Start).GetSafeNormal();
				HJCrosshiarWidget->SetCrosshairPosition(ScreenPos);
			}
		}
	}
	else
	{
		AimDirection = FollowCamera->GetForwardVector();
		HJCrosshiarWidget->ResetCrossharPosition();
	}
}

void AHJCharacterPlayerTPS::UseCard(UHJBaseCard* CardUsed)
{
	
	TSubclassOf<AHJAttackObject> AttackObject =  CardUsed->GetCardData()->AttackObject;
	ECardTypeData CardType =  CardUsed->GetCardData()->CardTypeData;
	if (AttackObject)
	{
		switch (CardType)
		{
		case ECardTypeData::Projectile:
		{
			TSubclassOf<AHJProjectile> ProjectileClass = Cast<UClass>(AttackObject);
			CurrentProjectile = ProjectileClass;
			FireProjectile();
			break;
		}
		case ECardTypeData::Slash:
			break;
		default:
			break;
		}
	}
}

UHJCardUserComponent* AHJCharacterPlayerTPS::GetCardUser()
{
	return CardUser;
}

void AHJCharacterPlayerTPS::TryAddCard(UHJCardData* CardData)
{
	CardUser->AddCard(CardData, 0);
}
