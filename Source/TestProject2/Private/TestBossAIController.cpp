// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBossAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ATestBossAIController::TargetPosKey(TEXT("TargetPos"));
const FName ATestBossAIController::TargetKey(TEXT("Target"));

ATestBossAIController::ATestBossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBOBJECT(TEXT("/Game/AI/BB_TestBoss.BB_TestBoss"));
	if (BBOBJECT.Succeeded())
	{
		BBAsset = BBOBJECT.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTOBJECT(TEXT("/Game/AI/BT_TestBoss.BT_TestBoss"));
	if (BTOBJECT.Succeeded())
	{
		BTAsset = BTOBJECT.Object;
	}
}

void ATestBossAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
}

void ATestBossAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			TLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}

void ATestBossAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
