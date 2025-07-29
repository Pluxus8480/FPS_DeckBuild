// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HJAnimNotify_SpawnProjectile.h"
#include "HJAnimNotify_SpawnProjectile.h"
#include "../Character/HJCharacterPlayerTPS.h"
#include "../Projectile/HJProjectile.h"
#include "../Interface/HJProjectileAttackInterface.h"

void UHJAnimNotify_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    IHJProjectileAttackInterface* ProjectilePawn = Cast<IHJProjectileAttackInterface>(MeshComp->GetOwner());

    if(ProjectilePawn)
        ProjectilePawn->FireProjectile();

}
