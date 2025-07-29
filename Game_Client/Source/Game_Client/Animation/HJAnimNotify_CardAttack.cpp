// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HJAnimNotify_CardAttack.h"
#include "Interface/HJCardUserInterface.h"
#include "../Card/HJCardUserComponent.h"
void UHJAnimNotify_CardAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    IHJCardUserInterface* CardUserObject = Cast<IHJCardUserInterface>(MeshComp->GetOwner());

    if (CardUserObject)
        CardUserObject->GetCardUser()->UseCard();

}