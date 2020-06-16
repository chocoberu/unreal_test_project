// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ATestAIController::HomePosKey(TEXT("HomePos"));
const FName ATestAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ATestAIController::TargetKey(TEXT("Target"));
ATestAIController::ATestAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBOBJECT(TEXT("/Game/AI/BB_TestEnemy.BB_TestEnemy"));
	if (BBOBJECT.Succeeded())
	{
		BBAsset = BBOBJECT.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTOBJECT(TEXT("/Game/AI/BT_TestEnemy.BT_TestEnemy"));
	if (BTOBJECT.Succeeded())
	{
		BTAsset = BTOBJECT.Object;
	}
}
void ATestAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

}

void ATestAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			TLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}

void ATestAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
