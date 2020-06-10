// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "TestAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

// �����̺�� Ʈ���� Find Patrol Task Node ����
UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}
EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn(); // AIController�� �����ϴ� ��
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (NavSystem == nullptr)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ATestAIController::HomePosKey); // NPC ���� ��ġ ��ǥ
	FNavLocation NextPatrol; // ���� ���� ��ġ

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ATestAIController::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
