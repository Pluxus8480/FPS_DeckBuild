// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HJCharacterBase.h"
#include "InputActionValue.h"
#include "HJCharacterPlayer.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHJCharacterPlayer, Log, All);

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API AHJCharacterPlayer : public AHJCharacterBase
{
	GENERATED_BODY()

public:
	AHJCharacterPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) ;
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PlayFireMontage();

// Camera Section
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FirstPersonCameraComponent;

// Move Section
	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float WalkSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float SprintSpeed = 750.f;

	FVector2D LastInputVector = {};
	bool bIsSprinting = false;

	// 얼마나 입력이 작으면 정지로 판단할지
	const float SprintStopThreshold = 0.1f;

// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShootAction;

	void FPSMove(const FInputActionValue& Value);
	void FPSLook(const FInputActionValue& Value);
	void OnFire();
	void FPSToggleSprint();

// Weapon Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<class AHJGun> Gun;

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSubclassOf<class AHJGun> GunClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<class UAnimMontage> FireMontage;


	void EquipGun(TSubclassOf<class AHJGun> AGun);

};
