// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HJAttackObject.h"
#include "HJProjectile.generated.h"

UCLASS()
class GAME_CLIENT_API AHJProjectile : public AHJAttackObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHJProjectile();

public:	
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	TObjectPtr <class USphereComponent> GetCollisionComponent() const { return CollisionComponent; }
	/** Returns ProjectileMovement subobject **/
	TObjectPtr <class UProjectileMovementComponent> GetProjectileMovement() const { return ProjectileMovement; }

	void FireInDirection(const FVector& ShootDirection);

protected:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TObjectPtr<class USphereComponent> CollisionComponent;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	TObjectPtr <class UProjectileMovementComponent> ProjectileMovement;

	// 이펙트 & 사운드
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> ProjectileEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> ProjectileDestroyEffect;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundBase> ProjectileSound;
};
