// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HJCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Gun/HJGun.h"
#include "../Gun/HJGunData.h"

DEFINE_LOG_CATEGORY(LogHJCharacterPlayer);
AHJCharacterPlayer::AHJCharacterPlayer()
{

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(FirstPersonCameraComponent);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	GetMesh()->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Move
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;


	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/HJProject/Input/IMC_Default.IMC_Default'"));
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
		RunAction = InputActionRunRef.Object;
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
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShootRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HJProject/Input/Actions/IA_Shoot.IA_Shoot'"));
	if (nullptr != InputActionShootRef.Object)
	{
		ShootAction = InputActionShootRef.Object;
	}

	// Weapon Component
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> RifleMeshRef(
	//	TEXT("/Game/Weapons_Free/Meshes/SM_rifle_001.SM_rifle_001")
	//);
	//if (RifleMeshRef.Succeeded())
	//{
	//	//UE_LOG(LogHJCharacterPlayer, Warning, TEXT("Rifle Equiped"));
	//	Weapon->SetStaticMesh(RifleMeshRef.Object);
	//}
}
void AHJCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 입력 없을 때 스프린트 끄기
	if (bIsSprinting && LastInputVector.SizeSquared() < SprintStopThreshold * SprintStopThreshold)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	// 입력은 한 번만 쓴 뒤 초기화
	LastInputVector = FVector2D::ZeroVector;
}
void AHJCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>((PlayerController->GetLocalPlayer())))
	{

		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	EquipGun(GunDataAsset);

}

void AHJCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayer::FPSMove);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayer::FPSLook);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayer::FPSToggleSprint);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AHJCharacterPlayer::OnFire);

}

void AHJCharacterPlayer::FPSMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

	LastInputVector = MovementVector;
}

void AHJCharacterPlayer::FPSLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AHJCharacterPlayer::OnFire()
{	
	if (Gun)
	{
		Gun->Fire();
	}
}

void AHJCharacterPlayer::FPSToggleSprint()
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



void AHJCharacterPlayer::EquipGun(TObjectPtr<class UHJGunData> AGunData)
{
	if (AGunData)
	{
		// 데이터 입력 구간
		if (AGunData->PlayerMesh.IsPending())
			AGunData->PlayerMesh.LoadSynchronous();

		GetMesh()->SetSkeletalMesh(AGunData->PlayerMesh.Get());
		GetMesh()->SetAnimInstanceClass(AGunData->PlayerAnimInstance);


		AHJGun* DefaultGun = AGunData->GunClass->GetDefaultObject<AHJGun>();

		if(DefaultGun->GetGunTypeNameTag() == "Rifle")
			Weapon->SetupAttachment(GetMesh(), TEXT("RifleSocket"));
		else if(DefaultGun->GetGunTypeNameTag() == "Pistol")
			Weapon->SetupAttachment(GetMesh(), TEXT("PistolSocket"));


		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;


		AHJGun* SpawnedGun = GetWorld()->SpawnActor<AHJGun>(AGunData->GunClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (SpawnedGun)
		{
			if (DefaultGun->GetGunTypeNameTag() == "Rifle")
				SpawnedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RifleSocket"));
			else if (DefaultGun->GetGunTypeNameTag() == "Pistol")
				SpawnedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("PistolSocket"));

			Gun = SpawnedGun;

			FireMontage = AGunData->GunFireMontage;

		}

	}
}

void AHJCharacterPlayer::PlayFireMontage()
{
	if (FireMontage)
	{
		//UE_LOG(LogHJCharacterPlayer, Warning, TEXT("Fire Montage"));
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance/* && !AnimInstance->Montage_IsPlaying(FireMontage)*/)
		{
			/*UE_LOG(LogHJCharacterPlayer, Warning, TEXT("Fire Montage playing"));*/
			AnimInstance->Montage_Play(FireMontage);
		}
	}
}

