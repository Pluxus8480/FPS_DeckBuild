// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HJCharacterPlayerTPS.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Animation/HJPlayerTPSAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

AHJCharacterPlayerTPS::AHJCharacterPlayerTPS()
{		
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Move
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/HJProject/Input/IMC_TPS.IMC_TPS'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRunRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Sprint.IA_Sprint'"));
	if (nullptr != InputActionRunRef.Object)
	{
		SprintAction = InputActionRunRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

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
}
void AHJCharacterPlayerTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector InputVec = GetLastMovementInputVector();
	// 입력 없을 때 스프린트 끄기
	if (bIsSprinting && InputVec.SizeSquared() < SprintStopThreshold * SprintStopThreshold)
	{
		bIsSprinting = false;
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
}

void AHJCharacterPlayerTPS::TPSLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AHJCharacterPlayerTPS::TPSToggleSprint()
{
	bIsSprinting = !bIsSprinting;

	if (bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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
