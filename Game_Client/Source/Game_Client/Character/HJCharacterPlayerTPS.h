// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HJCharacterBaseTPS.h"
#include "InputActionValue.h"
#include "../Interface/HJProjectileAttackInterface.h"
#include "Interface/HJCardUserInterface.h"
#include "HJCharacterPlayerTPS.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHJCharacterPlayerTPS, Log, All);
/**
 * 
 */

UENUM()
enum class EPlayerState: uint8
{
	IDLE = 0,
	WALK_FRONT,
	SIDEWALK,
	SPRINT
};
UENUM()
enum class EPlayerMovementDirection : uint8
{
	WALK_F = 0,
	WALK_L,
	WALK_R,
	WALK_B,
};

UCLASS()
class GAME_CLIENT_API AHJCharacterPlayerTPS : public AHJCharacterBaseTPS, public IHJProjectileAttackInterface, public IHJCardUserInterface
{

	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
public:
	AHJCharacterPlayerTPS();
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void FireProjectile() override;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	void TPSMove(const FInputActionValue& Value);
	void TPSLook(const FInputActionValue& Value);
	void TPSToggleSprint();
public:
	void TPSAttack(const FInputActionValue& Value);
private:
	void CheckKeyInput(bool IsInput);


// Move Section
public:
	void SetMovementState(EPlayerState NewType);
	void SetMovementDirection(EPlayerMovementDirection NewType);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float WalkSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float SideWalkSpeed = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float SprintSpeed = 750.f;

	EPlayerState CurrnetMovementType = EPlayerState::IDLE;
	EPlayerMovementDirection CurrnetMovementDirection = EPlayerMovementDirection::WALK_F;
	// 얼마나 입력이 작으면 정지로 판단할지
	const float SprintStopThreshold = 0.1f;


// AttackSection
public:
	virtual TSubclassOf<class AHJProjectile> GetCurrentProjectile() const override  { return CurrentProjectile; }
protected:
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHJProjectile> CurrentProjectile;
private:
	void UpdateCrosshairTarget();
	FVector AimDirection = {};
//CardUserInterface Section
protected:
	void UseCard(UHJBaseCard* CardUsed) override;
	UHJCardUserComponent* GetCardUser() override;
	void TryAddCard(UHJCardData* CardData) override;

	UPROPERTY(VisibleAnywhere, Category = Card)
	TObjectPtr<class UHJCardUserComponent> CardUser;


// UI Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UHJCrosshairWidget> HJCrosshairWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UHJCrosshairWidget> HJCrosshiarWidget;
};
