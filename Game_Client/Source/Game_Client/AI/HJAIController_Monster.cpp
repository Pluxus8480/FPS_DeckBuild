// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HJAIController_Monster.h"
#include "HJAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Interface/HJCharacterAIInterface.h"
#include "BehaviorTree/BehaviorTree.h"


AHJAIController_Monster::AHJAIController_Monster()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/HJProject/AI/BB_HJBase.BB_HJBase'"));
	if (BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/HJProject/AI/BT_HJBase.BT_HJBase'"));
	if (BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}


}

void AHJAIController_Monster::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AHJAIController_Monster::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AHJAIController_Monster::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	IHJCharacterAIInterface* AIPawn = Cast<IHJCharacterAIInterface>(InPawn);
	if (AIPawn)
	{
		SetupBlackBoard(AIPawn);
	}
	RunAI();
}

void AHJAIController_Monster::SetupBlackBoard(IHJCharacterAIInterface* AIPawn)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsFloat(BBKEY_ATTACKRANGE, AIPawn->GetAIAttackRange());
		Blackboard->SetValueAsFloat(BBKEY_ATTACKTIME, AIPawn->GetAIAttackSpeed());
	}
}
