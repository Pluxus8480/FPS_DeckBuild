// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HJCharacterBaseTPS.h"
#include "InputActionValue.h"
#include "HJCharacterPlayerTPS.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLIENT_API AHJCharacterPlayerTPS : public AHJCharacterBaseTPS
{

	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
public:
	AHJCharacterPlayerTPS();
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SprintAction;

	void TPSMove(const FInputActionValue& Value);
	void TPSLook(const FInputActionValue& Value);
	void TPSToggleSprint();
private:
	void CheckKeyInput(bool IsInput);


	// Move Section
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float WalkSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float SprintSpeed = 750.f;

	FVector2D LastInputVector = {};
	bool bIsSprinting = false;

	// 얼마나 입력이 작으면 정지로 판단할지
	const float SprintStopThreshold = 0.1f;

};
